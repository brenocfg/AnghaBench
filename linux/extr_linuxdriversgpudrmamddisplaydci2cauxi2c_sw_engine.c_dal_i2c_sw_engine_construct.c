#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct i2c_sw_engine_create_arg {int /*<<< orphan*/  default_speed; int /*<<< orphan*/  ctx; } ;
struct TYPE_4__ {int /*<<< orphan*/ * funcs; } ;
struct TYPE_5__ {TYPE_1__ base; int /*<<< orphan*/ * funcs; } ;
struct i2c_sw_engine {TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  dal_i2c_engine_construct (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dal_i2c_sw_engine_set_speed (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  engine_funcs ; 
 int /*<<< orphan*/  i2c_engine_funcs ; 

void dal_i2c_sw_engine_construct(
	struct i2c_sw_engine *engine,
	const struct i2c_sw_engine_create_arg *arg)
{
	dal_i2c_engine_construct(&engine->base, arg->ctx);
	dal_i2c_sw_engine_set_speed(&engine->base, arg->default_speed);
	engine->base.funcs = &i2c_engine_funcs;
	engine->base.base.funcs = &engine_funcs;
}