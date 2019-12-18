#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  rules; } ;
struct TYPE_3__ {int /*<<< orphan*/  rules; } ;
struct nsim_fib_data {TYPE_2__ ipv6; TYPE_1__ ipv4; } ;
struct netlink_ext_ack {int dummy; } ;
struct fib_notifier_info {int family; struct netlink_ext_ack* extack; int /*<<< orphan*/  net; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 struct nsim_fib_data* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsim_fib_net_id ; 
 int nsim_fib_rule_account (int /*<<< orphan*/ *,int,struct netlink_ext_ack*) ; 

__attribute__((used)) static int nsim_fib_rule_event(struct fib_notifier_info *info, bool add)
{
	struct nsim_fib_data *data = net_generic(info->net, nsim_fib_net_id);
	struct netlink_ext_ack *extack = info->extack;
	int err = 0;

	switch (info->family) {
	case AF_INET:
		err = nsim_fib_rule_account(&data->ipv4.rules, add, extack);
		break;
	case AF_INET6:
		err = nsim_fib_rule_account(&data->ipv6.rules, add, extack);
		break;
	}

	return err;
}