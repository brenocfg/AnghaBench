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
struct intel_engine_cs {int /*<<< orphan*/  class; int /*<<< orphan*/  i915; } ;

/* Variables and functions */
 int INTEL_GEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_I915G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_I915GM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIDEO_DECODE_CLASS ; 

bool intel_engine_can_store_dword(struct intel_engine_cs *engine)
{
	switch (INTEL_GEN(engine->i915)) {
	case 2:
		return false; /* uses physical not virtual addresses */
	case 3:
		/* maybe only uses physical not virtual addresses */
		return !(IS_I915G(engine->i915) || IS_I915GM(engine->i915));
	case 6:
		return engine->class != VIDEO_DECODE_CLASS; /* b0rked */
	default:
		return true;
	}
}