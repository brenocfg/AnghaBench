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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  LEDEN ; 
 int /*<<< orphan*/  TWL4030_MODULE_LED ; 
 int /*<<< orphan*/  twl_i2c_read_u8 (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl_i2c_write_u8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vibra_disable_leds(void)
{
	u8 reg;

	/* Disable LEDA & LEDB, cannot be used with vibra (PWM) */
	twl_i2c_read_u8(TWL4030_MODULE_LED, &reg, LEDEN);
	reg &= ~0x03;
	twl_i2c_write_u8(TWL4030_MODULE_LED, LEDEN, reg);
}