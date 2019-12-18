#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* primary; } ;
struct drm_i915_private {TYPE_2__ drm; } ;
struct device {int /*<<< orphan*/  kobj; } ;
struct TYPE_3__ {struct device* kdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 scalar_t__ HAS_L3_DPF (struct drm_i915_private*) ; 
 scalar_t__ HAS_RC6 (struct drm_i915_private*) ; 
 scalar_t__ HAS_RC6p (struct drm_i915_private*) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int NUM_L3_SLICES (struct drm_i915_private*) ; 
 int device_create_bin_file (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dpf_attrs ; 
 int /*<<< orphan*/  dpf_attrs_1 ; 
 int /*<<< orphan*/  gen6_attrs ; 
 int /*<<< orphan*/  i915_setup_error_capture (struct device*) ; 
 int /*<<< orphan*/  media_rc6_attr_group ; 
 int /*<<< orphan*/  rc6_attr_group ; 
 int /*<<< orphan*/  rc6p_attr_group ; 
 int sysfs_create_files (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sysfs_merge_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlv_attrs ; 

void i915_setup_sysfs(struct drm_i915_private *dev_priv)
{
	struct device *kdev = dev_priv->drm.primary->kdev;
	int ret;

#ifdef CONFIG_PM
	if (HAS_RC6(dev_priv)) {
		ret = sysfs_merge_group(&kdev->kobj,
					&rc6_attr_group);
		if (ret)
			DRM_ERROR("RC6 residency sysfs setup failed\n");
	}
	if (HAS_RC6p(dev_priv)) {
		ret = sysfs_merge_group(&kdev->kobj,
					&rc6p_attr_group);
		if (ret)
			DRM_ERROR("RC6p residency sysfs setup failed\n");
	}
	if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) {
		ret = sysfs_merge_group(&kdev->kobj,
					&media_rc6_attr_group);
		if (ret)
			DRM_ERROR("Media RC6 residency sysfs setup failed\n");
	}
#endif
	if (HAS_L3_DPF(dev_priv)) {
		ret = device_create_bin_file(kdev, &dpf_attrs);
		if (ret)
			DRM_ERROR("l3 parity sysfs setup failed\n");

		if (NUM_L3_SLICES(dev_priv) > 1) {
			ret = device_create_bin_file(kdev,
						     &dpf_attrs_1);
			if (ret)
				DRM_ERROR("l3 parity slice 1 setup failed\n");
		}
	}

	ret = 0;
	if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		ret = sysfs_create_files(&kdev->kobj, vlv_attrs);
	else if (INTEL_GEN(dev_priv) >= 6)
		ret = sysfs_create_files(&kdev->kobj, gen6_attrs);
	if (ret)
		DRM_ERROR("RPS sysfs setup failed\n");

	i915_setup_error_capture(kdev);
}