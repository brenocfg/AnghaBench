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
struct qca_serdev {scalar_t__ btsoc_type; int /*<<< orphan*/  oper_speed; int /*<<< orphan*/  init_speed; int /*<<< orphan*/  bt_en; } ;
struct qca_data {int tx_vote; int rx_vote; int /*<<< orphan*/  wake_retrans; int /*<<< orphan*/  tx_idle_delay; int /*<<< orphan*/  tx_idle_timer; int /*<<< orphan*/  wake_retrans_timer; int /*<<< orphan*/  rx_skb; int /*<<< orphan*/  workqueue; scalar_t__ rx_votes_off; scalar_t__ rx_votes_on; scalar_t__ tx_votes_off; scalar_t__ tx_votes_on; scalar_t__ votes_off; scalar_t__ votes_on; scalar_t__ vote_off_ms; scalar_t__ vote_on_ms; int /*<<< orphan*/  vote_last_jif; scalar_t__ ibs_recv_wakes; scalar_t__ ibs_recv_slps; scalar_t__ ibs_recv_wacks; scalar_t__ ibs_sent_wakes; scalar_t__ ibs_sent_slps; scalar_t__ ibs_sent_wacks; scalar_t__ flags; int /*<<< orphan*/  rx_ibs_state; int /*<<< orphan*/  tx_ibs_state; struct hci_uart* hu; int /*<<< orphan*/  ws_tx_vote_off; int /*<<< orphan*/  ws_rx_vote_off; int /*<<< orphan*/  ws_awake_device; int /*<<< orphan*/  ws_awake_rx; int /*<<< orphan*/  hci_ibs_lock; int /*<<< orphan*/  tx_wait_q; int /*<<< orphan*/  txq; } ;
struct hci_uart {struct qca_data* priv; int /*<<< orphan*/  oper_speed; int /*<<< orphan*/  init_speed; scalar_t__ serdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_uart*,...) ; 
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HCI_IBS_RX_ASLEEP ; 
 int /*<<< orphan*/  HCI_IBS_TX_ASLEEP ; 
 int /*<<< orphan*/  IBS_TX_IDLE_TIMEOUT_MS ; 
 int /*<<< orphan*/  IBS_WAKE_RETRANS_TIMEOUT_MS ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ QCA_WCN3990 ; 
 int /*<<< orphan*/  alloc_ordered_workqueue (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hci_ibs_tx_idle_timeout ; 
 int /*<<< orphan*/  hci_ibs_wake_retrans_timeout ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kfree (struct qca_data*) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 
 struct qca_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int qca_power_setup (struct hci_uart*,int) ; 
 int /*<<< orphan*/  qca_wq_awake_device ; 
 int /*<<< orphan*/  qca_wq_awake_rx ; 
 int /*<<< orphan*/  qca_wq_serial_rx_clock_vote_off ; 
 int /*<<< orphan*/  qca_wq_serial_tx_clock_vote_off ; 
 struct qca_serdev* serdev_device_get_drvdata (scalar_t__) ; 
 int /*<<< orphan*/  serdev_device_open (scalar_t__) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qca_open(struct hci_uart *hu)
{
	struct qca_serdev *qcadev;
	struct qca_data *qca;
	int ret;

	BT_DBG("hu %p qca_open", hu);

	qca = kzalloc(sizeof(struct qca_data), GFP_KERNEL);
	if (!qca)
		return -ENOMEM;

	skb_queue_head_init(&qca->txq);
	skb_queue_head_init(&qca->tx_wait_q);
	spin_lock_init(&qca->hci_ibs_lock);
	qca->workqueue = alloc_ordered_workqueue("qca_wq", 0);
	if (!qca->workqueue) {
		BT_ERR("QCA Workqueue not initialized properly");
		kfree(qca);
		return -ENOMEM;
	}

	INIT_WORK(&qca->ws_awake_rx, qca_wq_awake_rx);
	INIT_WORK(&qca->ws_awake_device, qca_wq_awake_device);
	INIT_WORK(&qca->ws_rx_vote_off, qca_wq_serial_rx_clock_vote_off);
	INIT_WORK(&qca->ws_tx_vote_off, qca_wq_serial_tx_clock_vote_off);

	qca->hu = hu;

	/* Assume we start with both sides asleep -- extra wakes OK */
	qca->tx_ibs_state = HCI_IBS_TX_ASLEEP;
	qca->rx_ibs_state = HCI_IBS_RX_ASLEEP;

	/* clocks actually on, but we start votes off */
	qca->tx_vote = false;
	qca->rx_vote = false;
	qca->flags = 0;

	qca->ibs_sent_wacks = 0;
	qca->ibs_sent_slps = 0;
	qca->ibs_sent_wakes = 0;
	qca->ibs_recv_wacks = 0;
	qca->ibs_recv_slps = 0;
	qca->ibs_recv_wakes = 0;
	qca->vote_last_jif = jiffies;
	qca->vote_on_ms = 0;
	qca->vote_off_ms = 0;
	qca->votes_on = 0;
	qca->votes_off = 0;
	qca->tx_votes_on = 0;
	qca->tx_votes_off = 0;
	qca->rx_votes_on = 0;
	qca->rx_votes_off = 0;

	hu->priv = qca;

	if (hu->serdev) {
		serdev_device_open(hu->serdev);

		qcadev = serdev_device_get_drvdata(hu->serdev);
		if (qcadev->btsoc_type != QCA_WCN3990) {
			gpiod_set_value_cansleep(qcadev->bt_en, 1);
		} else {
			hu->init_speed = qcadev->init_speed;
			hu->oper_speed = qcadev->oper_speed;
			ret = qca_power_setup(hu, true);
			if (ret) {
				destroy_workqueue(qca->workqueue);
				kfree_skb(qca->rx_skb);
				hu->priv = NULL;
				kfree(qca);
				return ret;
			}
		}
	}

	timer_setup(&qca->wake_retrans_timer, hci_ibs_wake_retrans_timeout, 0);
	qca->wake_retrans = IBS_WAKE_RETRANS_TIMEOUT_MS;

	timer_setup(&qca->tx_idle_timer, hci_ibs_tx_idle_timeout, 0);
	qca->tx_idle_delay = IBS_TX_IDLE_TIMEOUT_MS;

	BT_DBG("HCI_UART_QCA open, tx_idle_delay=%u, wake_retrans=%u",
	       qca->tx_idle_delay, qca->wake_retrans);

	return 0;
}