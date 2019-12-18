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
struct c_can_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  c_can_pm_runtime_disable (struct c_can_priv*) ; 
 struct c_can_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  unregister_candev (struct net_device*) ; 

void unregister_c_can_dev(struct net_device *dev)
{
	struct c_can_priv *priv = netdev_priv(dev);

	unregister_candev(dev);

	c_can_pm_runtime_disable(priv);
}