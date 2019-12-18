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
struct TYPE_2__ {int /*<<< orphan*/  vma; } ;
struct intel_engine_cs {TYPE_1__ status_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_cs_tlb (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  i915_ggtt_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_hwsp (struct intel_engine_cs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_hwstam (struct intel_engine_cs*,unsigned int) ; 

__attribute__((used)) static void ring_setup_status_page(struct intel_engine_cs *engine)
{
	set_hwsp(engine, i915_ggtt_offset(engine->status_page.vma));
	set_hwstam(engine, ~0u);

	flush_cs_tlb(engine);
}