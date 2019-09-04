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
 int /*<<< orphan*/  intel_runtime_pm_get (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_user_get (struct drm_i915_private*) ; 

__attribute__((used)) static int i915_forcewake_open(struct inode *inode, struct file *file)
{
	struct drm_i915_private *i915 = inode->i_private;

	if (INTEL_GEN(i915) < 6)
		return 0;

	intel_runtime_pm_get(i915);
	intel_uncore_forcewake_user_get(i915);

	return 0;
}