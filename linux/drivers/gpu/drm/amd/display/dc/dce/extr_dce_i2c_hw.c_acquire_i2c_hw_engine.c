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
typedef  int uint32_t ;
struct resource_pool {int i2c_hw_buffer_in_use; struct dce_i2c_hw** hw_i2cs; TYPE_2__* res_cap; } ;
struct TYPE_3__ {scalar_t__ hw_supported; } ;
struct ddc {TYPE_1__ hw_info; } ;
struct dce_i2c_hw {int original_speed; struct ddc* ddc; } ;
typedef  enum gpio_result { ____Placeholder_gpio_result } gpio_result ;
typedef  enum gpio_ddc_line { ____Placeholder_gpio_ddc_line } gpio_ddc_line ;
struct TYPE_4__ {int num_ddc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_DDC_CONFIG_TYPE_MODE_I2C ; 
 int /*<<< orphan*/  GPIO_MODE_HARDWARE ; 
 int GPIO_RESULT_OK ; 
 int dal_ddc_get_line (struct ddc*) ; 
 int dal_ddc_open (struct ddc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_speed (struct dce_i2c_hw*) ; 
 int /*<<< orphan*/  is_engine_available (struct dce_i2c_hw*) ; 
 int /*<<< orphan*/  release_engine (struct dce_i2c_hw*) ; 
 int /*<<< orphan*/  setup_engine (struct dce_i2c_hw*) ; 
 int /*<<< orphan*/  udelay (int) ; 

struct dce_i2c_hw *acquire_i2c_hw_engine(
	struct resource_pool *pool,
	struct ddc *ddc)
{
	uint32_t counter = 0;
	enum gpio_result result;
	uint32_t current_speed;
	struct dce_i2c_hw *dce_i2c_hw = NULL;

	if (!ddc)
		return NULL;

	if (ddc->hw_info.hw_supported) {
		enum gpio_ddc_line line = dal_ddc_get_line(ddc);

		if (line < pool->res_cap->num_ddc)
			dce_i2c_hw = pool->hw_i2cs[line];
	}

	if (!dce_i2c_hw)
		return NULL;

	if (pool->i2c_hw_buffer_in_use || !is_engine_available(dce_i2c_hw))
		return NULL;

	do {
		result = dal_ddc_open(ddc, GPIO_MODE_HARDWARE,
			GPIO_DDC_CONFIG_TYPE_MODE_I2C);

		if (result == GPIO_RESULT_OK)
			break;

		/* i2c_engine is busy by VBios, lets wait and retry */

		udelay(10);

		++counter;
	} while (counter < 2);

	if (result != GPIO_RESULT_OK)
		return NULL;

	dce_i2c_hw->ddc = ddc;

	current_speed = get_speed(dce_i2c_hw);

	if (current_speed)
		dce_i2c_hw->original_speed = current_speed;

	if (!setup_engine(dce_i2c_hw)) {
		release_engine(dce_i2c_hw);
		return NULL;
	}

	pool->i2c_hw_buffer_in_use = true;
	return dce_i2c_hw;
}