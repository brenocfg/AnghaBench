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
struct sky2_port {scalar_t__ wol; } ;
struct sky2_hw {int ports; struct net_device** dev; int /*<<< orphan*/  restart_work; int /*<<< orphan*/  watchdog_timer; } ;
struct net_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct sky2_hw* dev_get_drvdata (struct device*) ; 
 struct sky2_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  sky2_all_down (struct sky2_hw*) ; 
 int /*<<< orphan*/  sky2_power_aux (struct sky2_hw*) ; 
 int /*<<< orphan*/  sky2_wol_init (struct sky2_port*) ; 

__attribute__((used)) static int sky2_suspend(struct device *dev)
{
	struct sky2_hw *hw = dev_get_drvdata(dev);
	int i;

	if (!hw)
		return 0;

	del_timer_sync(&hw->watchdog_timer);
	cancel_work_sync(&hw->restart_work);

	rtnl_lock();

	sky2_all_down(hw);
	for (i = 0; i < hw->ports; i++) {
		struct net_device *dev = hw->dev[i];
		struct sky2_port *sky2 = netdev_priv(dev);

		if (sky2->wol)
			sky2_wol_init(sky2);
	}

	sky2_power_aux(hw);
	rtnl_unlock();

	return 0;
}