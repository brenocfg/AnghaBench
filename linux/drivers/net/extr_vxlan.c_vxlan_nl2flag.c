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
struct vxlan_config {unsigned long flags; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ NLA_FLAG ; 
 scalar_t__ nla_get_u8 (struct nlattr*) ; 
 int /*<<< orphan*/  vxlan_flag_attr_error (int,struct netlink_ext_ack*) ; 
 TYPE_1__* vxlan_policy ; 

__attribute__((used)) static int vxlan_nl2flag(struct vxlan_config *conf, struct nlattr *tb[],
			  int attrtype, unsigned long mask, bool changelink,
			  bool changelink_supported,
			  struct netlink_ext_ack *extack)
{
	unsigned long flags;

	if (!tb[attrtype])
		return 0;

	if (changelink && !changelink_supported) {
		vxlan_flag_attr_error(attrtype, extack);
		return -EOPNOTSUPP;
	}

	if (vxlan_policy[attrtype].type == NLA_FLAG)
		flags = conf->flags | mask;
	else if (nla_get_u8(tb[attrtype]))
		flags = conf->flags | mask;
	else
		flags = conf->flags & ~mask;

	conf->flags = flags;

	return 0;
}