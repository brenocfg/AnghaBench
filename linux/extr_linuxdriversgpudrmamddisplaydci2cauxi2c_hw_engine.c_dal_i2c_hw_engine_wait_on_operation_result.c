#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {TYPE_1__* funcs; } ;
struct i2c_hw_engine {TYPE_2__ base; } ;
typedef  enum i2c_channel_operation_result { ____Placeholder_i2c_channel_operation_result } i2c_channel_operation_result ;
struct TYPE_3__ {int (* get_channel_status ) (TYPE_2__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int I2C_CHANNEL_OPERATION_SUCCEEDED ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

enum i2c_channel_operation_result dal_i2c_hw_engine_wait_on_operation_result(
	struct i2c_hw_engine *engine,
	uint32_t timeout,
	enum i2c_channel_operation_result expected_result)
{
	enum i2c_channel_operation_result result;
	uint32_t i = 0;

	if (!timeout)
		return I2C_CHANNEL_OPERATION_SUCCEEDED;

	do {
		result = engine->base.funcs->get_channel_status(
			&engine->base, NULL);

		if (result != expected_result)
			break;

		udelay(1);

		++i;
	} while (i < timeout);

	return result;
}