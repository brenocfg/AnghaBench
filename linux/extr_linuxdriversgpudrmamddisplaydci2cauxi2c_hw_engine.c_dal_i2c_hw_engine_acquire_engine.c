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
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {struct ddc* ddc; } ;
struct i2c_engine {TYPE_2__* funcs; TYPE_1__ base; } ;
struct ddc {int dummy; } ;
typedef  enum gpio_result { ____Placeholder_gpio_result } gpio_result ;
struct TYPE_6__ {scalar_t__ original_speed; } ;
struct TYPE_5__ {scalar_t__ (* get_speed ) (struct i2c_engine*) ;} ;

/* Variables and functions */
 TYPE_3__* FROM_I2C_ENGINE (struct i2c_engine*) ; 
 int /*<<< orphan*/  GPIO_DDC_CONFIG_TYPE_MODE_I2C ; 
 int /*<<< orphan*/  GPIO_MODE_HARDWARE ; 
 int GPIO_RESULT_OK ; 
 int dal_ddc_open (struct ddc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct i2c_engine*) ; 

bool dal_i2c_hw_engine_acquire_engine(
	struct i2c_engine *engine,
	struct ddc *ddc)
{
	enum gpio_result result;
	uint32_t current_speed;

	result = dal_ddc_open(ddc, GPIO_MODE_HARDWARE,
		GPIO_DDC_CONFIG_TYPE_MODE_I2C);

	if (result != GPIO_RESULT_OK)
		return false;

	engine->base.ddc = ddc;

	current_speed = engine->funcs->get_speed(engine);

	if (current_speed)
		FROM_I2C_ENGINE(engine)->original_speed = current_speed;

	return true;
}