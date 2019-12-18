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
struct TYPE_2__ {int* addr; } ;
struct intel_engine_cs {TYPE_1__ status_page; } ;

/* Variables and functions */
 size_t I915_GEM_HWS_PREEMPT ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline void
ring_set_paused(const struct intel_engine_cs *engine, int state)
{
	/*
	 * We inspect HWS_PREEMPT with a semaphore inside
	 * engine->emit_fini_breadcrumb. If the dword is true,
	 * the ring is paused as the semaphore will busywait
	 * until the dword is false.
	 */
	engine->status_page.addr[I915_GEM_HWS_PREEMPT] = state;
	if (state)
		wmb();
}