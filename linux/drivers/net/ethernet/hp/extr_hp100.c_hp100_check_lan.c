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
struct net_device {int /*<<< orphan*/  name; } ;
struct hp100_private {scalar_t__ lan_type; int /*<<< orphan*/  hub_status; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ HP100_LAN_100 ; 
 int /*<<< orphan*/  hp100_login_to_vg_hub (struct net_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ hp100_sense_lan (struct net_device*) ; 
 int /*<<< orphan*/  hp100_start_interface (struct net_device*) ; 
 int /*<<< orphan*/  hp100_stop_interface (struct net_device*) ; 
 struct hp100_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hp100_check_lan(struct net_device *dev)
{
	struct hp100_private *lp = netdev_priv(dev);

	if (lp->lan_type < 0) {	/* no LAN type detected yet? */
		hp100_stop_interface(dev);
		if ((lp->lan_type = hp100_sense_lan(dev)) < 0) {
			printk("hp100: %s: no connection found - check wire\n", dev->name);
			hp100_start_interface(dev);	/* 10Mb/s RX packets maybe handled */
			return -EIO;
		}
		if (lp->lan_type == HP100_LAN_100)
			lp->hub_status = hp100_login_to_vg_hub(dev, 0);	/* relogin */
		hp100_start_interface(dev);
	}
	return 0;
}