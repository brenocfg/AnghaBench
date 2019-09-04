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
struct inode {struct drm_i915_private* i_private; } ;
struct file {int dummy; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_user_put (struct drm_i915_private*) ; 

__attribute__((used)) static int i915_forcewake_release(struct inode *inode, struct file *file)
{
	struct drm_i915_private *i915 = inode->i_private;

	if (INTEL_GEN(i915) < 6)
		return 0;

	intel_uncore_forcewake_user_put(i915);
	intel_runtime_pm_put(i915);

	return 0;
}