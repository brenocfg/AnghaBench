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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  vma; } ;
struct intel_engine_cs {TYPE_1__ status_page; } ;

/* Variables and functions */
 scalar_t__ I915_GEM_HWS_PREEMPT_ADDR ; 
 scalar_t__ i915_ggtt_offset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 intel_hws_preempt_address(struct intel_engine_cs *engine)
{
	return (i915_ggtt_offset(engine->status_page.vma) +
		I915_GEM_HWS_PREEMPT_ADDR);
}