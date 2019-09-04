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
struct resource_pool {size_t pipe_count; int /*<<< orphan*/ ** transforms; int /*<<< orphan*/ ** mis; int /*<<< orphan*/ ** timing_generators; int /*<<< orphan*/ ** opps; } ;
struct dce_transform {int /*<<< orphan*/  base; } ;
struct dce_mem_input {int /*<<< orphan*/  base; } ;
struct dce110_timing_generator {int /*<<< orphan*/  base; } ;
struct dce110_opp {int /*<<< orphan*/  base; } ;
struct dc_context {TYPE_2__* dc; } ;
struct TYPE_3__ {int max_slave_planes; } ;
struct TYPE_4__ {TYPE_1__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dce110_mem_input_v_construct (struct dce_transform*,struct dc_context*) ; 
 int /*<<< orphan*/  dce110_opp_v_construct (struct dce_transform*,struct dc_context*) ; 
 int /*<<< orphan*/  dce110_timing_generator_v_construct (struct dce_transform*,struct dc_context*) ; 
 int /*<<< orphan*/  dce110_transform_v_construct (struct dce_transform*,struct dc_context*) ; 
 int /*<<< orphan*/  kfree (struct dce_transform*) ; 
 struct dce_transform* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool underlay_create(struct dc_context *ctx, struct resource_pool *pool)
{
	struct dce110_timing_generator *dce110_tgv = kzalloc(sizeof(*dce110_tgv),
							     GFP_KERNEL);
	struct dce_transform *dce110_xfmv = kzalloc(sizeof(*dce110_xfmv),
						    GFP_KERNEL);
	struct dce_mem_input *dce110_miv = kzalloc(sizeof(*dce110_miv),
						   GFP_KERNEL);
	struct dce110_opp *dce110_oppv = kzalloc(sizeof(*dce110_oppv),
						 GFP_KERNEL);

	if (!dce110_tgv || !dce110_xfmv || !dce110_miv || !dce110_oppv) {
		kfree(dce110_tgv);
		kfree(dce110_xfmv);
		kfree(dce110_miv);
		kfree(dce110_oppv);
		return false;
	}

	dce110_opp_v_construct(dce110_oppv, ctx);

	dce110_timing_generator_v_construct(dce110_tgv, ctx);
	dce110_mem_input_v_construct(dce110_miv, ctx);
	dce110_transform_v_construct(dce110_xfmv, ctx);

	pool->opps[pool->pipe_count] = &dce110_oppv->base;
	pool->timing_generators[pool->pipe_count] = &dce110_tgv->base;
	pool->mis[pool->pipe_count] = &dce110_miv->base;
	pool->transforms[pool->pipe_count] = &dce110_xfmv->base;
	pool->pipe_count++;

	/* update the public caps to indicate an underlay is available */
	ctx->dc->caps.max_slave_planes = 1;
	ctx->dc->caps.max_slave_planes = 1;

	return true;
}