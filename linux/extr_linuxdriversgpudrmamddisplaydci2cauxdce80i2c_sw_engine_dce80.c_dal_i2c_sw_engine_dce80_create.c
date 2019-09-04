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
struct i2c_sw_engine_dce80_create_arg {int dummy; } ;
struct i2c_engine {int dummy; } ;
struct TYPE_2__ {struct i2c_engine base; } ;
struct i2c_sw_engine_dce80 {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  construct (struct i2c_sw_engine_dce80*,struct i2c_sw_engine_dce80_create_arg const*) ; 
 struct i2c_sw_engine_dce80* kzalloc (int,int /*<<< orphan*/ ) ; 

struct i2c_engine *dal_i2c_sw_engine_dce80_create(
	const struct i2c_sw_engine_dce80_create_arg *arg)
{
	struct i2c_sw_engine_dce80 *engine;

	if (!arg) {
		BREAK_TO_DEBUGGER();
		return NULL;
	}

	engine = kzalloc(sizeof(struct i2c_sw_engine_dce80), GFP_KERNEL);

	if (!engine) {
		BREAK_TO_DEBUGGER();
		return NULL;
	}

	construct(engine, arg);
	return &engine->base.base;
}