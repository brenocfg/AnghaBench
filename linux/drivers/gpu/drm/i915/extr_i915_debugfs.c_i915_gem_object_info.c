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
struct seq_file {int /*<<< orphan*/  private; } ;
struct TYPE_3__ {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_4__ {int /*<<< orphan*/  shrink_memory; int /*<<< orphan*/  free_count; int /*<<< orphan*/  shrink_count; } ;
struct drm_i915_private {TYPE_1__ drm; TYPE_2__ mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* node_to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_context_stats (struct seq_file*,struct drm_i915_private*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 

__attribute__((used)) static int i915_gem_object_info(struct seq_file *m, void *data)
{
	struct drm_i915_private *i915 = node_to_i915(m->private);
	int ret;

	seq_printf(m, "%u shrinkable [%u free] objects, %llu bytes\n",
		   i915->mm.shrink_count,
		   atomic_read(&i915->mm.free_count),
		   i915->mm.shrink_memory);

	seq_putc(m, '\n');

	ret = mutex_lock_interruptible(&i915->drm.struct_mutex);
	if (ret)
		return ret;

	print_context_stats(m, i915);
	mutex_unlock(&i915->drm.struct_mutex);

	return 0;
}