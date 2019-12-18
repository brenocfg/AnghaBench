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
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ state; } ;
struct m_can_classdev {struct sk_buff* tx_skb; int /*<<< orphan*/  tx_work; int /*<<< orphan*/  tx_wq; int /*<<< orphan*/  net; TYPE_1__ can; scalar_t__ is_peripheral; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 scalar_t__ CAN_STATE_BUS_OFF ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 scalar_t__ can_dropped_invalid_skb (struct net_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  m_can_clean (struct net_device*) ; 
 int /*<<< orphan*/  m_can_tx_handler (struct m_can_classdev*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct m_can_classdev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static netdev_tx_t m_can_start_xmit(struct sk_buff *skb,
				    struct net_device *dev)
{
	struct m_can_classdev *cdev = netdev_priv(dev);

	if (can_dropped_invalid_skb(dev, skb))
		return NETDEV_TX_OK;

	if (cdev->is_peripheral) {
		if (cdev->tx_skb) {
			netdev_err(dev, "hard_xmit called while tx busy\n");
			return NETDEV_TX_BUSY;
		}

		if (cdev->can.state == CAN_STATE_BUS_OFF) {
			m_can_clean(dev);
		} else {
			/* Need to stop the queue to avoid numerous requests
			 * from being sent.  Suggested improvement is to create
			 * a queueing mechanism that will queue the skbs and
			 * process them in order.
			 */
			cdev->tx_skb = skb;
			netif_stop_queue(cdev->net);
			queue_work(cdev->tx_wq, &cdev->tx_work);
		}
	} else {
		cdev->tx_skb = skb;
		return m_can_tx_handler(cdev);
	}

	return NETDEV_TX_OK;
}