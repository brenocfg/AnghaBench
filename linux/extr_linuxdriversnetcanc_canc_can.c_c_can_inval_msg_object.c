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
struct c_can_priv {int /*<<< orphan*/  (* write_reg ) (struct c_can_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ARB1_REG ; 
 int /*<<< orphan*/  ARB2_REG ; 
 int /*<<< orphan*/  C_CAN_IFACE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  c_can_inval_tx_object (struct net_device*,int,int) ; 
 struct c_can_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct c_can_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct c_can_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void c_can_inval_msg_object(struct net_device *dev, int iface, int obj)
{
	struct c_can_priv *priv = netdev_priv(dev);

	priv->write_reg(priv, C_CAN_IFACE(ARB1_REG, iface), 0);
	priv->write_reg(priv, C_CAN_IFACE(ARB2_REG, iface), 0);
	c_can_inval_tx_object(dev, iface, obj);
}