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
struct intel_engine_cs {int /*<<< orphan*/  batch_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  i915_gem_batch_pool_init (int /*<<< orphan*/ *,struct intel_engine_cs*) ; 

__attribute__((used)) static void intel_engine_init_batch_pool(struct intel_engine_cs *engine)
{
	i915_gem_batch_pool_init(&engine->batch_pool, engine);
}