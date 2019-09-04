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
struct intel_engine_cs {int /*<<< orphan*/  id; int /*<<< orphan*/  i915; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENGINE_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_device_reset(struct intel_engine_cs *engine)
{
	i915_reset(engine->i915, ENGINE_MASK(engine->id), NULL);
	return 0;
}