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
typedef  int /*<<< orphan*/  u32 ;
struct intel_engine_cs {scalar_t__ id; TYPE_3__* i915; } ;
struct i915_perf_stream {int /*<<< orphan*/  oa_config; } ;
struct i915_gem_context {int dummy; } ;
struct TYPE_4__ {struct i915_perf_stream* exclusive_stream; } ;
struct TYPE_5__ {TYPE_1__ oa; } ;
struct TYPE_6__ {TYPE_2__ perf; } ;

/* Variables and functions */
 scalar_t__ RCS ; 
 int /*<<< orphan*/  gen8_update_reg_state_unlocked (struct i915_gem_context*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void i915_oa_init_reg_state(struct intel_engine_cs *engine,
			    struct i915_gem_context *ctx,
			    u32 *reg_state)
{
	struct i915_perf_stream *stream;

	if (engine->id != RCS)
		return;

	stream = engine->i915->perf.oa.exclusive_stream;
	if (stream)
		gen8_update_reg_state_unlocked(ctx, reg_state, stream->oa_config);
}