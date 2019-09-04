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
struct TYPE_2__ {int /*<<< orphan*/  bit_6_swizzle_y; int /*<<< orphan*/  bit_6_swizzle_x; } ;
struct drm_i915_private {int quirks; TYPE_1__ mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARB_MODE ; 
 int /*<<< orphan*/  C0DRB3 ; 
 int /*<<< orphan*/  C1DRB3 ; 
 int /*<<< orphan*/  DCC ; 
 int /*<<< orphan*/  DCC2 ; 
 int /*<<< orphan*/  DISP_ARB_CTL ; 
 int /*<<< orphan*/  GAMTARBMODE ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_READ16 (int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN3 (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN4 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  MAD_DIMM_C0 ; 
 int /*<<< orphan*/  MAD_DIMM_C1 ; 
 int /*<<< orphan*/  MAD_DIMM_C2 ; 
 int QUIRK_PIN_SWIZZLED_PAGES ; 
 int /*<<< orphan*/  TILECTL ; 
 int /*<<< orphan*/  intel_runtime_pm_get (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (struct drm_i915_private*) ; 
 struct drm_i915_private* node_to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  swizzle_string (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i915_swizzle_info(struct seq_file *m, void *data)
{
	struct drm_i915_private *dev_priv = node_to_i915(m->private);

	intel_runtime_pm_get(dev_priv);

	seq_printf(m, "bit6 swizzle for X-tiling = %s\n",
		   swizzle_string(dev_priv->mm.bit_6_swizzle_x));
	seq_printf(m, "bit6 swizzle for Y-tiling = %s\n",
		   swizzle_string(dev_priv->mm.bit_6_swizzle_y));

	if (IS_GEN3(dev_priv) || IS_GEN4(dev_priv)) {
		seq_printf(m, "DDC = 0x%08x\n",
			   I915_READ(DCC));
		seq_printf(m, "DDC2 = 0x%08x\n",
			   I915_READ(DCC2));
		seq_printf(m, "C0DRB3 = 0x%04x\n",
			   I915_READ16(C0DRB3));
		seq_printf(m, "C1DRB3 = 0x%04x\n",
			   I915_READ16(C1DRB3));
	} else if (INTEL_GEN(dev_priv) >= 6) {
		seq_printf(m, "MAD_DIMM_C0 = 0x%08x\n",
			   I915_READ(MAD_DIMM_C0));
		seq_printf(m, "MAD_DIMM_C1 = 0x%08x\n",
			   I915_READ(MAD_DIMM_C1));
		seq_printf(m, "MAD_DIMM_C2 = 0x%08x\n",
			   I915_READ(MAD_DIMM_C2));
		seq_printf(m, "TILECTL = 0x%08x\n",
			   I915_READ(TILECTL));
		if (INTEL_GEN(dev_priv) >= 8)
			seq_printf(m, "GAMTARBMODE = 0x%08x\n",
				   I915_READ(GAMTARBMODE));
		else
			seq_printf(m, "ARB_MODE = 0x%08x\n",
				   I915_READ(ARB_MODE));
		seq_printf(m, "DISP_ARB_CTL = 0x%08x\n",
			   I915_READ(DISP_ARB_CTL));
	}

	if (dev_priv->quirks & QUIRK_PIN_SWIZZLED_PAGES)
		seq_puts(m, "L-shaped memory detected\n");

	intel_runtime_pm_put(dev_priv);

	return 0;
}