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
struct i915_request {int /*<<< orphan*/  engine; } ;

/* Variables and functions */
 int MI_SEMAPHORE_GLOBAL_GTT ; 
 int MI_SEMAPHORE_POLL ; 
 int MI_SEMAPHORE_SAD_EQ_SDD ; 
 int MI_SEMAPHORE_WAIT ; 
 int /*<<< orphan*/  intel_hws_preempt_address (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 *emit_preempt_busywait(struct i915_request *request, u32 *cs)
{
	*cs++ = MI_SEMAPHORE_WAIT |
		MI_SEMAPHORE_GLOBAL_GTT |
		MI_SEMAPHORE_POLL |
		MI_SEMAPHORE_SAD_EQ_SDD;
	*cs++ = 0;
	*cs++ = intel_hws_preempt_address(request->engine);
	*cs++ = 0;

	return cs;
}