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
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  intel_rc6_residency_us (struct drm_i915_private*,int /*<<< orphan*/  const) ; 
 struct drm_i915_private* node_to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_rc6_res(struct seq_file *m,
			  const char *title,
			  const i915_reg_t reg)
{
	struct drm_i915_private *dev_priv = node_to_i915(m->private);

	seq_printf(m, "%s %u (%llu us)\n",
		   title, I915_READ(reg),
		   intel_rc6_residency_us(dev_priv, reg));
}