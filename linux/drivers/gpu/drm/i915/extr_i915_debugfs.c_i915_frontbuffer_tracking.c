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
struct TYPE_2__ {int /*<<< orphan*/  flip_bits; int /*<<< orphan*/  busy_bits; } ;
struct drm_i915_private {TYPE_1__ fb_tracking; } ;

/* Variables and functions */
 struct drm_i915_private* node_to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i915_frontbuffer_tracking(struct seq_file *m, void *unused)
{
	struct drm_i915_private *dev_priv = node_to_i915(m->private);

	seq_printf(m, "FB tracking busy bits: 0x%08x\n",
		   dev_priv->fb_tracking.busy_bits);

	seq_printf(m, "FB tracking flip bits: 0x%08x\n",
		   dev_priv->fb_tracking.flip_bits);

	return 0;
}