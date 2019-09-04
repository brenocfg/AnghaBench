#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct i2caux_dce80 {int i2c_hw_buffer_in_use; } ;
struct i2caux {struct i2c_engine* i2c_generic_hw_engine; struct i2c_engine** i2c_hw_engines; } ;
struct TYPE_7__ {TYPE_2__* funcs; } ;
struct i2c_engine {TYPE_3__ base; } ;
struct TYPE_5__ {scalar_t__ hw_supported; } ;
struct ddc {TYPE_1__ hw_info; } ;
typedef  enum gpio_ddc_line { ____Placeholder_gpio_ddc_line } gpio_ddc_line ;
struct TYPE_6__ {scalar_t__ (* acquire ) (TYPE_3__*,struct ddc*) ;} ;

/* Variables and functions */
 struct i2caux_dce80* FROM_I2C_AUX (struct i2caux*) ; 
 int GPIO_DDC_LINE_COUNT ; 
 int dal_ddc_get_line (struct ddc*) ; 
 scalar_t__ stub1 (TYPE_3__*,struct ddc*) ; 
 scalar_t__ stub2 (TYPE_3__*,struct ddc*) ; 

__attribute__((used)) static struct i2c_engine *acquire_i2c_hw_engine(
	struct i2caux *i2caux,
	struct ddc *ddc)
{
	struct i2caux_dce80 *i2caux_dce80 = FROM_I2C_AUX(i2caux);

	struct i2c_engine *engine = NULL;
	bool non_generic;

	if (!ddc)
		return NULL;

	if (ddc->hw_info.hw_supported) {
		enum gpio_ddc_line line = dal_ddc_get_line(ddc);

		if (line < GPIO_DDC_LINE_COUNT) {
			non_generic = true;
			engine = i2caux->i2c_hw_engines[line];
		}
	}

	if (!engine) {
		non_generic = false;
		engine = i2caux->i2c_generic_hw_engine;
	}

	if (!engine)
		return NULL;

	if (non_generic) {
		if (!i2caux_dce80->i2c_hw_buffer_in_use &&
			engine->base.funcs->acquire(&engine->base, ddc)) {
			i2caux_dce80->i2c_hw_buffer_in_use = true;
			return engine;
		}
	} else {
		if (engine->base.funcs->acquire(&engine->base, ddc))
			return engine;
	}

	return NULL;
}