#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {TYPE_1__* funcs; } ;
struct i2c_hw_engine {TYPE_2__ base; } ;
struct TYPE_6__ {int buffer_used_bytes; int transaction_count; } ;
struct TYPE_4__ {int (* get_speed ) (TYPE_2__*) ;} ;

/* Variables and functions */
 TYPE_3__* FROM_I2C_HW_ENGINE (struct i2c_hw_engine const*) ; 
 int TRANSACTION_TIMEOUT_IN_I2C_CLOCKS ; 
 int stub1 (TYPE_2__*) ; 

__attribute__((used)) static uint32_t get_transaction_timeout(
	const struct i2c_hw_engine *engine,
	uint32_t length)
{
	uint32_t speed = engine->base.funcs->get_speed(&engine->base);

	uint32_t period_timeout;
	uint32_t num_of_clock_stretches;

	if (!speed)
		return 0;

	period_timeout = (1000 * TRANSACTION_TIMEOUT_IN_I2C_CLOCKS) / speed;

	num_of_clock_stretches = 1 + (length << 3) + 1;
	num_of_clock_stretches +=
		(FROM_I2C_HW_ENGINE(engine)->buffer_used_bytes << 3) +
		(FROM_I2C_HW_ENGINE(engine)->transaction_count << 1);

	return period_timeout * num_of_clock_stretches;
}