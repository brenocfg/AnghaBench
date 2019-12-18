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
struct net_device {int dummy; } ;
struct TYPE_2__ {int ctrlmode; } ;
struct c_can_priv {scalar_t__ tx_dir; scalar_t__ rxmasked; int /*<<< orphan*/  tx_active; int /*<<< orphan*/  (* write_reg ) (struct c_can_priv*,int /*<<< orphan*/ ,int) ;TYPE_1__ can; } ;

/* Variables and functions */
 int CAN_CTRLMODE_LISTENONLY ; 
 int CAN_CTRLMODE_LOOPBACK ; 
 int CONTROL_ENABLE_AR ; 
 int CONTROL_TEST ; 
 int /*<<< orphan*/  C_CAN_CTRL_REG ; 
 int /*<<< orphan*/  C_CAN_STS_REG ; 
 int /*<<< orphan*/  C_CAN_TEST_REG ; 
 int LEC_UNUSED ; 
 int TEST_LBACK ; 
 int TEST_SILENT ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_can_configure_msg_objects (struct net_device*) ; 
 int c_can_set_bittiming (struct net_device*) ; 
 int c_can_software_reset (struct net_device*) ; 
 struct c_can_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct c_can_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct c_can_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct c_can_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (struct c_can_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (struct c_can_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub6 (struct c_can_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub7 (struct c_can_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub8 (struct c_can_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int c_can_chip_config(struct net_device *dev)
{
	struct c_can_priv *priv = netdev_priv(dev);
	int err;

	err = c_can_software_reset(dev);
	if (err)
		return err;

	/* enable automatic retransmission */
	priv->write_reg(priv, C_CAN_CTRL_REG, CONTROL_ENABLE_AR);

	if ((priv->can.ctrlmode & CAN_CTRLMODE_LISTENONLY) &&
	    (priv->can.ctrlmode & CAN_CTRLMODE_LOOPBACK)) {
		/* loopback + silent mode : useful for hot self-test */
		priv->write_reg(priv, C_CAN_CTRL_REG, CONTROL_TEST);
		priv->write_reg(priv, C_CAN_TEST_REG, TEST_LBACK | TEST_SILENT);
	} else if (priv->can.ctrlmode & CAN_CTRLMODE_LOOPBACK) {
		/* loopback mode : useful for self-test function */
		priv->write_reg(priv, C_CAN_CTRL_REG, CONTROL_TEST);
		priv->write_reg(priv, C_CAN_TEST_REG, TEST_LBACK);
	} else if (priv->can.ctrlmode & CAN_CTRLMODE_LISTENONLY) {
		/* silent mode : bus-monitoring mode */
		priv->write_reg(priv, C_CAN_CTRL_REG, CONTROL_TEST);
		priv->write_reg(priv, C_CAN_TEST_REG, TEST_SILENT);
	}

	/* configure message objects */
	c_can_configure_msg_objects(dev);

	/* set a `lec` value so that we can check for updates later */
	priv->write_reg(priv, C_CAN_STS_REG, LEC_UNUSED);

	/* Clear all internal status */
	atomic_set(&priv->tx_active, 0);
	priv->rxmasked = 0;
	priv->tx_dir = 0;

	/* set bittiming params */
	return c_can_set_bittiming(dev);
}