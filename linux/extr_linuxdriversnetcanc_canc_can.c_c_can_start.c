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
struct pinctrl {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct c_can_priv {scalar_t__ type; int /*<<< orphan*/  device; TYPE_1__ can; int /*<<< orphan*/  comm_rcv_high; } ;

/* Variables and functions */
 scalar_t__ BOSCH_D_CAN ; 
 int /*<<< orphan*/  CAN_STATE_ERROR_ACTIVE ; 
 int /*<<< orphan*/  IF_COMM_RCV_HIGH ; 
 int /*<<< orphan*/  IF_COMM_RCV_LOW ; 
 int /*<<< orphan*/  IS_ERR (struct pinctrl*) ; 
 int c_can_chip_config (struct net_device*) ; 
 struct c_can_priv* netdev_priv (struct net_device*) ; 
 struct pinctrl* pinctrl_get_select (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pinctrl_pm_select_default_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pinctrl_put (struct pinctrl*) ; 

__attribute__((used)) static int c_can_start(struct net_device *dev)
{
	struct c_can_priv *priv = netdev_priv(dev);
	int err;
	struct pinctrl *p;

	/* basic c_can configuration */
	err = c_can_chip_config(dev);
	if (err)
		return err;

	/* Setup the command for new messages */
	priv->comm_rcv_high = priv->type != BOSCH_D_CAN ?
		IF_COMM_RCV_LOW : IF_COMM_RCV_HIGH;

	priv->can.state = CAN_STATE_ERROR_ACTIVE;

	/* Attempt to use "active" if available else use "default" */
	p = pinctrl_get_select(priv->device, "active");
	if (!IS_ERR(p))
		pinctrl_put(p);
	else
		pinctrl_pm_select_default_state(priv->device);

	return 0;
}