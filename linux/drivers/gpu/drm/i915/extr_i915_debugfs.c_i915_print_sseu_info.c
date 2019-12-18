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
struct sseu_dev_info {scalar_t__ has_eu_pg; scalar_t__ has_subslice_pg; scalar_t__ has_slice_pg; int /*<<< orphan*/  min_eu_in_pool; int /*<<< orphan*/  eu_per_subslice; int /*<<< orphan*/  eu_total; int /*<<< orphan*/  slice_mask; } ;
struct seq_file {int /*<<< orphan*/  private; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 scalar_t__ HAS_POOLED_EU (struct drm_i915_private*) ; 
 int fls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hweight8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_sseu_subslice_total (struct sseu_dev_info const*) ; 
 int /*<<< orphan*/  intel_sseu_subslices_per_slice (struct sseu_dev_info const*,int) ; 
 struct drm_i915_private* node_to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char const*,...) ; 
 int /*<<< orphan*/  yesno (scalar_t__) ; 

__attribute__((used)) static void i915_print_sseu_info(struct seq_file *m, bool is_available_info,
				 const struct sseu_dev_info *sseu)
{
	struct drm_i915_private *dev_priv = node_to_i915(m->private);
	const char *type = is_available_info ? "Available" : "Enabled";
	int s;

	seq_printf(m, "  %s Slice Mask: %04x\n", type,
		   sseu->slice_mask);
	seq_printf(m, "  %s Slice Total: %u\n", type,
		   hweight8(sseu->slice_mask));
	seq_printf(m, "  %s Subslice Total: %u\n", type,
		   intel_sseu_subslice_total(sseu));
	for (s = 0; s < fls(sseu->slice_mask); s++) {
		seq_printf(m, "  %s Slice%i subslices: %u\n", type,
			   s, intel_sseu_subslices_per_slice(sseu, s));
	}
	seq_printf(m, "  %s EU Total: %u\n", type,
		   sseu->eu_total);
	seq_printf(m, "  %s EU Per Subslice: %u\n", type,
		   sseu->eu_per_subslice);

	if (!is_available_info)
		return;

	seq_printf(m, "  Has Pooled EU: %s\n", yesno(HAS_POOLED_EU(dev_priv)));
	if (HAS_POOLED_EU(dev_priv))
		seq_printf(m, "  Min EU in pool: %u\n", sseu->min_eu_in_pool);

	seq_printf(m, "  Has Slice Power Gating: %s\n",
		   yesno(sseu->has_slice_pg));
	seq_printf(m, "  Has Subslice Power Gating: %s\n",
		   yesno(sseu->has_subslice_pg));
	seq_printf(m, "  Has EU Power Gating: %s\n",
		   yesno(sseu->has_eu_pg));
}