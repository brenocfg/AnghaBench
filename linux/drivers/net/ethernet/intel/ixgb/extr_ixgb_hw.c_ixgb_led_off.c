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
struct ixgb_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL0 ; 
 int /*<<< orphan*/  IXGB_CTRL0_SDP0 ; 
 int /*<<< orphan*/  IXGB_READ_REG (struct ixgb_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGB_WRITE_REG (struct ixgb_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ixgb_led_off(struct ixgb_hw *hw)
{
	u32 ctrl0_reg = IXGB_READ_REG(hw, CTRL0);

	/* To turn off the LED, set software-definable pin 0 (SDP0). */
	ctrl0_reg |= IXGB_CTRL0_SDP0;
	IXGB_WRITE_REG(hw, CTRL0, ctrl0_reg);
}