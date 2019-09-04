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
struct TYPE_2__ {struct ddc* ddc; } ;
struct i2c_engine {TYPE_1__ base; } ;
struct ddc {int dummy; } ;
typedef  enum gpio_result { ____Placeholder_gpio_result } gpio_result ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_DDC_CONFIG_TYPE_MODE_I2C ; 
 int /*<<< orphan*/  GPIO_MODE_FAST_OUTPUT ; 
 int GPIO_RESULT_OK ; 
 int dal_ddc_open (struct ddc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool dal_i2caux_i2c_sw_engine_acquire_engine(
	struct i2c_engine *engine,
	struct ddc *ddc)
{
	enum gpio_result result;

	result = dal_ddc_open(ddc, GPIO_MODE_FAST_OUTPUT,
		GPIO_DDC_CONFIG_TYPE_MODE_I2C);

	if (result != GPIO_RESULT_OK)
		return false;

	engine->base.ddc = ddc;

	return true;
}