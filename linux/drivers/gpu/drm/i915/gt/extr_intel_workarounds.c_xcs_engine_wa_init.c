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
struct intel_engine_cs {int /*<<< orphan*/  mmio_base; struct drm_i915_private* i915; } ;
struct i915_wa_list {int dummy; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_KBL_REVID (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KBL_REVID_A0 ; 
 int /*<<< orphan*/  KBL_REVID_E0 ; 
 int /*<<< orphan*/  RING_SEMA_WAIT_POLL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wa_write (struct i915_wa_list*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
xcs_engine_wa_init(struct intel_engine_cs *engine, struct i915_wa_list *wal)
{
	struct drm_i915_private *i915 = engine->i915;

	/* WaKBLVECSSemaphoreWaitPoll:kbl */
	if (IS_KBL_REVID(i915, KBL_REVID_A0, KBL_REVID_E0)) {
		wa_write(wal,
			 RING_SEMA_WAIT_POLL(engine->mmio_base),
			 1);
	}
}