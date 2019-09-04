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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct c_can_priv {int /*<<< orphan*/  (* write_reg ) (struct c_can_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* write_reg32 ) (struct c_can_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ARB1_REG ; 
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  C_CAN_IFACE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IF_ARB_MSGVAL ; 
 int /*<<< orphan*/  IF_COMM_RCV_SETUP ; 
 int /*<<< orphan*/  MASK1_REG ; 
 int /*<<< orphan*/  MSGCTRL_REG ; 
 int /*<<< orphan*/  c_can_object_put (struct net_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct c_can_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct c_can_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct c_can_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct c_can_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void c_can_setup_receive_object(struct net_device *dev, int iface,
				       u32 obj, u32 mask, u32 id, u32 mcont)
{
	struct c_can_priv *priv = netdev_priv(dev);

	mask |= BIT(29);
	priv->write_reg32(priv, C_CAN_IFACE(MASK1_REG, iface), mask);

	id |= IF_ARB_MSGVAL;
	priv->write_reg32(priv, C_CAN_IFACE(ARB1_REG, iface), id);

	priv->write_reg(priv, C_CAN_IFACE(MSGCTRL_REG, iface), mcont);
	c_can_object_put(dev, iface, obj, IF_COMM_RCV_SETUP);
}