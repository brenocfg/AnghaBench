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
typedef  int /*<<< orphan*/  u32 ;
struct intel_engine_cs {scalar_t__ class; TYPE_2__* i915; } ;
struct intel_context {int dummy; } ;
struct i915_perf_stream {int /*<<< orphan*/  oa_config; } ;
struct TYPE_3__ {struct i915_perf_stream* exclusive_stream; } ;
struct TYPE_4__ {TYPE_1__ perf; } ;

/* Variables and functions */
 scalar_t__ RENDER_CLASS ; 
 int /*<<< orphan*/  gen8_update_reg_state_unlocked (struct i915_perf_stream*,struct intel_context*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void i915_oa_init_reg_state(struct intel_engine_cs *engine,
			    struct intel_context *ce,
			    u32 *regs)
{
	struct i915_perf_stream *stream;

	if (engine->class != RENDER_CLASS)
		return;

	stream = engine->i915->perf.exclusive_stream;
	if (stream)
		gen8_update_reg_state_unlocked(stream, ce, regs, stream->oa_config);
}