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
struct intel_engine_cs {int /*<<< orphan*/  (* irq_seqno_barrier ) (struct intel_engine_cs*) ;} ;
struct i915_request {int dummy; } ;

/* Variables and functions */
 struct i915_request* i915_gem_find_active_request (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_engine_stop_cs (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  stub1 (struct intel_engine_cs*) ; 

__attribute__((used)) static struct i915_request *reset_prepare(struct intel_engine_cs *engine)
{
	intel_engine_stop_cs(engine);

	if (engine->irq_seqno_barrier)
		engine->irq_seqno_barrier(engine);

	return i915_gem_find_active_request(engine);
}