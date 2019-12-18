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
typedef  int /*<<< orphan*/  u64 ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;
struct devlink {int dummy; } ;
typedef  enum nsim_resource_id { ____Placeholder_nsim_resource_id } nsim_resource_id ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int NSIM_RESOURCE_IPV4_FIB ; 
 int NSIM_RESOURCE_IPV4_FIB_RULES ; 
 int NSIM_RESOURCE_IPV6_FIB ; 
 int NSIM_RESOURCE_IPV6_FIB_RULES ; 
 int devlink_resource_size_get (struct devlink*,int,int /*<<< orphan*/ *) ; 
 struct net* nsim_devlink_net (struct devlink*) ; 
 int /*<<< orphan*/  nsim_devlink_param_load_driverinit_values (struct devlink*) ; 
 int nsim_fib_set_max (struct net*,int,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 

__attribute__((used)) static int nsim_dev_reload_up(struct devlink *devlink,
			      struct netlink_ext_ack *extack)
{
	enum nsim_resource_id res_ids[] = {
		NSIM_RESOURCE_IPV4_FIB, NSIM_RESOURCE_IPV4_FIB_RULES,
		NSIM_RESOURCE_IPV6_FIB, NSIM_RESOURCE_IPV6_FIB_RULES
	};
	struct net *net = nsim_devlink_net(devlink);
	int i;

	for (i = 0; i < ARRAY_SIZE(res_ids); ++i) {
		int err;
		u64 val;

		err = devlink_resource_size_get(devlink, res_ids[i], &val);
		if (!err) {
			err = nsim_fib_set_max(net, res_ids[i], val, extack);
			if (err)
				return err;
		}
	}
	nsim_devlink_param_load_driverinit_values(devlink);

	return 0;
}