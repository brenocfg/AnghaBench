#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int /*<<< orphan*/  private; } ;
struct i915_vma {int /*<<< orphan*/  obj; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {int num_fence_regs; TYPE_1__* fence_regs; struct drm_device drm; } ;
struct TYPE_2__ {int /*<<< orphan*/  pin_count; struct i915_vma* vma; } ;

/* Variables and functions */
 int /*<<< orphan*/  describe_obj (struct seq_file*,int /*<<< orphan*/ ) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* node_to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,...) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int i915_gem_fence_regs_info(struct seq_file *m, void *data)
{
	struct drm_i915_private *dev_priv = node_to_i915(m->private);
	struct drm_device *dev = &dev_priv->drm;
	int i, ret;

	ret = mutex_lock_interruptible(&dev->struct_mutex);
	if (ret)
		return ret;

	seq_printf(m, "Total fences = %d\n", dev_priv->num_fence_regs);
	for (i = 0; i < dev_priv->num_fence_regs; i++) {
		struct i915_vma *vma = dev_priv->fence_regs[i].vma;

		seq_printf(m, "Fence %d, pin count = %d, object = ",
			   i, dev_priv->fence_regs[i].pin_count);
		if (!vma)
			seq_puts(m, "unused");
		else
			describe_obj(m, vma->obj);
		seq_putc(m, '\n');
	}

	mutex_unlock(&dev->struct_mutex);
	return 0;
}