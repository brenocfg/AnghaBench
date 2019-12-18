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
struct net_device {scalar_t__ type; int /*<<< orphan*/ * rtnl_link_ops; } ;
struct can_priv {int dummy; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_CAN ; 
 int /*<<< orphan*/  can_link_ops ; 
 struct can_priv* netdev_priv (struct net_device*) ; 

struct can_priv *safe_candev_priv(struct net_device *dev)
{
	if (dev->type != ARPHRD_CAN || dev->rtnl_link_ops != &can_link_ops)
		return NULL;

	return netdev_priv(dev);
}