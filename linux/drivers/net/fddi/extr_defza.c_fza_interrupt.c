#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint ;
struct net_device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  expires; } ;
struct fza_private {int int_mask; int cmd_done_flag; int state; int queue_active; int state_chg_flag; int /*<<< orphan*/  lock; int /*<<< orphan*/  state_chg_wait; int /*<<< orphan*/  name; TYPE_2__ reset_timer; int /*<<< orphan*/  timer_state; int /*<<< orphan*/  ring_smt_rx_index; int /*<<< orphan*/  ring_smt_tx_index; int /*<<< orphan*/  ring_hst_rx_index; int /*<<< orphan*/  ring_rmc_txd_index; int /*<<< orphan*/  ring_rmc_tx_index; int /*<<< orphan*/  ring_uns_index; int /*<<< orphan*/  ring_cmd_index; TYPE_1__* regs; int /*<<< orphan*/  irq_count_state_chg; int /*<<< orphan*/  irq_count_uns_poll; int /*<<< orphan*/  irq_count_link_st_chg; int /*<<< orphan*/  irq_count_flush_tx; int /*<<< orphan*/  irq_count_smt_tx_poll; int /*<<< orphan*/  irq_count_rx_poll; int /*<<< orphan*/  irq_count_tx_done; int /*<<< orphan*/  cmd_done_wait; int /*<<< orphan*/  irq_count_cmd_done; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  status; int /*<<< orphan*/  int_event; } ;

/* Variables and functions */
 int FZA_EVENT_CMD_DONE ; 
 int FZA_EVENT_FLUSH_TX ; 
 int FZA_EVENT_LINK_ST_CHG ; 
 int FZA_EVENT_RX_POLL ; 
 int FZA_EVENT_SMT_TX_POLL ; 
 int FZA_EVENT_STATE_CHG ; 
 int FZA_EVENT_TX_DONE ; 
 int FZA_EVENT_UNS_POLL ; 
 scalar_t__ FZA_LINK_ON ; 
 int /*<<< orphan*/  FZA_RING_CMD_INIT ; 
 int /*<<< orphan*/  FZA_RING_CMD_PARAM ; 
