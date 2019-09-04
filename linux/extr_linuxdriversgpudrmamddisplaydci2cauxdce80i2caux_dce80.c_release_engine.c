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
struct i2caux {int dummy; } ;
struct engine {TYPE_1__* funcs; } ;
struct TYPE_4__ {int i2c_hw_buffer_in_use; } ;
struct TYPE_3__ {scalar_t__ (* get_engine_type ) (struct engine*) ;} ;

/* Variables and functions */
 TYPE_2__* FROM_I2C_AUX (struct i2caux*) ; 
 scalar_t__ I2CAUX_ENGINE_TYPE_I2C_DDC_HW ; 
 int /*<<< orphan*/  dal_i2caux_release_engine (struct i2caux*,struct engine*) ; 
 scalar_t__ stub1 (struct engine*) ; 

__attribute__((used)) static void release_engine(
	struct i2caux *i2caux,
	struct engine *engine)
{
	if (engine->funcs->get_engine_type(engine) ==
		I2CAUX_ENGINE_TYPE_I2C_DDC_HW)
		FROM_I2C_AUX(i2caux)->i2c_hw_buffer_in_use = false;

	dal_i2caux_release_engine(i2caux, engine);
}