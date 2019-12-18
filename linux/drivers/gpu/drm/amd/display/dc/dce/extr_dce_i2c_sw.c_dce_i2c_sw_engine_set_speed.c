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
struct dce_i2c_sw {int speed; int clock_delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int DCE_I2C_DEFAULT_I2C_SW_SPEED ; 

void dce_i2c_sw_engine_set_speed(
	struct dce_i2c_sw *engine,
	uint32_t speed)
{
	ASSERT(speed);

	engine->speed = speed ? speed : DCE_I2C_DEFAULT_I2C_SW_SPEED;

	engine->clock_delay = 1000 / engine->speed;

	if (engine->clock_delay < 12)
		engine->clock_delay = 12;
}