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
typedef  int u32 ;
struct c_can_priv {int (* read_reg ) (struct c_can_priv*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* write_reg ) (struct c_can_priv*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int CONTROL_IRQMSK ; 
 int /*<<< orphan*/  C_CAN_CTRL_REG ; 
 int stub1 (struct c_can_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct c_can_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void c_can_irq_control(struct c_can_priv *priv, bool enable)
{
	u32 ctrl = priv->read_reg(priv,	C_CAN_CTRL_REG) & ~CONTROL_IRQMSK;

	if (enable)
		ctrl |= CONTROL_IRQMSK;

	priv->write_reg(priv, C_CAN_CTRL_REG, ctrl);
}