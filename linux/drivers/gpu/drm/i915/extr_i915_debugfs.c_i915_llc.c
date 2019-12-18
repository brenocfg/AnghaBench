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
struct drm_i915_private {int /*<<< orphan*/  edram_size_mb; } ;

/* Variables and functions */
 int /*<<< orphan*/  HAS_LLC (struct drm_i915_private*) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 struct drm_i915_private* node_to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,...) ; 
 int /*<<< orphan*/  yesno (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i915_llc(struct seq_file *m, void *data)
{
	struct drm_i915_private *dev_priv = node_to_i915(m->private);
	const bool edram = INTEL_GEN(dev_priv) > 8;

	seq_printf(m, "LLC: %s\n", yesno(HAS_LLC(dev_priv)));
	seq_printf(m, "%s: %uMB\n", edram ? "eDRAM" : "eLLC",
		   dev_priv->edram_size_mb);

	return 0;
}