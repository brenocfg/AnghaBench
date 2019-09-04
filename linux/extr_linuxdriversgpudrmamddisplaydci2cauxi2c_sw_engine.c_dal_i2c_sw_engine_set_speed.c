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
struct i2c_sw_engine {int speed; int clock_delay; } ;
struct i2c_engine {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 struct i2c_sw_engine* FROM_I2C_ENGINE (struct i2c_engine*) ; 
 int I2CAUX_DEFAULT_I2C_SW_SPEED ; 

void dal_i2c_sw_engine_set_speed(
	struct i2c_engine *engine,
	uint32_t speed)
{
	struct i2c_sw_engine *sw_engine = FROM_I2C_ENGINE(engine);

	ASSERT(speed);

	sw_engine->speed = speed ? speed : I2CAUX_DEFAULT_I2C_SW_SPEED;

	sw_engine->clock_delay = 1000 / sw_engine->speed;

	if (sw_engine->clock_delay < 12)
		sw_engine->clock_delay = 12;
}