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
struct netdevsim {int dummy; } ;
struct net_device {int dummy; } ;
typedef  enum tc_setup_type { ____Placeholder_tc_setup_type } tc_setup_type ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  TC_SETUP_BLOCK 128 
 int flow_block_cb_setup_simple (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct netdevsim*,struct netdevsim*,int) ; 
 struct netdevsim* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nsim_block_cb_list ; 
 int /*<<< orphan*/  nsim_setup_tc_block_cb ; 

__attribute__((used)) static int
nsim_setup_tc(struct net_device *dev, enum tc_setup_type type, void *type_data)
{
	struct netdevsim *ns = netdev_priv(dev);

	switch (type) {
	case TC_SETUP_BLOCK:
		return flow_block_cb_setup_simple(type_data,
						  &nsim_block_cb_list,
						  nsim_setup_tc_block_cb,
						  ns, ns, true);
	default:
		return -EOPNOTSUPP;
	}
}