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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 int /*<<< orphan*/  SOFIA_BACKLIGHT_REG ; 
 int /*<<< orphan*/  SOFIA_I2C_ADDR ; 
 scalar_t__ SOFIA_MAX_LIGHT_VAL ; 
 int sx1_i2c_write_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

int sx1_setbacklight(u8 backlight)
{
	if (backlight > SOFIA_MAX_LIGHT_VAL)
		backlight = SOFIA_MAX_LIGHT_VAL;
	return sx1_i2c_write_byte(SOFIA_I2C_ADDR, SOFIA_BACKLIGHT_REG,
				  backlight);
}