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
struct intel_renderstate_rodata {int dummy; } ;
struct intel_engine_cs {scalar_t__ class; int /*<<< orphan*/  i915; } ;

/* Variables and functions */
 int INTEL_GEN (int /*<<< orphan*/ ) ; 
 scalar_t__ RENDER_CLASS ; 
 struct intel_renderstate_rodata const gen6_null_state ; 
 struct intel_renderstate_rodata const gen7_null_state ; 
 struct intel_renderstate_rodata const gen8_null_state ; 
 struct intel_renderstate_rodata const gen9_null_state ; 

__attribute__((used)) static const struct intel_renderstate_rodata *
render_state_get_rodata(const struct intel_engine_cs *engine)
{
	if (engine->class != RENDER_CLASS)
		return NULL;

	switch (INTEL_GEN(engine->i915)) {
	case 6:
		return &gen6_null_state;
	case 7:
		return &gen7_null_state;
	case 8:
		return &gen8_null_state;
	case 9:
		return &gen9_null_state;
	}

	return NULL;
}