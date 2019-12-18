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
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  device_remove_bin_file (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dpf_attrs ; 
 int /*<<< orphan*/  dpf_attrs_1 ; 
 int /*<<< orphan*/  gen6_attrs ; 
 int /*<<< orphan*/  i915_teardown_error_capture (struct device*) ; 
 int /*<<< orphan*/  rc6_attr_group ; 
 int /*<<< orphan*/  rc6p_attr_group ; 
 int /*<<< orphan*/  sysfs_remove_files (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_unmerge_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlv_attrs ; 

void i915_teardown_sysfs(struct drm_i915_private *dev_priv)
{
	struct device *kdev = dev_priv->drm.primary->kdev;

	i915_teardown_error_capture(kdev);

	if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		sysfs_remove_files(&kdev->kobj, vlv_attrs);
	else
		sysfs_remove_files(&kdev->kobj, gen6_attrs);
	device_remove_bin_file(kdev,  &dpf_attrs_1);
	device_remove_bin_file(kdev,  &dpf_attrs);
#ifdef CONFIG_PM
	sysfs_unmerge_group(&kdev->kobj, &rc6_attr_group);
	sysfs_unmerge_group(&kdev->kobj, &rc6p_attr_group);
#endif
}