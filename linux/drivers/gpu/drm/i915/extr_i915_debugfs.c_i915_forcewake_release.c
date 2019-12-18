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
struct file {scalar_t__ private_data; } ;
struct drm_i915_private {int /*<<< orphan*/  runtime_pm; int /*<<< orphan*/  uncore; } ;
typedef  int /*<<< orphan*/  intel_wakeref_t ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_user_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i915_forcewake_release(struct inode *inode, struct file *file)
{
	struct drm_i915_private *i915 = inode->i_private;

	if (INTEL_GEN(i915) < 6)
		return 0;

	intel_uncore_forcewake_user_put(&i915->uncore);
	intel_runtime_pm_put(&i915->runtime_pm,
			     (intel_wakeref_t)(uintptr_t)file->private_data);

	return 0;
}