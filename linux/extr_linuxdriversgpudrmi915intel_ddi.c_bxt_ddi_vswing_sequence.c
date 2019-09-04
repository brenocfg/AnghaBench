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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {int port; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
struct bxt_ddi_buf_trans {int /*<<< orphan*/  deemphasis; int /*<<< orphan*/  enable; int /*<<< orphan*/  scale; int /*<<< orphan*/  margin; } ;
typedef  enum port { ____Placeholder_port } port ;
typedef  enum intel_output_type { ____Placeholder_intel_output_type } intel_output_type ;

/* Variables and functions */
 int INTEL_OUTPUT_EDP ; 
 int INTEL_OUTPUT_HDMI ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  bxt_ddi_phy_set_signal_level (struct drm_i915_private*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bxt_ddi_buf_trans* bxt_get_buf_trans_dp (struct drm_i915_private*,int*) ; 
 struct bxt_ddi_buf_trans* bxt_get_buf_trans_edp (struct drm_i915_private*,int*) ; 
 struct bxt_ddi_buf_trans* bxt_get_buf_trans_hdmi (struct drm_i915_private*,int*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bxt_ddi_vswing_sequence(struct intel_encoder *encoder,
				    int level, enum intel_output_type type)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	const struct bxt_ddi_buf_trans *ddi_translations;
	enum port port = encoder->port;
	int n_entries;

	if (type == INTEL_OUTPUT_HDMI)
		ddi_translations = bxt_get_buf_trans_hdmi(dev_priv, &n_entries);
	else if (type == INTEL_OUTPUT_EDP)
		ddi_translations = bxt_get_buf_trans_edp(dev_priv, &n_entries);
	else
		ddi_translations = bxt_get_buf_trans_dp(dev_priv, &n_entries);

	if (WARN_ON_ONCE(!ddi_translations))
		return;
	if (WARN_ON_ONCE(level >= n_entries))
		level = n_entries - 1;

	bxt_ddi_phy_set_signal_level(dev_priv, port,
				     ddi_translations[level].margin,
				     ddi_translations[level].scale,
				     ddi_translations[level].enable,
				     ddi_translations[level].deemphasis);
}