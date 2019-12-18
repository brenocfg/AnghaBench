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
typedef  scalar_t__ u32 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_STATE_EN ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,scalar_t__,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void gen9_write_dc_state(struct drm_i915_private *dev_priv,
				u32 state)
{
	int rewrites = 0;
	int rereads = 0;
	u32 v;

	I915_WRITE(DC_STATE_EN, state);

	/* It has been observed that disabling the dc6 state sometimes
	 * doesn't stick and dmc keeps returning old value. Make sure
	 * the write really sticks enough times and also force rewrite until
	 * we are confident that state is exactly what we want.
	 */
	do  {
		v = I915_READ(DC_STATE_EN);

		if (v != state) {
			I915_WRITE(DC_STATE_EN, state);
			rewrites++;
			rereads = 0;
		} else if (rereads++ > 5) {
			break;
		}

	} while (rewrites < 100);

	if (v != state)
		DRM_ERROR("Writing dc state to 0x%x failed, now 0x%x\n",
			  state, v);

	/* Most of the times we need one retry, avoid spam */
	if (rewrites > 1)
		DRM_DEBUG_KMS("Rewrote dc state to 0x%x %d times\n",
			      state, rewrites);
}