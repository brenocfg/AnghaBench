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
typedef  size_t uint32_t ;
struct i2caux {int aux_timeout_period; int /*<<< orphan*/  default_i2c_sw_speed; int /*<<< orphan*/  default_i2c_hw_speed; int /*<<< orphan*/ * i2c_generic_hw_engine; int /*<<< orphan*/ * i2c_generic_sw_engine; int /*<<< orphan*/ ** aux_engines; int /*<<< orphan*/ ** i2c_hw_engines; int /*<<< orphan*/ ** i2c_sw_engines; struct dc_context* ctx; } ;
struct dc_context {scalar_t__ dce_version; } ;

/* Variables and functions */
 int AUX_TIMEOUT_PERIOD ; 
 scalar_t__ DCE_VERSION_11_2 ; 
 int /*<<< orphan*/  DEFAULT_I2C_HW_SPEED ; 
 int /*<<< orphan*/  DEFAULT_I2C_HW_SPEED_100KHZ ; 
 int /*<<< orphan*/  DEFAULT_I2C_SW_SPEED ; 
 int /*<<< orphan*/  DEFAULT_I2C_SW_SPEED_100KHZ ; 
 size_t GPIO_DDC_LINE_COUNT ; 
 int SW_AUX_TIMEOUT_PERIOD_MULTIPLIER ; 

void dal_i2caux_construct(
	struct i2caux *i2caux,
	struct dc_context *ctx)
{
	uint32_t i = 0;

	i2caux->ctx = ctx;
	do {
		i2caux->i2c_sw_engines[i] = NULL;
		i2caux->i2c_hw_engines[i] = NULL;
		i2caux->aux_engines[i] = NULL;

		++i;
	} while (i < GPIO_DDC_LINE_COUNT);

	i2caux->i2c_generic_sw_engine = NULL;
	i2caux->i2c_generic_hw_engine = NULL;

	i2caux->aux_timeout_period =
		SW_AUX_TIMEOUT_PERIOD_MULTIPLIER * AUX_TIMEOUT_PERIOD;

	if (ctx->dce_version >= DCE_VERSION_11_2) {
		i2caux->default_i2c_hw_speed = DEFAULT_I2C_HW_SPEED_100KHZ;
		i2caux->default_i2c_sw_speed = DEFAULT_I2C_SW_SPEED_100KHZ;
	} else {
		i2caux->default_i2c_hw_speed = DEFAULT_I2C_HW_SPEED;
		i2caux->default_i2c_sw_speed = DEFAULT_I2C_SW_SPEED;
	}
}