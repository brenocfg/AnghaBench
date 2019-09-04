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
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE_FW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RESET_CTL_REQUEST_RESET ; 
 int /*<<< orphan*/  RING_RESET_CTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _MASKED_BIT_DISABLE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gen8_reset_engine_cancel(struct intel_engine_cs *engine)
{
	struct drm_i915_private *dev_priv = engine->i915;

	I915_WRITE_FW(RING_RESET_CTL(engine->mmio_base),
		      _MASKED_BIT_DISABLE(RESET_CTL_REQUEST_RESET));
}