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
struct i915_request {int dummy; } ;

/* Variables and functions */
 int EMIT_INVALIDATE ; 
 scalar_t__ IS_ERR (int*) ; 
 int MI_FLUSH ; 
 int /*<<< orphan*/  MI_NOOP ; 
 int MI_READ_FLUSH ; 
 int PTR_ERR (int*) ; 
 int /*<<< orphan*/  intel_ring_advance (struct i915_request*,int*) ; 
 int* intel_ring_begin (struct i915_request*,int) ; 

__attribute__((used)) static int
gen2_render_ring_flush(struct i915_request *rq, u32 mode)
{
	u32 cmd, *cs;

	cmd = MI_FLUSH;

	if (mode & EMIT_INVALIDATE)
		cmd |= MI_READ_FLUSH;

	cs = intel_ring_begin(rq, 2);
	if (IS_ERR(cs))
		return PTR_ERR(cs);

	*cs++ = cmd;
	*cs++ = MI_NOOP;
	intel_ring_advance(rq, cs);

	return 0;
}