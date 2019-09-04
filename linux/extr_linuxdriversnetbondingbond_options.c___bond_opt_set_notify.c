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
struct bonding {TYPE_1__* dev; } ;
struct bond_opt_value {int dummy; } ;
struct TYPE_2__ {scalar_t__ reg_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int ENOENT ; 
 int /*<<< orphan*/  NETDEV_CHANGEINFODATA ; 
 scalar_t__ NETREG_REGISTERED ; 
 int __bond_opt_set (struct bonding*,unsigned int,struct bond_opt_value*) ; 
 int /*<<< orphan*/  call_netdevice_notifiers (int /*<<< orphan*/ ,TYPE_1__*) ; 

int __bond_opt_set_notify(struct bonding *bond,
			  unsigned int option, struct bond_opt_value *val)
{
	int ret = -ENOENT;

	ASSERT_RTNL();

	ret = __bond_opt_set(bond, option, val);

	if (!ret && (bond->dev->reg_state == NETREG_REGISTERED))
		call_netdevice_notifiers(NETDEV_CHANGEINFODATA, bond->dev);

	return ret;
}