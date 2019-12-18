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
typedef  int uint32_t ;
struct dce_i2c_hw {int reference_frequency; int default_speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_I2C_DDC1_PRESCALE ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  SPEED ; 

__attribute__((used)) static uint32_t get_speed(
	const struct dce_i2c_hw *dce_i2c_hw)
{
	uint32_t pre_scale = 0;

	REG_GET(SPEED, DC_I2C_DDC1_PRESCALE, &pre_scale);

	/* [anaumov] it seems following is unnecessary */
	/*ASSERT(value.bits.DC_I2C_DDC1_PRESCALE);*/
	return pre_scale ?
		dce_i2c_hw->reference_frequency / pre_scale :
		dce_i2c_hw->default_speed;
}