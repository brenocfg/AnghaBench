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
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 

__attribute__((used)) static int nsim_validate(struct nlattr *tb[], struct nlattr *data[],
			 struct netlink_ext_ack *extack)
{
	NL_SET_ERR_MSG_MOD(extack, "Please use: echo \"[ID] [PORT_COUNT]\" > /sys/bus/netdevsim/new_device");
	return -EOPNOTSUPP;
}