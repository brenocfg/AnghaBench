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
struct ntb_netdev {int /*<<< orphan*/  tx_timer; int /*<<< orphan*/  qp; struct net_device* ndev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct ntb_netdev* dev ; 
 struct ntb_netdev* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 scalar_t__ ntb_transport_tx_free_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 
 scalar_t__ tx_stop ; 
 int /*<<< orphan*/  tx_time ; 
 int /*<<< orphan*/  tx_timer ; 
 scalar_t__ usecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ntb_netdev_tx_timer(struct timer_list *t)
{
	struct ntb_netdev *dev = from_timer(dev, t, tx_timer);
	struct net_device *ndev = dev->ndev;

	if (ntb_transport_tx_free_entry(dev->qp) < tx_stop) {
		mod_timer(&dev->tx_timer, jiffies + usecs_to_jiffies(tx_time));
	} else {
		/* Make sure anybody stopping the queue after this sees the new
		 * value of ntb_transport_tx_free_entry()
		 */
		smp_mb();
		if (netif_queue_stopped(ndev))
			netif_wake_queue(ndev);
	}
}