#define  FZA_STATE_HALTED 133 
#define  FZA_STATE_INITIALIZED 132 
#define  FZA_STATE_MAINTENANCE 131 
#define  FZA_STATE_RESET 130 
#define  FZA_STATE_RUNNING 129 
#define  FZA_STATE_UNINITIALIZED 128 
 int FZA_STATUS_GET_HALT (int) ; 
 scalar_t__ FZA_STATUS_GET_LINK (int) ; 
 int FZA_STATUS_GET_STATE (int) ; 
 int HZ ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  del_timer_sync (TYPE_2__*) ; 
 int /*<<< orphan*/  fza_cmd_send (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fza_do_reset (struct fza_private*) ; 
 int /*<<< orphan*/  fza_regs_dump (struct fza_private*) ; 
 int /*<<< orphan*/  fza_rx (struct net_device*) ; 
 int /*<<< orphan*/  fza_rx_init (struct fza_private*) ; 
 int /*<<< orphan*/  fza_set_rx_mode (struct net_device*) ; 
 int /*<<< orphan*/  fza_tx (struct net_device*) ; 
 int /*<<< orphan*/  fza_tx_flush (struct net_device*) ; 
 int /*<<< orphan*/  fza_tx_smt (struct net_device*) ; 
 int /*<<< orphan*/  fza_uns (struct net_device*) ; 
 int /*<<< orphan*/  jiffies ; 
 struct fza_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int) ; 
 int readw_o (int /*<<< orphan*/ *) ; 
 int readw_u (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writew_u (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t fza_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = dev_id;
	struct fza_private *fp = netdev_priv(dev);
	uint int_event;

	/* Get interrupt events. */
	int_event = readw_o(&fp->regs->int_event) & fp->int_mask;
	if (int_event == 0)
		return IRQ_NONE;

	/* Clear the events. */
	writew_u(int_event, &fp->regs->int_event);

	/* Now handle the events.  The order matters. */

	/* Command finished interrupt. */
	if ((int_event & FZA_EVENT_CMD_DONE) != 0) {
		fp->irq_count_cmd_done++;

		spin_lock(&fp->lock);
		fp->cmd_done_flag = 1;
		wake_up(&fp->cmd_done_wait);
		spin_unlock(&fp->lock);
	}

	/* Transmit finished interrupt. */
	if ((int_event & FZA_EVENT_TX_DONE) != 0) {
		fp->irq_count_tx_done++;
		fza_tx(dev);
	}

	/* Host receive interrupt. */
	if ((int_event & FZA_EVENT_RX_POLL) != 0) {
		fp->irq_count_rx_poll++;
		fza_rx(dev);
	}

	/* SMT transmit interrupt. */
	if ((int_event & FZA_EVENT_SMT_TX_POLL) != 0) {
		fp->irq_count_smt_tx_poll++;
		fza_tx_smt(dev);
	}

	/* Transmit ring flush request. */
	if ((int_event & FZA_EVENT_FLUSH_TX) != 0) {
		fp->irq_count_flush_tx++;
		fza_tx_flush(dev);
	}

	/* Link status change interrupt. */
	if ((int_event & FZA_EVENT_LINK_ST_CHG) != 0) {
		uint status;

		fp->irq_count_link_st_chg++;
		status = readw_u(&fp->regs->status);
		if (FZA_STATUS_GET_LINK(status) == FZA_LINK_ON) {
			netif_carrier_on(dev);
			pr_info("%s: link available\n", fp->name);
		} else {
			netif_carrier_off(dev);
			pr_info("%s: link unavailable\n", fp->name);
		}
	}

	/* Unsolicited event interrupt. */
	if ((int_event & FZA_EVENT_UNS_POLL) != 0) {
		fp->irq_count_uns_poll++;
		fza_uns(dev);
	}

	/* State change interrupt. */
	if ((int_event & FZA_EVENT_STATE_CHG) != 0) {
		uint status, state;

		fp->irq_count_state_chg++;

		status = readw_u(&fp->regs->status);
		state = FZA_STATUS_GET_STATE(status);
		pr_debug("%s: state change: %x\n", fp->name, state);
		switch (state) {
		case FZA_STATE_RESET:
			break;

		case FZA_STATE_UNINITIALIZED:
			netif_carrier_off(dev);
			del_timer_sync(&fp->reset_timer);
			fp->ring_cmd_index = 0;
			fp->ring_uns_index = 0;
			fp->ring_rmc_tx_index = 0;
			fp->ring_rmc_txd_index = 0;
			fp->ring_hst_rx_index = 0;
			fp->ring_smt_tx_index = 0;
			fp->ring_smt_rx_index = 0;
			if (fp->state > state) {
				pr_info("%s: OK\n", fp->name);
				fza_cmd_send(dev, FZA_RING_CMD_INIT);
			}
			break;

		case FZA_STATE_INITIALIZED:
			if (fp->state > state) {
				fza_set_rx_mode(dev);
				fza_cmd_send(dev, FZA_RING_CMD_PARAM);
			}
			break;

		case FZA_STATE_RUNNING:
		case FZA_STATE_MAINTENANCE:
			fp->state = state;
			fza_rx_init(fp);
			fp->queue_active = 1;
			netif_wake_queue(dev);
			pr_debug("%s: queue woken\n", fp->name);
			break;

		case FZA_STATE_HALTED:
			fp->queue_active = 0;
			netif_stop_queue(dev);
			pr_debug("%s: queue stopped\n", fp->name);
			del_timer_sync(&fp->reset_timer);
			pr_warn("%s: halted, reason: %x\n", fp->name,
				FZA_STATUS_GET_HALT(status));
			fza_regs_dump(fp);
			pr_info("%s: resetting the board...\n", fp->name);
			fza_do_reset(fp);
			fp->timer_state = 0;
			fp->reset_timer.expires = jiffies + 45 * HZ;
			add_timer(&fp->reset_timer);
			break;

		default:
			pr_warn("%s: undefined state: %x\n", fp->name, state);
			break;
		}

		spin_lock(&fp->lock);
		fp->state_chg_flag = 1;
		wake_up(&fp->state_chg_wait);
		spin_unlock(&fp->lock);
	}

	return IRQ_HANDLED;
}