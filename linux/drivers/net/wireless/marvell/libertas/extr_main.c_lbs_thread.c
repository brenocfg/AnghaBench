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
typedef  int /*<<< orphan*/  wait_queue_entry_t ;
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int /*<<< orphan*/  dismantle; struct lbs_private* ml_priv; } ;
struct lbs_private {scalar_t__ currenttxskb; scalar_t__ psstate; scalar_t__ tx_pending_len; size_t resp_idx; scalar_t__ connect_status; int (* hw_host_to_card ) (struct lbs_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ;int /*<<< orphan*/  auto_deepsleep_timer; int /*<<< orphan*/  tx_lockup_timer; int /*<<< orphan*/  command_timer; int /*<<< orphan*/  driver_lock; scalar_t__ mesh_dev; scalar_t__ dev; scalar_t__ dnld_sent; int /*<<< orphan*/  tx_pending_buf; struct cmd_ctrl_node* cur_cmd; scalar_t__ is_deep_sleep; int /*<<< orphan*/  fw_ready; scalar_t__ cmd_timed_out; int /*<<< orphan*/  (* reset_card ) (struct lbs_private*) ;scalar_t__ (* exit_deep_sleep ) (struct lbs_private*) ;scalar_t__ wakeup_dev_required; int /*<<< orphan*/  event_fifo; scalar_t__* resp_len; int /*<<< orphan*/ * resp_buf; scalar_t__ surpriseremoved; int /*<<< orphan*/  waitq; scalar_t__ psmode; int /*<<< orphan*/  cmdpendingq; } ;
struct cmd_ctrl_node {TYPE_1__* cmdbuf; } ;
typedef  int /*<<< orphan*/  event ;
struct TYPE_2__ {int /*<<< orphan*/  command; } ;

/* Variables and functions */
 scalar_t__ DNLD_RES_RECEIVED ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 int HZ ; 
 scalar_t__ LBS_CONNECTED ; 
 int /*<<< orphan*/  MVMS_DAT ; 
 scalar_t__ PS_STATE_AWAKE ; 
 scalar_t__ PS_STATE_PRE_SLEEP ; 
 scalar_t__ PS_STATE_SLEEP ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 scalar_t__ kfifo_len (int /*<<< orphan*/ *) ; 
 int kfifo_out (int /*<<< orphan*/ *,unsigned char*,int) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  lbs_complete_command (struct lbs_private*,struct cmd_ctrl_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_thread (char*,...) ; 
 int /*<<< orphan*/  lbs_deb_tx (char*,int) ; 
 int /*<<< orphan*/  lbs_execute_next_command (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_process_command_response (struct lbs_private*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  lbs_process_event (struct lbs_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_ps_confirm_sleep (struct lbs_private*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  netdev_alert (struct net_device*,char*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ netif_running (scalar_t__) ; 
 int /*<<< orphan*/  netif_wake_queue (scalar_t__) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct lbs_private*) ; 
 int /*<<< orphan*/  stub2 (struct lbs_private*) ; 
 int stub3 (struct lbs_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int lbs_thread(void *data)
{
	struct net_device *dev = data;
	struct lbs_private *priv = dev->ml_priv;
	wait_queue_entry_t wait;

	init_waitqueue_entry(&wait, current);

	for (;;) {
		int shouldsleep;
		u8 resp_idx;

		lbs_deb_thread("1: currenttxskb %p, dnld_sent %d\n",
				priv->currenttxskb, priv->dnld_sent);

		add_wait_queue(&priv->waitq, &wait);
		set_current_state(TASK_INTERRUPTIBLE);
		spin_lock_irq(&priv->driver_lock);

		if (kthread_should_stop())
			shouldsleep = 0;	/* Bye */
		else if (priv->surpriseremoved)
			shouldsleep = 1;	/* We need to wait until we're _told_ to die */
		else if (priv->psstate == PS_STATE_SLEEP)
			shouldsleep = 1;	/* Sleep mode. Nothing we can do till it wakes */
		else if (priv->cmd_timed_out)
			shouldsleep = 0;	/* Command timed out. Recover */
		else if (!priv->fw_ready)
			shouldsleep = 1;	/* Firmware not ready. We're waiting for it */
		else if (priv->dnld_sent)
			shouldsleep = 1;	/* Something is en route to the device already */
		else if (priv->tx_pending_len > 0)
			shouldsleep = 0;	/* We've a packet to send */
		else if (priv->resp_len[priv->resp_idx])
			shouldsleep = 0;	/* We have a command response */
		else if (priv->cur_cmd)
			shouldsleep = 1;	/* Can't send a command; one already running */
		else if (!list_empty(&priv->cmdpendingq) &&
					!(priv->wakeup_dev_required))
			shouldsleep = 0;	/* We have a command to send */
		else if (kfifo_len(&priv->event_fifo))
			shouldsleep = 0;	/* We have an event to process */
		else
			shouldsleep = 1;	/* No command */

		if (shouldsleep) {
			lbs_deb_thread("sleeping, connect_status %d, "
				"psmode %d, psstate %d\n",
				priv->connect_status,
				priv->psmode, priv->psstate);
			spin_unlock_irq(&priv->driver_lock);
			schedule();
		} else
			spin_unlock_irq(&priv->driver_lock);

		lbs_deb_thread("2: currenttxskb %p, dnld_send %d\n",
			       priv->currenttxskb, priv->dnld_sent);

		set_current_state(TASK_RUNNING);
		remove_wait_queue(&priv->waitq, &wait);

		lbs_deb_thread("3: currenttxskb %p, dnld_sent %d\n",
			       priv->currenttxskb, priv->dnld_sent);

		if (kthread_should_stop()) {
			lbs_deb_thread("break from main thread\n");
			break;
		}

		if (priv->surpriseremoved) {
			lbs_deb_thread("adapter removed; waiting to die...\n");
			continue;
		}

		lbs_deb_thread("4: currenttxskb %p, dnld_sent %d\n",
		       priv->currenttxskb, priv->dnld_sent);

		/* Process any pending command response */
		spin_lock_irq(&priv->driver_lock);
		resp_idx = priv->resp_idx;
		if (priv->resp_len[resp_idx]) {
			spin_unlock_irq(&priv->driver_lock);
			lbs_process_command_response(priv,
				priv->resp_buf[resp_idx],
				priv->resp_len[resp_idx]);
			spin_lock_irq(&priv->driver_lock);
			priv->resp_len[resp_idx] = 0;
		}
		spin_unlock_irq(&priv->driver_lock);

		/* Process hardware events, e.g. card removed, link lost */
		spin_lock_irq(&priv->driver_lock);
		while (kfifo_len(&priv->event_fifo)) {
			u32 event;

			if (kfifo_out(&priv->event_fifo,
				(unsigned char *) &event, sizeof(event)) !=
				sizeof(event))
					break;
			spin_unlock_irq(&priv->driver_lock);
			lbs_process_event(priv, event);
			spin_lock_irq(&priv->driver_lock);
		}
		spin_unlock_irq(&priv->driver_lock);

		if (priv->wakeup_dev_required) {
			lbs_deb_thread("Waking up device...\n");
			/* Wake up device */
			if (priv->exit_deep_sleep(priv))
				lbs_deb_thread("Wakeup device failed\n");
			continue;
		}

		/* command timeout stuff */
		if (priv->cmd_timed_out && priv->cur_cmd) {
			struct cmd_ctrl_node *cmdnode = priv->cur_cmd;

			netdev_info(dev, "Timeout submitting command 0x%04x\n",
				    le16_to_cpu(cmdnode->cmdbuf->command));
			lbs_complete_command(priv, cmdnode, -ETIMEDOUT);

			/* Reset card, but only when it isn't in the process
			 * of being shutdown anyway. */
			if (!dev->dismantle && priv->reset_card)
				priv->reset_card(priv);
		}
		priv->cmd_timed_out = 0;

		if (!priv->fw_ready)
			continue;

		/* Check if we need to confirm Sleep Request received previously */
		if (priv->psstate == PS_STATE_PRE_SLEEP &&
		    !priv->dnld_sent && !priv->cur_cmd) {
			if (priv->connect_status == LBS_CONNECTED) {
				lbs_deb_thread("pre-sleep, currenttxskb %p, "
					"dnld_sent %d, cur_cmd %p\n",
					priv->currenttxskb, priv->dnld_sent,
					priv->cur_cmd);

				lbs_ps_confirm_sleep(priv);
			} else {
				/* workaround for firmware sending
				 * deauth/linkloss event immediately
				 * after sleep request; remove this
				 * after firmware fixes it
				 */
				priv->psstate = PS_STATE_AWAKE;
				netdev_alert(dev,
					     "ignore PS_SleepConfirm in non-connected state\n");
			}
		}

		/* The PS state is changed during processing of Sleep Request
		 * event above
		 */
		if ((priv->psstate == PS_STATE_SLEEP) ||
		    (priv->psstate == PS_STATE_PRE_SLEEP))
			continue;

		if (priv->is_deep_sleep)
			continue;

		/* Execute the next command */
		if (!priv->dnld_sent && !priv->cur_cmd)
			lbs_execute_next_command(priv);

		spin_lock_irq(&priv->driver_lock);
		if (!priv->dnld_sent && priv->tx_pending_len > 0) {
			int ret = priv->hw_host_to_card(priv, MVMS_DAT,
							priv->tx_pending_buf,
							priv->tx_pending_len);
			if (ret) {
				lbs_deb_tx("host_to_card failed %d\n", ret);
				priv->dnld_sent = DNLD_RES_RECEIVED;
			} else {
				mod_timer(&priv->tx_lockup_timer,
					  jiffies + (HZ * 5));
			}
			priv->tx_pending_len = 0;
			if (!priv->currenttxskb) {
				/* We can wake the queues immediately if we aren't
				   waiting for TX feedback */
				if (priv->connect_status == LBS_CONNECTED)
					netif_wake_queue(priv->dev);
				if (priv->mesh_dev &&
				    netif_running(priv->mesh_dev))
					netif_wake_queue(priv->mesh_dev);
			}
		}
		spin_unlock_irq(&priv->driver_lock);
	}

	del_timer(&priv->command_timer);
	del_timer(&priv->tx_lockup_timer);
	del_timer(&priv->auto_deepsleep_timer);

	return 0;
}