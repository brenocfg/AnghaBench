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
struct i2c_engine {TYPE_1__* funcs; } ;
struct i2c_hw_engine {struct i2c_engine base; } ;
struct TYPE_2__ {int (* get_speed ) (struct i2c_engine const*) ;} ;

/* Variables and functions */
 int TRANSACTION_TIMEOUT_IN_I2C_CLOCKS ; 
 int stub1 (struct i2c_engine const*) ; 

uint32_t dal_i2c_generic_hw_engine_get_transaction_timeout(
	const struct i2c_hw_engine *engine,
	uint32_t length)
{
	const struct i2c_engine *base = &engine->base;

	uint32_t speed = base->funcs->get_speed(base);

	if (!speed)
		return 0;

	/* total timeout = period_timeout * (start + data bits count + stop) */

	return ((1000 * TRANSACTION_TIMEOUT_IN_I2C_CLOCKS) / speed) *
		(1 + (length << 3) + 1);
}