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
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_1__ dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
struct c_can_priv {TYPE_2__ can; int /*<<< orphan*/  (* write_reg ) (struct c_can_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_STATE_STOPPED ; 
 int /*<<< orphan*/  CONTROL_INIT ; 
 int /*<<< orphan*/  C_CAN_CTRL_REG ; 
 int /*<<< orphan*/  c_can_irq_control (struct c_can_priv*,int) ; 
 struct c_can_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pinctrl_pm_select_sleep_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct c_can_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void c_can_stop(struct net_device *dev)
{
	struct c_can_priv *priv = netdev_priv(dev);

	c_can_irq_control(priv, false);

	/* put ctrl to init on stop to end ongoing transmission */
	priv->write_reg(priv, C_CAN_CTRL_REG, CONTROL_INIT);

	/* deactivate pins */
	pinctrl_pm_select_sleep_state(dev->dev.parent);
	priv->can.state = CAN_STATE_STOPPED;
}