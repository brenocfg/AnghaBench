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
struct i2c_engine {TYPE_1__* funcs; } ;
struct engine {TYPE_2__* funcs; } ;
struct ddc {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* release_engine ) (struct engine*) ;} ;
struct TYPE_3__ {int (* acquire_engine ) (struct i2c_engine*,struct ddc*) ;int /*<<< orphan*/  (* setup_engine ) (struct i2c_engine*) ;} ;

/* Variables and functions */
 struct i2c_engine* FROM_ENGINE (struct engine*) ; 
 int stub1 (struct i2c_engine*,struct ddc*) ; 
 int /*<<< orphan*/  stub2 (struct i2c_engine*) ; 
 int /*<<< orphan*/  stub3 (struct engine*) ; 
 int /*<<< orphan*/  udelay (int) ; 

bool dal_i2c_engine_acquire(
	struct engine *engine,
	struct ddc *ddc_handle)
{
	struct i2c_engine *i2c_engine = FROM_ENGINE(engine);

	uint32_t counter = 0;
	bool result;

	do {
		result = i2c_engine->funcs->acquire_engine(
			i2c_engine, ddc_handle);

		if (result)
			break;

		/* i2c_engine is busy by VBios, lets wait and retry */

		udelay(10);

		++counter;
	} while (counter < 2);

	if (result) {
		if (!i2c_engine->funcs->setup_engine(i2c_engine)) {
			engine->funcs->release_engine(engine);
			result = false;
		}
	}

	return result;
}