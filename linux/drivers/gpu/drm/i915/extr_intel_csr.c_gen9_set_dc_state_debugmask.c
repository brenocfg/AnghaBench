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
typedef  int u32 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_STATE_DEBUG ; 
 int DC_STATE_DEBUG_MASK_CORES ; 
 int DC_STATE_DEBUG_MASK_MEMORY_UP ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gen9_set_dc_state_debugmask(struct drm_i915_private *dev_priv)
{
	u32 val, mask;

	mask = DC_STATE_DEBUG_MASK_MEMORY_UP;

	if (IS_GEN9_LP(dev_priv))
		mask |= DC_STATE_DEBUG_MASK_CORES;

	/* The below bit doesn't need to be cleared ever afterwards */
	val = I915_READ(DC_STATE_DEBUG);
	if ((val & mask) != mask) {
		val |= mask;
		I915_WRITE(DC_STATE_DEBUG, val);
		POSTING_READ(DC_STATE_DEBUG);
	}
}