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
typedef  int /*<<< orphan*/  uint32_t ;
struct i2c_engine {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  speed; } ;

/* Variables and functions */
 TYPE_1__* FROM_I2C_ENGINE (struct i2c_engine const*) ; 

uint32_t dal_i2c_sw_engine_get_speed(
	const struct i2c_engine *engine)
{
	return FROM_I2C_ENGINE(engine)->speed;
}