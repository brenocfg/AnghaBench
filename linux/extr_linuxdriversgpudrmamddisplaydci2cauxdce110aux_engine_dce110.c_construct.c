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
struct aux_engine_dce110_init_data {int /*<<< orphan*/  regs; int /*<<< orphan*/  timeout_period; int /*<<< orphan*/  ctx; } ;
struct TYPE_3__ {int /*<<< orphan*/ * funcs; } ;
struct TYPE_4__ {int /*<<< orphan*/ * funcs; TYPE_1__ base; } ;
struct aux_engine_dce110 {int /*<<< orphan*/  regs; int /*<<< orphan*/  timeout_period; TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  aux_engine_funcs ; 
 int /*<<< orphan*/  dal_aux_engine_construct (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  engine_funcs ; 

__attribute__((used)) static void construct(
	struct aux_engine_dce110 *engine,
	const struct aux_engine_dce110_init_data *aux_init_data)
{
	dal_aux_engine_construct(&engine->base, aux_init_data->ctx);
	engine->base.base.funcs = &engine_funcs;
	engine->base.funcs = &aux_engine_funcs;

	engine->timeout_period = aux_init_data->timeout_period;
	engine->regs = aux_init_data->regs;
}