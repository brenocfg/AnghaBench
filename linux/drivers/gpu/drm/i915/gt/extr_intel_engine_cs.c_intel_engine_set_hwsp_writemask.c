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
struct intel_engine_cs {scalar_t__ class; int /*<<< orphan*/  i915; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENGINE_WRITE (struct intel_engine_cs*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_WRITE16 (struct intel_engine_cs*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int INTEL_GEN (int /*<<< orphan*/ ) ; 
 scalar_t__ RENDER_CLASS ; 
 int /*<<< orphan*/  RING_HWSTAM ; 

void intel_engine_set_hwsp_writemask(struct intel_engine_cs *engine, u32 mask)
{
	/*
	 * Though they added more rings on g4x/ilk, they did not add
	 * per-engine HWSTAM until gen6.
	 */
	if (INTEL_GEN(engine->i915) < 6 && engine->class != RENDER_CLASS)
		return;

	if (INTEL_GEN(engine->i915) >= 3)
		ENGINE_WRITE(engine, RING_HWSTAM, mask);
	else
		ENGINE_WRITE16(engine, RING_HWSTAM, mask);
}