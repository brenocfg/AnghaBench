#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct i915_request {TYPE_1__* engine; } ;
struct TYPE_2__ {scalar_t__ class; } ;

/* Variables and functions */
 int EMIT_INVALIDATE ; 
 int I915_GEM_HWS_SCRATCH_ADDR ; 
 scalar_t__ IS_ERR (int*) ; 
 int MI_FLUSH_DW ; 
 int MI_FLUSH_DW_OP_STOREDW ; 
 int MI_FLUSH_DW_STORE_INDEX ; 
 int MI_FLUSH_DW_USE_GTT ; 
 int MI_INVALIDATE_BSD ; 
 int MI_INVALIDATE_TLB ; 
 int PTR_ERR (int*) ; 
 scalar_t__ VIDEO_DECODE_CLASS ; 
 int /*<<< orphan*/  intel_ring_advance (struct i915_request*,int*) ; 
 int* intel_ring_begin (struct i915_request*,int) ; 

__attribute__((used)) static int gen8_emit_flush(struct i915_request *request, u32 mode)
{
	u32 cmd, *cs;

	cs = intel_ring_begin(request, 4);
	if (IS_ERR(cs))
		return PTR_ERR(cs);

	cmd = MI_FLUSH_DW + 1;

	/* We always require a command barrier so that subsequent
	 * commands, such as breadcrumb interrupts, are strictly ordered
	 * wrt the contents of the write cache being flushed to memory
	 * (and thus being coherent from the CPU).
	 */
	cmd |= MI_FLUSH_DW_STORE_INDEX | MI_FLUSH_DW_OP_STOREDW;

	if (mode & EMIT_INVALIDATE) {
		cmd |= MI_INVALIDATE_TLB;
		if (request->engine->class == VIDEO_DECODE_CLASS)
			cmd |= MI_INVALIDATE_BSD;
	}

	*cs++ = cmd;
	*cs++ = I915_GEM_HWS_SCRATCH_ADDR | MI_FLUSH_DW_USE_GTT;
	*cs++ = 0; /* upper addr */
	*cs++ = 0; /* value */
	intel_ring_advance(request, cs);

	return 0;
}