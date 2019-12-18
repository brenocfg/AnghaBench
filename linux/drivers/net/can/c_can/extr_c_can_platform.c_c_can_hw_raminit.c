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
struct c_can_priv {int /*<<< orphan*/  (* write_reg32 ) (struct c_can_priv const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* read_reg32 ) (struct c_can_priv const*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  C_CAN_FUNCTION_REG ; 
 int /*<<< orphan*/  DCAN_RAM_INIT_BIT ; 
 int /*<<< orphan*/  c_can_hw_raminit_wait (struct c_can_priv const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct c_can_priv const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct c_can_priv const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct c_can_priv const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void c_can_hw_raminit(const struct c_can_priv *priv, bool enable)
{
	u32 ctrl;

	ctrl = priv->read_reg32(priv, C_CAN_FUNCTION_REG);
	ctrl &= ~DCAN_RAM_INIT_BIT;
	priv->write_reg32(priv, C_CAN_FUNCTION_REG, ctrl);
	c_can_hw_raminit_wait(priv, ctrl);

	if (enable) {
		ctrl |= DCAN_RAM_INIT_BIT;
		priv->write_reg32(priv, C_CAN_FUNCTION_REG, ctrl);
		c_can_hw_raminit_wait(priv, ctrl);
	}
}