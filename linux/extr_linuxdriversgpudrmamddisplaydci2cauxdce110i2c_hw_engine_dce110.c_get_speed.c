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
typedef  int uint32_t ;
struct TYPE_2__ {int default_speed; } ;
struct i2c_hw_engine_dce110 {int reference_frequency; TYPE_1__ base; } ;
struct i2c_engine {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_I2C_DDC1_PRESCALE ; 
 struct i2c_hw_engine_dce110* FROM_I2C_ENGINE (struct i2c_engine const*) ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  SPEED ; 

__attribute__((used)) static uint32_t get_speed(
	const struct i2c_engine *i2c_engine)
{
	const struct i2c_hw_engine_dce110 *hw_engine = FROM_I2C_ENGINE(i2c_engine);
	uint32_t pre_scale = 0;

	REG_GET(SPEED, DC_I2C_DDC1_PRESCALE, &pre_scale);

	/* [anaumov] it seems following is unnecessary */
	/*ASSERT(value.bits.DC_I2C_DDC1_PRESCALE);*/
	return pre_scale ?
		hw_engine->reference_frequency / pre_scale :
		hw_engine->base.default_speed;
}