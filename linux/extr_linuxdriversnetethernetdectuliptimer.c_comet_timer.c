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
struct tulip_private {int /*<<< orphan*/  timer; int /*<<< orphan*/ * phys; struct net_device* dev; } ;
struct timer_list {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  RUN_AT (int) ; 
 struct tulip_private* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  timer ; 
 struct tulip_private* tp ; 
 scalar_t__ tulip_check_duplex (struct net_device*) ; 
 int tulip_debug ; 
 int /*<<< orphan*/  tulip_mdio_read (struct net_device*,int /*<<< orphan*/ ,int) ; 

void comet_timer(struct timer_list *t)
{
	struct tulip_private *tp = from_timer(tp, t, timer);
	struct net_device *dev = tp->dev;
	int next_tick = 2*HZ;

	if (tulip_debug > 1)
		netdev_dbg(dev, "Comet link status %04x partner capability %04x\n",
			   tulip_mdio_read(dev, tp->phys[0], 1),
			   tulip_mdio_read(dev, tp->phys[0], 5));
	/* mod_timer synchronizes us with potential add_timer calls
	 * from interrupts.
	 */
	if (tulip_check_duplex(dev) < 0)
		{ netif_carrier_off(dev); }
	else
		{ netif_carrier_on(dev); }
	mod_timer(&tp->timer, RUN_AT(next_tick));
}