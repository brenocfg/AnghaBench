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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  vma; } ;
struct intel_engine_cs {TYPE_1__ status_page; int /*<<< orphan*/  i915; int /*<<< orphan*/  uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENGINE_POSTING_READ (struct intel_engine_cs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_WRITE_FW (struct intel_engine_cs*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FORCEWAKE_ALL ; 
 int /*<<< orphan*/  GEN11_GFX_DISABLE_LEGACY_MODE ; 
 int /*<<< orphan*/  GFX_RUN_LIST_ENABLE ; 
 int INTEL_GEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_HWS_PGA ; 
 int /*<<< orphan*/  RING_MI_MODE ; 
 int /*<<< orphan*/  RING_MODE_GEN7 ; 
 int /*<<< orphan*/  STOP_RING ; 
 int /*<<< orphan*/  _MASKED_BIT_DISABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _MASKED_BIT_ENABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_forcewakes_active (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_ggtt_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_engine_set_hwsp_writemask (struct intel_engine_cs*,unsigned int) ; 

__attribute__((used)) static void enable_execlists(struct intel_engine_cs *engine)
{
	u32 mode;

	assert_forcewakes_active(engine->uncore, FORCEWAKE_ALL);

	intel_engine_set_hwsp_writemask(engine, ~0u); /* HWSTAM */

	if (INTEL_GEN(engine->i915) >= 11)
		mode = _MASKED_BIT_ENABLE(GEN11_GFX_DISABLE_LEGACY_MODE);
	else
		mode = _MASKED_BIT_ENABLE(GFX_RUN_LIST_ENABLE);
	ENGINE_WRITE_FW(engine, RING_MODE_GEN7, mode);

	ENGINE_WRITE_FW(engine, RING_MI_MODE, _MASKED_BIT_DISABLE(STOP_RING));

	ENGINE_WRITE_FW(engine,
			RING_HWS_PGA,
			i915_ggtt_offset(engine->status_page.vma));
	ENGINE_POSTING_READ(engine, RING_HWS_PGA);
}