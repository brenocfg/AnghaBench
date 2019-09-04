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
struct net_device {int dummy; } ;
struct can_berr_counter {int dummy; } ;
struct c_can_priv {int dummy; } ;

/* Variables and functions */
 int __c_can_get_berr_counter (struct net_device const*,struct can_berr_counter*) ; 
 int /*<<< orphan*/  c_can_pm_runtime_get_sync (struct c_can_priv*) ; 
 int /*<<< orphan*/  c_can_pm_runtime_put_sync (struct c_can_priv*) ; 
 struct c_can_priv* netdev_priv (struct net_device const*) ; 

__attribute__((used)) static int c_can_get_berr_counter(const struct net_device *dev,
				  struct can_berr_counter *bec)
{
	struct c_can_priv *priv = netdev_priv(dev);
	int err;

	c_can_pm_runtime_get_sync(priv);
	err = __c_can_get_berr_counter(dev, bec);
	c_can_pm_runtime_put_sync(priv);

	return err;
}