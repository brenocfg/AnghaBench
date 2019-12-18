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
struct net_device_ops {int (* ndo_fcoe_get_wwn ) (struct net_device*,int /*<<< orphan*/ *,int) ;} ;
struct net_device {struct net_device_ops* netdev_ops; } ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (struct net_device*,int /*<<< orphan*/ *,int) ; 

int fcoe_get_wwn(struct net_device *netdev, u64 *wwn, int type)
{
	const struct net_device_ops *ops = netdev->netdev_ops;

	if (ops->ndo_fcoe_get_wwn)
		return ops->ndo_fcoe_get_wwn(netdev, wwn, type);
	return -EINVAL;
}