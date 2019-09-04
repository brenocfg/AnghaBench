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
struct i2c_hw_engine_dce110_create_arg {int /*<<< orphan*/  reference_frequency; } ;
struct i2c_engine {int dummy; } ;
struct TYPE_2__ {struct i2c_engine base; } ;
struct i2c_hw_engine_dce110 {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_CRITICAL (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  construct (struct i2c_hw_engine_dce110*,struct i2c_hw_engine_dce110_create_arg const*) ; 
 struct i2c_hw_engine_dce110* kzalloc (int,int /*<<< orphan*/ ) ; 

struct i2c_engine *dal_i2c_hw_engine_dce110_create(
	const struct i2c_hw_engine_dce110_create_arg *arg)
{
	struct i2c_hw_engine_dce110 *engine_dce10;

	if (!arg) {
		ASSERT_CRITICAL(false);
		return NULL;
	}
	if (!arg->reference_frequency) {
		ASSERT_CRITICAL(false);
		return NULL;
	}

	engine_dce10 = kzalloc(sizeof(struct i2c_hw_engine_dce110),
			       GFP_KERNEL);

	if (!engine_dce10) {
		ASSERT_CRITICAL(false);
		return NULL;
	}

	construct(engine_dce10, arg);
	return &engine_dce10->base.base;
}