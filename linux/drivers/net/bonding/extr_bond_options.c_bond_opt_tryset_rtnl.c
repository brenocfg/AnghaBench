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
struct bonding {int dummy; } ;
struct bond_opt_value {int dummy; } ;

/* Variables and functions */
 int __bond_opt_set_notify (struct bonding*,unsigned int,struct bond_opt_value*) ; 
 int /*<<< orphan*/  bond_opt_initstr (struct bond_opt_value*,char*) ; 
 int restart_syscall () ; 
 int /*<<< orphan*/  rtnl_trylock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

int bond_opt_tryset_rtnl(struct bonding *bond, unsigned int option, char *buf)
{
	struct bond_opt_value optval;
	int ret;

	if (!rtnl_trylock())
		return restart_syscall();
	bond_opt_initstr(&optval, buf);
	ret = __bond_opt_set_notify(bond, option, &optval);
	rtnl_unlock();

	return ret;
}