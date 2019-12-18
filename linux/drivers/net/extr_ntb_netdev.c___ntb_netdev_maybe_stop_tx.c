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
struct ntb_transport_qp {int dummy; } ;
struct ntb_netdev {int /*<<< orphan*/  tx_timer; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ jiffies ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct ntb_netdev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int ntb_transport_tx_free_entry (struct ntb_transport_qp*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  tx_time ; 
 scalar_t__ usecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __ntb_netdev_maybe_stop_tx(struct net_device *netdev,
				      struct ntb_transport_qp *qp, int size)
{
	struct ntb_netdev *dev = netdev_priv(netdev);

	netif_stop_queue(netdev);
	/* Make sure to see the latest value of ntb_transport_tx_free_entry()
	 * since the queue was last started.
	 */
	smp_mb();

	if (likely(ntb_transport_tx_free_entry(qp) < size)) {
		mod_timer(&dev->tx_timer, jiffies + usecs_to_jiffies(tx_time));
		return -EBUSY;
	}

	netif_start_queue(netdev);
	return 0;
}