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
struct rtnl_link_ops {int /*<<< orphan*/  maxtype; int /*<<< orphan*/  changelink; int /*<<< orphan*/  fill_info; int /*<<< orphan*/  validate; int /*<<< orphan*/  policy; int /*<<< orphan*/  get_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFLA_IPVLAN_MAX ; 
 int /*<<< orphan*/  ipvlan_nl_changelink ; 
 int /*<<< orphan*/  ipvlan_nl_fillinfo ; 
 int /*<<< orphan*/  ipvlan_nl_getsize ; 
 int /*<<< orphan*/  ipvlan_nl_policy ; 
 int /*<<< orphan*/  ipvlan_nl_validate ; 
 int rtnl_link_register (struct rtnl_link_ops*) ; 

int ipvlan_link_register(struct rtnl_link_ops *ops)
{
	ops->get_size	= ipvlan_nl_getsize;
	ops->policy	= ipvlan_nl_policy;
	ops->validate	= ipvlan_nl_validate;
	ops->fill_info	= ipvlan_nl_fillinfo;
	ops->changelink = ipvlan_nl_changelink;
	ops->maxtype	= IFLA_IPVLAN_MAX;
	return rtnl_link_register(ops);
}