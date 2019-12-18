#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ len; } ;
struct mwifiex_private {struct mwifiex_adapter* adapter; } ;
struct mwifiex_fw_dump_header {scalar_t__ type; } ;
struct mwifiex_adapter {scalar_t__ iface_type; scalar_t__ devdump_data; scalar_t__ devdump_len; int /*<<< orphan*/  devdump_timer; TYPE_1__* event_skb; scalar_t__ event_body; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ FW_DUMP_INFO_ENDED ; 
 int /*<<< orphan*/  MSG ; 
 scalar_t__ MWIFIEX_FW_DUMP_SIZE ; 
 int /*<<< orphan*/  MWIFIEX_TIMER_10S ; 
 scalar_t__ MWIFIEX_USB ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 scalar_t__ le16_to_cpu (int) ; 
 int /*<<< orphan*/  memmove (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mwifiex_drv_info_dump (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_upload_device_dump (struct mwifiex_adapter*) ; 
 scalar_t__ vzalloc (scalar_t__) ; 

__attribute__((used)) static void
mwifiex_fw_dump_info_event(struct mwifiex_private *priv,
			   struct sk_buff *event_skb)
{
	struct mwifiex_adapter *adapter = priv->adapter;
	struct mwifiex_fw_dump_header *fw_dump_hdr =
				(void *)adapter->event_body;

	if (adapter->iface_type != MWIFIEX_USB) {
		mwifiex_dbg(adapter, MSG,
			    "event is not on usb interface, ignore it\n");
		return;
	}

	if (!adapter->devdump_data) {
		/* When receive the first event, allocate device dump
		 * buffer, dump driver info.
		 */
		adapter->devdump_data = vzalloc(MWIFIEX_FW_DUMP_SIZE);
		if (!adapter->devdump_data) {
			mwifiex_dbg(adapter, ERROR,
				    "vzalloc devdump data failure!\n");
			return;
		}

		mwifiex_drv_info_dump(adapter);

		/* If no proceeded event arrive in 10s, upload device
		 * dump data, this will be useful if the end of
		 * transmission event get lost, in this cornel case,
		 * user would still get partial of the dump.
		 */
		mod_timer(&adapter->devdump_timer,
			  jiffies + msecs_to_jiffies(MWIFIEX_TIMER_10S));
	}

	/* Overflow check */
	if (adapter->devdump_len + event_skb->len >= MWIFIEX_FW_DUMP_SIZE)
		goto upload_dump;

	memmove(adapter->devdump_data + adapter->devdump_len,
		adapter->event_skb->data, event_skb->len);
	adapter->devdump_len += event_skb->len;

	if (le16_to_cpu(fw_dump_hdr->type == FW_DUMP_INFO_ENDED)) {
		mwifiex_dbg(adapter, MSG,
			    "receive end of transmission flag event!\n");
		goto upload_dump;
	}
	return;

upload_dump:
	del_timer_sync(&adapter->devdump_timer);
	mwifiex_upload_device_dump(adapter);
}