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
struct TYPE_2__ {int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_packets; } ;
struct net_device {TYPE_1__ stats; scalar_t__ phydev; } ;
struct lan78xx_net {int /*<<< orphan*/  intf; int /*<<< orphan*/  bh; int /*<<< orphan*/  wq; scalar_t__ flags; int /*<<< orphan*/  rxq_pause; int /*<<< orphan*/  urb_intr; int /*<<< orphan*/  net; int /*<<< orphan*/  stat_monitor; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_DEV_OPEN ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifdown ; 
 int /*<<< orphan*/  lan78xx_terminate_urbs (struct lan78xx_net*) ; 
 struct lan78xx_net* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_info (struct lan78xx_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_stop (scalar_t__) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lan78xx_stop(struct net_device *net)
{
	struct lan78xx_net *dev = netdev_priv(net);

	if (timer_pending(&dev->stat_monitor))
		del_timer_sync(&dev->stat_monitor);

	if (net->phydev)
		phy_stop(net->phydev);

	clear_bit(EVENT_DEV_OPEN, &dev->flags);
	netif_stop_queue(net);

	netif_info(dev, ifdown, dev->net,
		   "stop stats: rx/tx %lu/%lu, errs %lu/%lu\n",
		   net->stats.rx_packets, net->stats.tx_packets,
		   net->stats.rx_errors, net->stats.tx_errors);

	lan78xx_terminate_urbs(dev);

	usb_kill_urb(dev->urb_intr);

	skb_queue_purge(&dev->rxq_pause);

	/* deferred work (task, timer, softirq) must also stop.
	 * can't flush_scheduled_work() until we drop rtnl (later),
	 * else workers could deadlock; so make workers a NOP.
	 */
	dev->flags = 0;
	cancel_delayed_work_sync(&dev->wq);
	tasklet_kill(&dev->bh);

	usb_autopm_put_interface(dev->intf);

	return 0;
}