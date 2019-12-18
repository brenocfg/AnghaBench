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
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  owner; int /*<<< orphan*/  (* close ) (struct net_device*) ;int /*<<< orphan*/  (* command ) (struct net_device*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* intmask ) (struct net_device*,int /*<<< orphan*/ ) ;} ;
struct arcnet_local {TYPE_1__ hw; int /*<<< orphan*/  reply_tasklet; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCNET_LED_EVENT_STOP ; 
 int /*<<< orphan*/  NORXcmd ; 
 int /*<<< orphan*/  NOTXcmd ; 
 int /*<<< orphan*/  arcnet_led_event (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 struct arcnet_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct net_device*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

int arcnet_close(struct net_device *dev)
{
	struct arcnet_local *lp = netdev_priv(dev);

	arcnet_led_event(dev, ARCNET_LED_EVENT_STOP);
	del_timer_sync(&lp->timer);

	netif_stop_queue(dev);
	netif_carrier_off(dev);

	tasklet_kill(&lp->reply_tasklet);

	/* flush TX and disable RX */
	lp->hw.intmask(dev, 0);
	lp->hw.command(dev, NOTXcmd);	/* stop transmit */
	lp->hw.command(dev, NORXcmd);	/* disable receive */
	mdelay(1);

	/* shut down the card */
	lp->hw.close(dev);
	module_put(lp->hw.owner);
	return 0;
}