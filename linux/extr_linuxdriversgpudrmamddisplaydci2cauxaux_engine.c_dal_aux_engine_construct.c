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
struct dc_context {int dummy; } ;
struct aux_engine {scalar_t__ max_defer_write_retry; scalar_t__ delay; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  dal_i2caux_construct_engine (int /*<<< orphan*/ *,struct dc_context*) ; 

void dal_aux_engine_construct(
	struct aux_engine *engine,
	struct dc_context *ctx)
{
	dal_i2caux_construct_engine(&engine->base, ctx);
	engine->delay = 0;
	engine->max_defer_write_retry = 0;
}