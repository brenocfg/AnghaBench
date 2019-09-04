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
struct intel_engine_cs {int /*<<< orphan*/  name; int /*<<< orphan*/  mmio_base; struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 int ENODEV ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GEM_TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE_FW (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  MODE_IDLE ; 
 int /*<<< orphan*/  POSTING_READ_FW (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  RING_MI_MODE (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  STOP_RING ; 
 int /*<<< orphan*/  _MASKED_BIT_ENABLE (int /*<<< orphan*/ ) ; 
 scalar_t__ __intel_wait_for_register_fw (struct drm_i915_private*,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int intel_engine_stop_cs(struct intel_engine_cs *engine)
{
	struct drm_i915_private *dev_priv = engine->i915;
	const u32 base = engine->mmio_base;
	const i915_reg_t mode = RING_MI_MODE(base);
	int err;

	if (INTEL_GEN(dev_priv) < 3)
		return -ENODEV;

	GEM_TRACE("%s\n", engine->name);

	I915_WRITE_FW(mode, _MASKED_BIT_ENABLE(STOP_RING));

	err = 0;
	if (__intel_wait_for_register_fw(dev_priv,
					 mode, MODE_IDLE, MODE_IDLE,
					 1000, 0,
					 NULL)) {
		GEM_TRACE("%s: timed out on STOP_RING -> IDLE\n", engine->name);
		err = -ETIMEDOUT;
	}

	/* A final mmio read to let GPU writes be hopefully flushed to memory */
	POSTING_READ_FW(mode);

	return err;
}