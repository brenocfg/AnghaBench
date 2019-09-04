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
struct drm_i915_private {int /*<<< orphan*/  pcu_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int ENXIO ; 
 int /*<<< orphan*/  HDCP_AKSV_SEND_TRIGGER ; 
 int /*<<< orphan*/  HDCP_KEY_CONF ; 
 int HDCP_KEY_LOAD_DONE ; 
 int HDCP_KEY_LOAD_STATUS ; 
 int /*<<< orphan*/  HDCP_KEY_LOAD_TRIGGER ; 
 int /*<<< orphan*/  HDCP_KEY_STATUS ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_KABYLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_SKYLAKE (struct drm_i915_private*) ; 
 int /*<<< orphan*/  SKL_PCODE_LOAD_HDCP_KEYS ; 
 int __intel_wait_for_register (struct drm_i915_private*,int /*<<< orphan*/ ,int,int,int,int,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sandybridge_pcode_write (struct drm_i915_private*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int intel_hdcp_load_keys(struct drm_i915_private *dev_priv)
{
	int ret;
	u32 val;

	val = I915_READ(HDCP_KEY_STATUS);
	if ((val & HDCP_KEY_LOAD_DONE) && (val & HDCP_KEY_LOAD_STATUS))
		return 0;

	/*
	 * On HSW and BDW HW loads the HDCP1.4 Key when Display comes
	 * out of reset. So if Key is not already loaded, its an error state.
	 */
	if (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv))
		if (!(I915_READ(HDCP_KEY_STATUS) & HDCP_KEY_LOAD_DONE))
			return -ENXIO;

	/*
	 * Initiate loading the HDCP key from fuses.
	 *
	 * BXT+ platforms, HDCP key needs to be loaded by SW. Only SKL and KBL
	 * differ in the key load trigger process from other platforms.
	 */
	if (IS_SKYLAKE(dev_priv) || IS_KABYLAKE(dev_priv)) {
		mutex_lock(&dev_priv->pcu_lock);
		ret = sandybridge_pcode_write(dev_priv,
					      SKL_PCODE_LOAD_HDCP_KEYS, 1);
		mutex_unlock(&dev_priv->pcu_lock);
		if (ret) {
			DRM_ERROR("Failed to initiate HDCP key load (%d)\n",
			          ret);
			return ret;
		}
	} else {
		I915_WRITE(HDCP_KEY_CONF, HDCP_KEY_LOAD_TRIGGER);
	}

	/* Wait for the keys to load (500us) */
	ret = __intel_wait_for_register(dev_priv, HDCP_KEY_STATUS,
					HDCP_KEY_LOAD_DONE, HDCP_KEY_LOAD_DONE,
					10, 1, &val);
	if (ret)
		return ret;
	else if (!(val & HDCP_KEY_LOAD_STATUS))
		return -ENXIO;

	/* Send Aksv over to PCH display for use in authentication */
	I915_WRITE(HDCP_KEY_CONF, HDCP_AKSV_SEND_TRIGGER);

	return 0;
}