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
struct TYPE_2__ {int /*<<< orphan*/  (* wakeup ) (struct mwifiex_adapter*) ;int /*<<< orphan*/  (* process_int_status ) (struct mwifiex_adapter*) ;} ;
struct mwifiex_adapter {int mwifiex_processing; int more_task_flag; scalar_t__ hw_status; scalar_t__ iface_type; int delay_main_work; int data_received; scalar_t__ ps_state; int pm_wakeup_fw_try; int event_received; int cmd_resp_received; int delay_null_pkt; int /*<<< orphan*/  main_proc_lock; int /*<<< orphan*/  tx_data_q; scalar_t__ curr_cmd; scalar_t__ cmd_sent; int /*<<< orphan*/  work_flags; scalar_t__ hs_activated; scalar_t__ data_sent; scalar_t__ scan_processing; scalar_t__ scan_chan_gap_enabled; scalar_t__ usb_mc_setup; scalar_t__ tx_lock_flag; int /*<<< orphan*/  wakeup_timer; TYPE_1__ if_ops; scalar_t__ pm_wakeup_card_req; scalar_t__ rx_work_enabled; scalar_t__ int_status; int /*<<< orphan*/  rx_pending; scalar_t__ main_locked; } ;

/* Variables and functions */
 scalar_t__ HIGH_RX_PENDING ; 
 int HZ ; 
 scalar_t__ IS_CARD_RX_RCVD (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  MWIFIEX_BSS_ROLE_ANY ; 
 int /*<<< orphan*/  MWIFIEX_BSS_ROLE_STA ; 
 scalar_t__ MWIFIEX_HW_STATUS_INIT_DONE ; 
 scalar_t__ MWIFIEX_HW_STATUS_NOT_READY ; 
 scalar_t__ MWIFIEX_HW_STATUS_READY ; 
 int /*<<< orphan*/  MWIFIEX_IS_HS_CONFIGURED ; 
 int MWIFIEX_TxPD_POWER_MGMT_LAST_PACKET ; 
 int MWIFIEX_TxPD_POWER_MGMT_NULL_PACKET ; 
 scalar_t__ MWIFIEX_USB ; 
 scalar_t__ PS_STATE_AWAKE ; 
 scalar_t__ PS_STATE_PRE_SLEEP ; 
 scalar_t__ PS_STATE_SLEEP ; 
 scalar_t__ PS_STATE_SLEEP_CFM ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 scalar_t__ is_command_pending (struct mwifiex_adapter*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ mwifiex_bypass_txlist_empty (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_check_ps_cond (struct mwifiex_adapter*) ; 
 int mwifiex_exec_next_cmd (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_get_priv (struct mwifiex_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_hs_activated_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mwifiex_init_fw_complete (struct mwifiex_adapter*) ; 
 scalar_t__ mwifiex_is_send_cmd_allowed (int /*<<< orphan*/ ) ; 
 scalar_t__ mwifiex_is_tdls_chan_switching (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_process_bypass_tx (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_process_cmdresp (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_process_event (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_process_hs_config (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_process_tx_queue (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_queue_rx_work (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_send_null_packet (int /*<<< orphan*/ ,int) ; 
 scalar_t__ mwifiex_wmm_lists_empty (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_wmm_process_tx (struct mwifiex_adapter*) ; 
 scalar_t__ skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  stub2 (struct mwifiex_adapter*) ; 

int mwifiex_main_process(struct mwifiex_adapter *adapter)
{
	int ret = 0;
	unsigned long flags;

	spin_lock_irqsave(&adapter->main_proc_lock, flags);

	/* Check if already processing */
	if (adapter->mwifiex_processing || adapter->main_locked) {
		adapter->more_task_flag = true;
		spin_unlock_irqrestore(&adapter->main_proc_lock, flags);
		return 0;
	} else {
		adapter->mwifiex_processing = true;
		spin_unlock_irqrestore(&adapter->main_proc_lock, flags);
	}
process_start:
	do {
		if (adapter->hw_status == MWIFIEX_HW_STATUS_NOT_READY)
			break;

		/* For non-USB interfaces, If we process interrupts first, it
		 * would increase RX pending even further. Avoid this by
		 * checking if rx_pending has crossed high threshold and
		 * schedule rx work queue and then process interrupts.
		 * For USB interface, there are no interrupts. We already have
		 * HIGH_RX_PENDING check in usb.c
		 */
		if (atomic_read(&adapter->rx_pending) >= HIGH_RX_PENDING &&
		    adapter->iface_type != MWIFIEX_USB) {
			adapter->delay_main_work = true;
			mwifiex_queue_rx_work(adapter);
			break;
		}

		/* Handle pending interrupt if any */
		if (adapter->int_status) {
			if (adapter->hs_activated)
				mwifiex_process_hs_config(adapter);
			if (adapter->if_ops.process_int_status)
				adapter->if_ops.process_int_status(adapter);
		}

		if (adapter->rx_work_enabled && adapter->data_received)
			mwifiex_queue_rx_work(adapter);

		/* Need to wake up the card ? */
		if ((adapter->ps_state == PS_STATE_SLEEP) &&
		    (adapter->pm_wakeup_card_req &&
		     !adapter->pm_wakeup_fw_try) &&
		    (is_command_pending(adapter) ||
		     !skb_queue_empty(&adapter->tx_data_q) ||
		     !mwifiex_bypass_txlist_empty(adapter) ||
		     !mwifiex_wmm_lists_empty(adapter))) {
			adapter->pm_wakeup_fw_try = true;
			mod_timer(&adapter->wakeup_timer, jiffies + (HZ*3));
			adapter->if_ops.wakeup(adapter);
			continue;
		}

		if (IS_CARD_RX_RCVD(adapter)) {
			adapter->data_received = false;
			adapter->pm_wakeup_fw_try = false;
			del_timer(&adapter->wakeup_timer);
			if (adapter->ps_state == PS_STATE_SLEEP)
				adapter->ps_state = PS_STATE_AWAKE;
		} else {
			/* We have tried to wakeup the card already */
			if (adapter->pm_wakeup_fw_try)
				break;
			if (adapter->ps_state == PS_STATE_PRE_SLEEP)
				mwifiex_check_ps_cond(adapter);

			if (adapter->ps_state != PS_STATE_AWAKE)
				break;
			if (adapter->tx_lock_flag) {
				if (adapter->iface_type == MWIFIEX_USB) {
					if (!adapter->usb_mc_setup)
						break;
				} else
					break;
			}

			if ((!adapter->scan_chan_gap_enabled &&
			     adapter->scan_processing) || adapter->data_sent ||
			     mwifiex_is_tdls_chan_switching
			     (mwifiex_get_priv(adapter,
					       MWIFIEX_BSS_ROLE_STA)) ||
			    (mwifiex_wmm_lists_empty(adapter) &&
			     mwifiex_bypass_txlist_empty(adapter) &&
			     skb_queue_empty(&adapter->tx_data_q))) {
				if (adapter->cmd_sent || adapter->curr_cmd ||
					!mwifiex_is_send_cmd_allowed
						(mwifiex_get_priv(adapter,
						MWIFIEX_BSS_ROLE_STA)) ||
				    (!is_command_pending(adapter)))
					break;
			}
		}

		/* Check for event */
		if (adapter->event_received) {
			adapter->event_received = false;
			mwifiex_process_event(adapter);
		}

		/* Check for Cmd Resp */
		if (adapter->cmd_resp_received) {
			adapter->cmd_resp_received = false;
			mwifiex_process_cmdresp(adapter);

			/* call mwifiex back when init_fw is done */
			if (adapter->hw_status == MWIFIEX_HW_STATUS_INIT_DONE) {
				adapter->hw_status = MWIFIEX_HW_STATUS_READY;
				mwifiex_init_fw_complete(adapter);
			}
		}

		/* Check if we need to confirm Sleep Request
		   received previously */
		if (adapter->ps_state == PS_STATE_PRE_SLEEP)
			mwifiex_check_ps_cond(adapter);

		/* * The ps_state may have been changed during processing of
		 * Sleep Request event.
		 */
		if ((adapter->ps_state == PS_STATE_SLEEP) ||
		    (adapter->ps_state == PS_STATE_PRE_SLEEP) ||
		    (adapter->ps_state == PS_STATE_SLEEP_CFM)) {
			continue;
		}

		if (adapter->tx_lock_flag) {
			if (adapter->iface_type == MWIFIEX_USB) {
				if (!adapter->usb_mc_setup)
					continue;
			} else
				continue;
		}

		if (!adapter->cmd_sent && !adapter->curr_cmd &&
		    mwifiex_is_send_cmd_allowed
		    (mwifiex_get_priv(adapter, MWIFIEX_BSS_ROLE_STA))) {
			if (mwifiex_exec_next_cmd(adapter) == -1) {
				ret = -1;
				break;
			}
		}

		/** If USB Multi channel setup ongoing,
		 *  wait for ready to tx data.
		 */
		if (adapter->iface_type == MWIFIEX_USB &&
		    adapter->usb_mc_setup)
			continue;

		if ((adapter->scan_chan_gap_enabled ||
		     !adapter->scan_processing) &&
		    !adapter->data_sent &&
		    !skb_queue_empty(&adapter->tx_data_q)) {
			mwifiex_process_tx_queue(adapter);
			if (adapter->hs_activated) {
				clear_bit(MWIFIEX_IS_HS_CONFIGURED,
					  &adapter->work_flags);
				mwifiex_hs_activated_event
					(mwifiex_get_priv
					(adapter, MWIFIEX_BSS_ROLE_ANY),
					false);
			}
		}

		if ((adapter->scan_chan_gap_enabled ||
		     !adapter->scan_processing) &&
		    !adapter->data_sent &&
		    !mwifiex_bypass_txlist_empty(adapter) &&
		    !mwifiex_is_tdls_chan_switching
			(mwifiex_get_priv(adapter, MWIFIEX_BSS_ROLE_STA))) {
			mwifiex_process_bypass_tx(adapter);
			if (adapter->hs_activated) {
				clear_bit(MWIFIEX_IS_HS_CONFIGURED,
					  &adapter->work_flags);
				mwifiex_hs_activated_event
					(mwifiex_get_priv
					 (adapter, MWIFIEX_BSS_ROLE_ANY),
					 false);
			}
		}

		if ((adapter->scan_chan_gap_enabled ||
		     !adapter->scan_processing) &&
		    !adapter->data_sent && !mwifiex_wmm_lists_empty(adapter) &&
		    !mwifiex_is_tdls_chan_switching
			(mwifiex_get_priv(adapter, MWIFIEX_BSS_ROLE_STA))) {
			mwifiex_wmm_process_tx(adapter);
			if (adapter->hs_activated) {
				clear_bit(MWIFIEX_IS_HS_CONFIGURED,
					  &adapter->work_flags);
				mwifiex_hs_activated_event
					(mwifiex_get_priv
					 (adapter, MWIFIEX_BSS_ROLE_ANY),
					 false);
			}
		}

		if (adapter->delay_null_pkt && !adapter->cmd_sent &&
		    !adapter->curr_cmd && !is_command_pending(adapter) &&
		    (mwifiex_wmm_lists_empty(adapter) &&
		     mwifiex_bypass_txlist_empty(adapter) &&
		     skb_queue_empty(&adapter->tx_data_q))) {
			if (!mwifiex_send_null_packet
			    (mwifiex_get_priv(adapter, MWIFIEX_BSS_ROLE_STA),
			     MWIFIEX_TxPD_POWER_MGMT_NULL_PACKET |
			     MWIFIEX_TxPD_POWER_MGMT_LAST_PACKET)) {
				adapter->delay_null_pkt = false;
				adapter->ps_state = PS_STATE_SLEEP;
			}
			break;
		}
	} while (true);

	spin_lock_irqsave(&adapter->main_proc_lock, flags);
	if (adapter->more_task_flag) {
		adapter->more_task_flag = false;
		spin_unlock_irqrestore(&adapter->main_proc_lock, flags);
		goto process_start;
	}
	adapter->mwifiex_processing = false;
	spin_unlock_irqrestore(&adapter->main_proc_lock, flags);

	return ret;
}