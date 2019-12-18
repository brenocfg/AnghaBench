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
struct file {void* private_data; } ;
struct drm_i915_private {int /*<<< orphan*/  uncore; int /*<<< orphan*/  runtime_pm; } ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ intel_runtime_pm_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_user_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i915_forcewake_open(struct inode *inode, struct file *file)
{
	struct drm_i915_private *i915 = inode->i_private;

	if (INTEL_GEN(i915) < 6)
		return 0;

	file->private_data =
		(void *)(uintptr_t)intel_runtime_pm_get(&i915->runtime_pm);
	intel_uncore_forcewake_user_get(&i915->uncore);

	return 0;
}