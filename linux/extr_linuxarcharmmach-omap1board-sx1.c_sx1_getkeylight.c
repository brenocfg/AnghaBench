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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  SOFIA_I2C_ADDR ; 
 int /*<<< orphan*/  SOFIA_KEYLIGHT_REG ; 
 int sx1_i2c_read_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int sx1_getkeylight(u8 * keylight)
{
	return sx1_i2c_read_byte(SOFIA_I2C_ADDR, SOFIA_KEYLIGHT_REG, keylight);
}