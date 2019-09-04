#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct i2c_sw_engine_dce110_create_arg {int /*<<< orphan*/  engine_id; int /*<<< orphan*/  default_speed; int /*<<< orphan*/  ctx; } ;
struct TYPE_4__ {int /*<<< orphan*/ * funcs; } ;
struct TYPE_5__ {int /*<<< orphan*/ * funcs; TYPE_1__ base; } ;
struct TYPE_6__ {int /*<<< orphan*/  default_speed; TYPE_2__ base; } ;
struct i2c_sw_engine_dce110 {int /*<<< orphan*/  engine_id; TYPE_3__ base; } ;
struct i2c_sw_engine_create_arg {int /*<<< orphan*/  default_speed; int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  dal_i2c_sw_engine_construct (TYPE_3__*,struct i2c_sw_engine_create_arg*) ; 
 int /*<<< orphan*/  engine_funcs ; 
 int /*<<< orphan*/  i2c_engine_funcs ; 

__attribute__((used)) static void construct(
	struct i2c_sw_engine_dce110 *engine_dce110,
	const struct i2c_sw_engine_dce110_create_arg *arg_dce110)
{
	struct i2c_sw_engine_create_arg arg_base;

	arg_base.ctx = arg_dce110->ctx;
	arg_base.default_speed = arg_dce110->default_speed;

	dal_i2c_sw_engine_construct(&engine_dce110->base, &arg_base);

	/*struct engine   struct engine_funcs*/
	engine_dce110->base.base.base.funcs = &engine_funcs;
	/*struct i2c_engine  struct i2c_engine_funcs*/
	engine_dce110->base.base.funcs = &i2c_engine_funcs;
	engine_dce110->base.default_speed = arg_dce110->default_speed;
	engine_dce110->engine_id = arg_dce110->engine_id;
}