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
struct TYPE_3__ {int /*<<< orphan*/  batch; int /*<<< orphan*/  seeks; } ;
struct TYPE_4__ {TYPE_1__ shrinker; } ;
struct drm_i915_private {TYPE_2__ mm; } ;

/* Variables and functions */
 struct drm_i915_private* node_to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i915_shrinker_info(struct seq_file *m, void *unused)
{
	struct drm_i915_private *i915 = node_to_i915(m->private);

	seq_printf(m, "seeks = %d\n", i915->mm.shrinker.seeks);
	seq_printf(m, "batch = %lu\n", i915->mm.shrinker.batch);

	return 0;
}