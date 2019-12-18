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
typedef  size_t uint32_t ;
struct dce_aux {int dummy; } ;
struct dc_context {int dummy; } ;
struct aux_engine_dce110 {struct dce_aux base; } ;

/* Variables and functions */
 int AUX_TIMEOUT_PERIOD ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SW_AUX_TIMEOUT_PERIOD_MULTIPLIER ; 
 int /*<<< orphan*/ * aux_engine_regs ; 
 int /*<<< orphan*/  dce110_aux_engine_construct (struct aux_engine_dce110*,struct dc_context*,size_t,int,int /*<<< orphan*/ *) ; 
 struct aux_engine_dce110* kzalloc (int,int /*<<< orphan*/ ) ; 

struct dce_aux *dce100_aux_engine_create(
	struct dc_context *ctx,
	uint32_t inst)
{
	struct aux_engine_dce110 *aux_engine =
		kzalloc(sizeof(struct aux_engine_dce110), GFP_KERNEL);

	if (!aux_engine)
		return NULL;

	dce110_aux_engine_construct(aux_engine, ctx, inst,
				    SW_AUX_TIMEOUT_PERIOD_MULTIPLIER * AUX_TIMEOUT_PERIOD,
				    &aux_engine_regs[inst]);

	return &aux_engine->base;
}