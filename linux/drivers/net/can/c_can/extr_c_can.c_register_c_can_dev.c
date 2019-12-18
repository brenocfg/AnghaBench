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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct net_device {int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  flags; TYPE_1__ dev; } ;
struct c_can_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_ECHO ; 
 int /*<<< orphan*/  c_can_netdev_ops ; 
 int /*<<< orphan*/  c_can_pm_runtime_disable (struct c_can_priv*) ; 
 int /*<<< orphan*/  c_can_pm_runtime_enable (struct c_can_priv*) ; 
 int /*<<< orphan*/  devm_can_led_init (struct net_device*) ; 
 struct c_can_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pinctrl_pm_select_sleep_state (int /*<<< orphan*/ ) ; 
 int register_candev (struct net_device*) ; 

int register_c_can_dev(struct net_device *dev)
{
	struct c_can_priv *priv = netdev_priv(dev);
	int err;

	/* Deactivate pins to prevent DRA7 DCAN IP from being
	 * stuck in transition when module is disabled.
	 * Pins are activated in c_can_start() and deactivated
	 * in c_can_stop()
	 */
	pinctrl_pm_select_sleep_state(dev->dev.parent);

	c_can_pm_runtime_enable(priv);

	dev->flags |= IFF_ECHO;	/* we support local echo */
	dev->netdev_ops = &c_can_netdev_ops;

	err = register_candev(dev);
	if (err)
		c_can_pm_runtime_disable(priv);
	else
		devm_can_led_init(dev);

	return err;
}