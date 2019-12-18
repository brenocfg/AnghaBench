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
typedef  int /*<<< orphan*/  u32 ;
struct i915_request {int /*<<< orphan*/  wa_tail; } ;

/* Variables and functions */
 int /*<<< orphan*/  MI_ARB_CHECK ; 
 int /*<<< orphan*/  MI_NOOP ; 
 int /*<<< orphan*/  intel_ring_offset (struct i915_request*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 *gen8_emit_wa_tail(struct i915_request *request, u32 *cs)
{
	/* Ensure there's always at least one preemption point per-request. */
	*cs++ = MI_ARB_CHECK;
	*cs++ = MI_NOOP;
	request->wa_tail = intel_ring_offset(request, cs);

	return cs;
}