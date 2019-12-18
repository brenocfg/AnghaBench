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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct wmi_tx_complete_event {int num_msg; int /*<<< orphan*/  msg_type; int /*<<< orphan*/  msg_len; } ;
struct tx_complete_msg_v1 {int /*<<< orphan*/  ack_failures; int /*<<< orphan*/  rate_idx; int /*<<< orphan*/  pkt_id; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_WMI ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int ath6kl_wmi_tx_complete_event_rx(u8 *datap, int len)
{
	struct tx_complete_msg_v1 *msg_v1;
	struct wmi_tx_complete_event *evt;
	int index;
	u16 size;

	evt = (struct wmi_tx_complete_event *) datap;

	ath6kl_dbg(ATH6KL_DBG_WMI, "comp: %d %d %d\n",
		   evt->num_msg, evt->msg_len, evt->msg_type);

	for (index = 0; index < evt->num_msg; index++) {
		size = sizeof(struct wmi_tx_complete_event) +
		    (index * sizeof(struct tx_complete_msg_v1));
		msg_v1 = (struct tx_complete_msg_v1 *)(datap + size);

		ath6kl_dbg(ATH6KL_DBG_WMI, "msg: %d %d %d %d\n",
			   msg_v1->status, msg_v1->pkt_id,
			   msg_v1->rate_idx, msg_v1->ack_failures);
	}

	return 0;
}