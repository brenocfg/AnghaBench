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
struct timer_list {int dummy; } ;
struct qca_data {int tx_ibs_state; int /*<<< orphan*/  hci_ibs_lock; int /*<<< orphan*/  ws_tx_vote_off; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  ibs_sent_slps; struct hci_uart* hu; } ;
struct hci_uart {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_uart*,int) ; 
 int /*<<< orphan*/  BT_ERR (char*,...) ; 
 int /*<<< orphan*/  HCI_IBS_SLEEP_IND ; 
#define  HCI_IBS_TX_ASLEEP 130 
#define  HCI_IBS_TX_AWAKE 129 
#define  HCI_IBS_TX_WAKING 128 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 struct qca_data* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct qca_data* qca ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_hci_ibs_cmd (int /*<<< orphan*/ ,struct hci_uart*) ; 
 int /*<<< orphan*/  spin_lock_irqsave_nested (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tx_idle_timer ; 

__attribute__((used)) static void hci_ibs_tx_idle_timeout(struct timer_list *t)
{
	struct qca_data *qca = from_timer(qca, t, tx_idle_timer);
	struct hci_uart *hu = qca->hu;
	unsigned long flags;

	BT_DBG("hu %p idle timeout in %d state", hu, qca->tx_ibs_state);

	spin_lock_irqsave_nested(&qca->hci_ibs_lock,
				 flags, SINGLE_DEPTH_NESTING);

	switch (qca->tx_ibs_state) {
	case HCI_IBS_TX_AWAKE:
		/* TX_IDLE, go to SLEEP */
		if (send_hci_ibs_cmd(HCI_IBS_SLEEP_IND, hu) < 0) {
			BT_ERR("Failed to send SLEEP to device");
			break;
		}
		qca->tx_ibs_state = HCI_IBS_TX_ASLEEP;
		qca->ibs_sent_slps++;
		queue_work(qca->workqueue, &qca->ws_tx_vote_off);
		break;

	case HCI_IBS_TX_ASLEEP:
	case HCI_IBS_TX_WAKING:
		/* Fall through */

	default:
		BT_ERR("Spurious timeout tx state %d", qca->tx_ibs_state);
		break;
	}

	spin_unlock_irqrestore(&qca->hci_ibs_lock, flags);
}