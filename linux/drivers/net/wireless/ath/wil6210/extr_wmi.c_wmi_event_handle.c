#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t u8 ;
typedef  int u16 ;
struct wmi_cmd_hdr {size_t mid; int /*<<< orphan*/  command_id; } ;
struct wil6210_vif {int dummy; } ;
struct wil6210_priv {int reply_id; size_t reply_mid; int /*<<< orphan*/  wmi_call; scalar_t__ reply_buf; struct wil6210_vif** vifs; } ;
struct wil6210_mbox_hdr {scalar_t__ type; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 size_t GET_MAX_VIFS (struct wil6210_priv*) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 size_t MID_BROADCAST ; 
 scalar_t__ WIL_MBOX_HDR_TYPE_WMI ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eventid2name (int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,struct wil6210_mbox_hdr*,int,int) ; 
 int /*<<< orphan*/  wil_dbg_wmi (struct wil6210_priv*,char*,int,...) ; 
 int /*<<< orphan*/  wil_err (struct wil6210_priv*,char*,...) ; 
 int /*<<< orphan*/  wil_info (struct wil6210_priv*,char*,int) ; 
 int /*<<< orphan*/  wmi_evt_call_handler (struct wil6210_vif*,int,void*,int) ; 

__attribute__((used)) static void wmi_event_handle(struct wil6210_priv *wil,
			     struct wil6210_mbox_hdr *hdr)
{
	u16 len = le16_to_cpu(hdr->len);
	struct wil6210_vif *vif;

	if ((hdr->type == WIL_MBOX_HDR_TYPE_WMI) &&
	    (len >= sizeof(struct wmi_cmd_hdr))) {
		struct wmi_cmd_hdr *wmi = (void *)(&hdr[1]);
		void *evt_data = (void *)(&wmi[1]);
		u16 id = le16_to_cpu(wmi->command_id);
		u8 mid = wmi->mid;

		wil_dbg_wmi(wil, "Handle %s (0x%04x) (reply_id 0x%04x,%d)\n",
			    eventid2name(id), id, wil->reply_id,
			    wil->reply_mid);

		if (mid == MID_BROADCAST)
			mid = 0;
		if (mid >= GET_MAX_VIFS(wil)) {
			wil_dbg_wmi(wil, "invalid mid %d, event skipped\n",
				    mid);
			return;
		}
		vif = wil->vifs[mid];
		if (!vif) {
			wil_dbg_wmi(wil, "event for empty VIF(%d), skipped\n",
				    mid);
			return;
		}

		/* check if someone waits for this event */
		if (wil->reply_id && wil->reply_id == id &&
		    wil->reply_mid == mid) {
			if (wil->reply_buf) {
				/* event received while wmi_call is waiting
				 * with a buffer. Such event should be handled
				 * in wmi_recv_cmd function. Handling the event
				 * here means a previous wmi_call was timeout.
				 * Drop the event and do not handle it.
				 */
				wil_err(wil,
					"Old event (%d, %s) while wmi_call is waiting. Drop it and Continue waiting\n",
					id, eventid2name(id));
				return;
			}

			wmi_evt_call_handler(vif, id, evt_data,
					     len - sizeof(*wmi));
			wil_dbg_wmi(wil, "event_handle: Complete WMI 0x%04x\n",
				    id);
			complete(&wil->wmi_call);
			return;
		}
		/* unsolicited event */
		/* search for handler */
		if (!wmi_evt_call_handler(vif, id, evt_data,
					  len - sizeof(*wmi))) {
			wil_info(wil, "Unhandled event 0x%04x\n", id);
		}
	} else {
		wil_err(wil, "Unknown event type\n");
		print_hex_dump(KERN_ERR, "evt?? ", DUMP_PREFIX_OFFSET, 16, 1,
			       hdr, sizeof(*hdr) + len, true);
	}
}