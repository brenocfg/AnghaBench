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
typedef  int u32 ;
struct intel_engine_cs {int /*<<< orphan*/  gt; } ;
struct i915_request {struct intel_engine_cs* engine; } ;

/* Variables and functions */
 int EMIT_FLUSH ; 
 int EMIT_INVALIDATE ; 
 int /*<<< orphan*/  INTEL_GT_SCRATCH_FIELD_RENDER_FLUSH ; 
 scalar_t__ IS_ERR (int*) ; 
 int PIPE_CONTROL_COMMAND_CACHE_INVALIDATE ; 
 int PIPE_CONTROL_CONST_CACHE_INVALIDATE ; 
 int PIPE_CONTROL_CS_STALL ; 
 int PIPE_CONTROL_DC_FLUSH_ENABLE ; 
 int PIPE_CONTROL_DEPTH_CACHE_FLUSH ; 
 int PIPE_CONTROL_FLUSH_ENABLE ; 
 int PIPE_CONTROL_GLOBAL_GTT_IVB ; 
 int PIPE_CONTROL_INSTRUCTION_CACHE_INVALIDATE ; 
 int PIPE_CONTROL_QW_WRITE ; 
 int PIPE_CONTROL_RENDER_TARGET_CACHE_FLUSH ; 
 int PIPE_CONTROL_STATE_CACHE_INVALIDATE ; 
 int PIPE_CONTROL_TEXTURE_CACHE_INVALIDATE ; 
 int PIPE_CONTROL_TILE_CACHE_FLUSH ; 
 int PIPE_CONTROL_TLB_INVALIDATE ; 
 int PIPE_CONTROL_VF_CACHE_INVALIDATE ; 
 int PTR_ERR (int*) ; 
 int* gen8_emit_pipe_control (int*,int,int const) ; 
 int intel_gt_scratch_offset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ring_advance (struct i915_request*,int*) ; 
 int* intel_ring_begin (struct i915_request*,int) ; 

__attribute__((used)) static int gen11_emit_flush_render(struct i915_request *request,
				   u32 mode)
{
	struct intel_engine_cs *engine = request->engine;
	const u32 scratch_addr =
		intel_gt_scratch_offset(engine->gt,
					INTEL_GT_SCRATCH_FIELD_RENDER_FLUSH);

	if (mode & EMIT_FLUSH) {
		u32 *cs;
		u32 flags = 0;

		flags |= PIPE_CONTROL_CS_STALL;

		flags |= PIPE_CONTROL_TILE_CACHE_FLUSH;
		flags |= PIPE_CONTROL_RENDER_TARGET_CACHE_FLUSH;
		flags |= PIPE_CONTROL_DEPTH_CACHE_FLUSH;
		flags |= PIPE_CONTROL_DC_FLUSH_ENABLE;
		flags |= PIPE_CONTROL_FLUSH_ENABLE;
		flags |= PIPE_CONTROL_QW_WRITE;
		flags |= PIPE_CONTROL_GLOBAL_GTT_IVB;

		cs = intel_ring_begin(request, 6);
		if (IS_ERR(cs))
			return PTR_ERR(cs);

		cs = gen8_emit_pipe_control(cs, flags, scratch_addr);
		intel_ring_advance(request, cs);
	}

	if (mode & EMIT_INVALIDATE) {
		u32 *cs;
		u32 flags = 0;

		flags |= PIPE_CONTROL_CS_STALL;

		flags |= PIPE_CONTROL_COMMAND_CACHE_INVALIDATE;
		flags |= PIPE_CONTROL_TLB_INVALIDATE;
		flags |= PIPE_CONTROL_INSTRUCTION_CACHE_INVALIDATE;
		flags |= PIPE_CONTROL_TEXTURE_CACHE_INVALIDATE;
		flags |= PIPE_CONTROL_VF_CACHE_INVALIDATE;
		flags |= PIPE_CONTROL_CONST_CACHE_INVALIDATE;
		flags |= PIPE_CONTROL_STATE_CACHE_INVALIDATE;
		flags |= PIPE_CONTROL_QW_WRITE;
		flags |= PIPE_CONTROL_GLOBAL_GTT_IVB;

		cs = intel_ring_begin(request, 6);
		if (IS_ERR(cs))
			return PTR_ERR(cs);

		cs = gen8_emit_pipe_control(cs, flags, scratch_addr);
		intel_ring_advance(request, cs);
	}

	return 0;
}