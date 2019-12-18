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
struct seq_file {int /*<<< orphan*/  private; } ;
struct intel_opregion {scalar_t__ header; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {struct intel_opregion opregion; struct drm_device drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPREGION_SIZE ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* node_to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_write (struct seq_file*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i915_opregion(struct seq_file *m, void *unused)
{
	struct drm_i915_private *dev_priv = node_to_i915(m->private);
	struct drm_device *dev = &dev_priv->drm;
	struct intel_opregion *opregion = &dev_priv->opregion;
	int ret;

	ret = mutex_lock_interruptible(&dev->struct_mutex);
	if (ret)
		goto out;

	if (opregion->header)
		seq_write(m, opregion->header, OPREGION_SIZE);

	mutex_unlock(&dev->struct_mutex);

out:
	return 0;
}