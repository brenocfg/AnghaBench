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
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int FORCE_DDR_FREQ_REQ_ACK ; 
 int FORCE_DDR_HIGH_FREQ ; 
 int FORCE_DDR_LOW_FREQ ; 
 int /*<<< orphan*/  PUNIT_REG_DDR_SETUP2 ; 
 int /*<<< orphan*/  vlv_punit_get (struct drm_i915_private*) ; 
 int /*<<< orphan*/  vlv_punit_put (struct drm_i915_private*) ; 
 int vlv_punit_read (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlv_punit_write (struct drm_i915_private*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ wait_for (int,int) ; 

__attribute__((used)) static void chv_set_memory_dvfs(struct drm_i915_private *dev_priv, bool enable)
{
	u32 val;

	vlv_punit_get(dev_priv);

	val = vlv_punit_read(dev_priv, PUNIT_REG_DDR_SETUP2);
	if (enable)
		val &= ~FORCE_DDR_HIGH_FREQ;
	else
		val |= FORCE_DDR_HIGH_FREQ;
	val &= ~FORCE_DDR_LOW_FREQ;
	val |= FORCE_DDR_FREQ_REQ_ACK;
	vlv_punit_write(dev_priv, PUNIT_REG_DDR_SETUP2, val);

	if (wait_for((vlv_punit_read(dev_priv, PUNIT_REG_DDR_SETUP2) &
		      FORCE_DDR_FREQ_REQ_ACK) == 0, 3))
		DRM_ERROR("timed out waiting for Punit DDR DVFS request\n");

	vlv_punit_put(dev_priv);
}