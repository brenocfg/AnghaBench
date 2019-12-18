#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
union iwl_dbg_tlv_tp_data {struct iwl_rx_packet* fw_pkt; } ;
struct TYPE_3__ {int /*<<< orphan*/  cmd; int /*<<< orphan*/  group_id; } ;
struct iwl_rx_packet {TYPE_1__ hdr; } ;
struct iwl_rx_handlers {scalar_t__ cmd_id; scalar_t__ context; int /*<<< orphan*/  (* fn ) (struct iwl_mvm*,struct iwl_rx_cmd_buffer*) ;} ;
struct iwl_rx_cmd_buffer {int /*<<< orphan*/  _rx_page_order; int /*<<< orphan*/  _offset; } ;
struct iwl_mvm {int /*<<< orphan*/  async_handlers_wk; int /*<<< orphan*/  async_handlers_lock; int /*<<< orphan*/  async_handlers_list; int /*<<< orphan*/  notif_wait; int /*<<< orphan*/  fwrt; } ;
struct TYPE_4__ {int /*<<< orphan*/  _rx_page_order; int /*<<< orphan*/  _offset; int /*<<< orphan*/  _page; } ;
struct iwl_async_handler_entry {scalar_t__ context; int /*<<< orphan*/  list; int /*<<< orphan*/  (* fn ) (struct iwl_mvm*,struct iwl_rx_cmd_buffer*) ;TYPE_2__ rxb; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct iwl_rx_handlers*) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IWL_FW_INI_TIME_POINT_FW_RSP_OR_NOTIF ; 
 scalar_t__ RX_HANDLER_SYNC ; 
 scalar_t__ WIDE_ID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_dbg_tlv_time_point (int /*<<< orphan*/ *,int /*<<< orphan*/ ,union iwl_dbg_tlv_tp_data*) ; 
 int /*<<< orphan*/  iwl_mvm_rx_check_trigger (struct iwl_mvm*,struct iwl_rx_packet*) ; 
 struct iwl_rx_handlers* iwl_mvm_rx_handlers ; 
 int /*<<< orphan*/  iwl_notification_wait_notify (int /*<<< orphan*/ *,struct iwl_rx_packet*) ; 
 struct iwl_async_handler_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxb_steal_page (struct iwl_rx_cmd_buffer*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct iwl_mvm*,struct iwl_rx_cmd_buffer*) ; 

__attribute__((used)) static void iwl_mvm_rx_common(struct iwl_mvm *mvm,
			      struct iwl_rx_cmd_buffer *rxb,
			      struct iwl_rx_packet *pkt)
{
	int i;
	union iwl_dbg_tlv_tp_data tp_data = { .fw_pkt = pkt };

	iwl_dbg_tlv_time_point(&mvm->fwrt,
			       IWL_FW_INI_TIME_POINT_FW_RSP_OR_NOTIF, &tp_data);
	iwl_mvm_rx_check_trigger(mvm, pkt);

	/*
	 * Do the notification wait before RX handlers so
	 * even if the RX handler consumes the RXB we have
	 * access to it in the notification wait entry.
	 */
	iwl_notification_wait_notify(&mvm->notif_wait, pkt);

	for (i = 0; i < ARRAY_SIZE(iwl_mvm_rx_handlers); i++) {
		const struct iwl_rx_handlers *rx_h = &iwl_mvm_rx_handlers[i];
		struct iwl_async_handler_entry *entry;

		if (rx_h->cmd_id != WIDE_ID(pkt->hdr.group_id, pkt->hdr.cmd))
			continue;

		if (rx_h->context == RX_HANDLER_SYNC) {
			rx_h->fn(mvm, rxb);
			return;
		}

		entry = kzalloc(sizeof(*entry), GFP_ATOMIC);
		/* we can't do much... */
		if (!entry)
			return;

		entry->rxb._page = rxb_steal_page(rxb);
		entry->rxb._offset = rxb->_offset;
		entry->rxb._rx_page_order = rxb->_rx_page_order;
		entry->fn = rx_h->fn;
		entry->context = rx_h->context;
		spin_lock(&mvm->async_handlers_lock);
		list_add_tail(&entry->list, &mvm->async_handlers_list);
		spin_unlock(&mvm->async_handlers_lock);
		schedule_work(&mvm->async_handlers_wk);
		break;
	}
}