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
struct i2c_sw_engine_create_arg {int dummy; } ;
struct i2c_engine {int dummy; } ;
struct i2c_sw_engine {struct i2c_engine base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dal_i2c_sw_engine_construct (struct i2c_sw_engine*,struct i2c_sw_engine_create_arg const*) ; 
 struct i2c_sw_engine* kzalloc (int,int /*<<< orphan*/ ) ; 

struct i2c_engine *dal_i2c_sw_engine_create(
	const struct i2c_sw_engine_create_arg *arg)
{
	struct i2c_sw_engine *engine;

	if (!arg) {
		BREAK_TO_DEBUGGER();
		return NULL;
	}

	engine = kzalloc(sizeof(struct i2c_sw_engine), GFP_KERNEL);

	if (!engine) {
		BREAK_TO_DEBUGGER();
		return NULL;
	}

	dal_i2c_sw_engine_construct(engine, arg);
	return &engine->base;
}