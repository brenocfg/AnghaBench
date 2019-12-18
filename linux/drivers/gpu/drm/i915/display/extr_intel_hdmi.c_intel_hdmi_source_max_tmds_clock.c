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
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {size_t port; TYPE_1__ base; } ;
struct TYPE_4__ {struct ddi_vbt_port_info* ddi_port_info; } ;
struct drm_i915_private {TYPE_2__ vbt; } ;
struct ddi_vbt_port_info {scalar_t__ max_tmds_clock; } ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 int min (int,scalar_t__) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intel_hdmi_source_max_tmds_clock(struct intel_encoder *encoder)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	const struct ddi_vbt_port_info *info =
		&dev_priv->vbt.ddi_port_info[encoder->port];
	int max_tmds_clock;

	if (INTEL_GEN(dev_priv) >= 10 || IS_GEMINILAKE(dev_priv))
		max_tmds_clock = 594000;
	else if (INTEL_GEN(dev_priv) >= 8 || IS_HASWELL(dev_priv))
		max_tmds_clock = 300000;
	else if (INTEL_GEN(dev_priv) >= 5)
		max_tmds_clock = 225000;
	else
		max_tmds_clock = 165000;

	if (info->max_tmds_clock)
		max_tmds_clock = min(max_tmds_clock, info->max_tmds_clock);

	return max_tmds_clock;
}