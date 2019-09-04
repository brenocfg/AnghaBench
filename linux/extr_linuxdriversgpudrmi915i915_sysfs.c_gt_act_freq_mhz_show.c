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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  GEN6_RPSTAT1 ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PUNIT_REG_GPU_FREQ_STS ; 
 int intel_get_cagf (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int intel_gpu_freq (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_runtime_pm_get (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (struct drm_i915_private*) ; 
 struct drm_i915_private* kdev_minor_to_i915 (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int vlv_punit_read (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t gt_act_freq_mhz_show(struct device *kdev,
				    struct device_attribute *attr, char *buf)
{
	struct drm_i915_private *dev_priv = kdev_minor_to_i915(kdev);
	int ret;

	intel_runtime_pm_get(dev_priv);

	mutex_lock(&dev_priv->pcu_lock);
	if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) {
		u32 freq;
		freq = vlv_punit_read(dev_priv, PUNIT_REG_GPU_FREQ_STS);
		ret = intel_gpu_freq(dev_priv, (freq >> 8) & 0xff);
	} else {
		ret = intel_gpu_freq(dev_priv,
				     intel_get_cagf(dev_priv,
						    I915_READ(GEN6_RPSTAT1)));
	}
	mutex_unlock(&dev_priv->pcu_lock);

	intel_runtime_pm_put(dev_priv);

	return snprintf(buf, PAGE_SIZE, "%d\n", ret);
}