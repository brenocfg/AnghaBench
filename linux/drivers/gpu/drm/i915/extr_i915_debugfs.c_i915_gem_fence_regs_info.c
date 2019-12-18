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
struct i915_fence_reg {int /*<<< orphan*/  pin_count; struct i915_vma* vma; } ;
struct TYPE_2__ {unsigned int num_fences; struct i915_fence_reg* fence_regs; } ;
struct drm_i915_private {TYPE_1__ ggtt; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  describe_obj (struct seq_file*,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* node_to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,unsigned int,...) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int i915_gem_fence_regs_info(struct seq_file *m, void *data)
{
	struct drm_i915_private *i915 = node_to_i915(m->private);
	unsigned int i;

	seq_printf(m, "Total fences = %d\n", i915->ggtt.num_fences);

	rcu_read_lock();
	for (i = 0; i < i915->ggtt.num_fences; i++) {
		struct i915_fence_reg *reg = &i915->ggtt.fence_regs[i];
		struct i915_vma *vma = reg->vma;

		seq_printf(m, "Fence %d, pin count = %d, object = ",
			   i, atomic_read(&reg->pin_count));
		if (!vma)
			seq_puts(m, "unused");
		else
			describe_obj(m, vma->obj);
		seq_putc(m, '\n');
	}
	rcu_read_unlock();

	return 0;
}