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
struct sk_buff {scalar_t__ len; } ;
struct ntb_transport_qp {int dummy; } ;
struct ntb_netdev {int /*<<< orphan*/  qp; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_aborted_errors; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 struct ntb_netdev* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 scalar_t__ ntb_transport_tx_free_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 
 scalar_t__ tx_start ; 

__attribute__((used)) static void ntb_netdev_tx_handler(struct ntb_transport_qp *qp, void *qp_data,
				  void *data, int len)
{
	struct net_device *ndev = qp_data;
	struct sk_buff *skb;
	struct ntb_netdev *dev = netdev_priv(ndev);

	skb = data;
	if (!skb || !ndev)
		return;

	if (len > 0) {
		ndev->stats.tx_packets++;
		ndev->stats.tx_bytes += skb->len;
	} else {
		ndev->stats.tx_errors++;
		ndev->stats.tx_aborted_errors++;
	}

	dev_kfree_skb(skb);

	if (ntb_transport_tx_free_entry(dev->qp) >= tx_start) {
		/* Make sure anybody stopping the queue after this sees the new
		 * value of ntb_transport_tx_free_entry()
		 */
		smp_mb();
		if (netif_queue_stopped(ndev))
			netif_wake_queue(ndev);
	}
}