#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct skb_shared_hwtstamps {int /*<<< orphan*/  hwtstamp; } ;
struct sk_buff {int dummy; } ;
struct pcan_usb_msg_context {int ptr; scalar_t__ end; TYPE_3__* netdev; int /*<<< orphan*/  ts16; TYPE_1__* pdev; int /*<<< orphan*/  rec_ts_idx; } ;
struct can_frame {int can_id; int can_dlc; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_5__ {int rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct TYPE_6__ {TYPE_2__ stats; } ;
struct TYPE_4__ {int /*<<< orphan*/  time_ref; } ;

/* Variables and functions */
 int CAN_EFF_FLAG ; 
 int CAN_RTR_FLAG ; 
 int EINVAL ; 
 int ENOMEM ; 
 int PCAN_USB_STATUSLEN_DLC ; 
 int PCAN_USB_STATUSLEN_EXT_ID ; 
 int PCAN_USB_STATUSLEN_RTR ; 
 struct sk_buff* alloc_can_skb (TYPE_3__*,struct can_frame**) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int get_can_dlc (int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 scalar_t__ pcan_usb_decode_ts (struct pcan_usb_msg_context*,int) ; 
 int /*<<< orphan*/  peak_usb_get_ts_time (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct skb_shared_hwtstamps* skb_hwtstamps (struct sk_buff*) ; 

__attribute__((used)) static int pcan_usb_decode_data(struct pcan_usb_msg_context *mc, u8 status_len)
{
	u8 rec_len = status_len & PCAN_USB_STATUSLEN_DLC;
	struct sk_buff *skb;
	struct can_frame *cf;
	struct skb_shared_hwtstamps *hwts;

	skb = alloc_can_skb(mc->netdev, &cf);
	if (!skb)
		return -ENOMEM;

	if (status_len & PCAN_USB_STATUSLEN_EXT_ID) {
		__le32 tmp32;

		if ((mc->ptr + 4) > mc->end)
			goto decode_failed;

		memcpy(&tmp32, mc->ptr, 4);
		mc->ptr += 4;

		cf->can_id = (le32_to_cpu(tmp32) >> 3) | CAN_EFF_FLAG;
	} else {
		__le16 tmp16;

		if ((mc->ptr + 2) > mc->end)
			goto decode_failed;

		memcpy(&tmp16, mc->ptr, 2);
		mc->ptr += 2;

		cf->can_id = le16_to_cpu(tmp16) >> 5;
	}

	cf->can_dlc = get_can_dlc(rec_len);

	/* Only first packet timestamp is a word */
	if (pcan_usb_decode_ts(mc, !mc->rec_ts_idx))
		goto decode_failed;

	/* Next packet in the buffer will have a timestamp on a single byte */
	mc->rec_ts_idx++;

	/* read data */
	memset(cf->data, 0x0, sizeof(cf->data));
	if (status_len & PCAN_USB_STATUSLEN_RTR) {
		cf->can_id |= CAN_RTR_FLAG;
	} else {
		if ((mc->ptr + rec_len) > mc->end)
			goto decode_failed;

		memcpy(cf->data, mc->ptr, cf->can_dlc);
		mc->ptr += rec_len;
	}

	/* convert timestamp into kernel time */
	hwts = skb_hwtstamps(skb);
	peak_usb_get_ts_time(&mc->pdev->time_ref, mc->ts16, &hwts->hwtstamp);

	/* update statistics */
	mc->netdev->stats.rx_packets++;
	mc->netdev->stats.rx_bytes += cf->can_dlc;
	/* push the skb */
	netif_rx(skb);

	return 0;

decode_failed:
	dev_kfree_skb(skb);
	return -EINVAL;
}