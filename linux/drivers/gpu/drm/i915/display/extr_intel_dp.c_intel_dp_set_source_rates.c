#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct intel_dp {int const* source_rates; int num_source_rates; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {size_t port; TYPE_1__ base; } ;
struct intel_digital_port {TYPE_3__ base; } ;
struct TYPE_5__ {struct ddi_vbt_port_info* ddi_port_info; } ;
struct drm_i915_private {TYPE_2__ vbt; } ;
struct ddi_vbt_port_info {int dp_max_link_rate; } ;

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 scalar_t__ IS_GEN9_BC (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_HSW_ULX (struct drm_i915_private*) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int cnl_max_source_rate (struct intel_dp*) ; 
 struct intel_digital_port* dp_to_dig_port (struct intel_dp*) ; 
 int icl_max_source_rate (struct intel_dp*) ; 
 int intel_dp_rate_limit_len (int const*,int,int) ; 
 int min (int,int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
intel_dp_set_source_rates(struct intel_dp *intel_dp)
{
	/* The values must be in increasing order */
	static const int cnl_rates[] = {
		162000, 216000, 270000, 324000, 432000, 540000, 648000, 810000
	};
	static const int bxt_rates[] = {
		162000, 216000, 243000, 270000, 324000, 432000, 540000
	};
	static const int skl_rates[] = {
		162000, 216000, 270000, 324000, 432000, 540000
	};
	static const int hsw_rates[] = {
		162000, 270000, 540000
	};
	static const int g4x_rates[] = {
		162000, 270000
	};
	struct intel_digital_port *dig_port = dp_to_dig_port(intel_dp);
	struct drm_i915_private *dev_priv = to_i915(dig_port->base.base.dev);
	const struct ddi_vbt_port_info *info =
		&dev_priv->vbt.ddi_port_info[dig_port->base.port];
	const int *source_rates;
	int size, max_rate = 0, vbt_max_rate = info->dp_max_link_rate;

	/* This should only be done once */
	WARN_ON(intel_dp->source_rates || intel_dp->num_source_rates);

	if (INTEL_GEN(dev_priv) >= 10) {
		source_rates = cnl_rates;
		size = ARRAY_SIZE(cnl_rates);
		if (IS_GEN(dev_priv, 10))
			max_rate = cnl_max_source_rate(intel_dp);
		else
			max_rate = icl_max_source_rate(intel_dp);
	} else if (IS_GEN9_LP(dev_priv)) {
		source_rates = bxt_rates;
		size = ARRAY_SIZE(bxt_rates);
	} else if (IS_GEN9_BC(dev_priv)) {
		source_rates = skl_rates;
		size = ARRAY_SIZE(skl_rates);
	} else if ((IS_HASWELL(dev_priv) && !IS_HSW_ULX(dev_priv)) ||
		   IS_BROADWELL(dev_priv)) {
		source_rates = hsw_rates;
		size = ARRAY_SIZE(hsw_rates);
	} else {
		source_rates = g4x_rates;
		size = ARRAY_SIZE(g4x_rates);
	}

	if (max_rate && vbt_max_rate)
		max_rate = min(max_rate, vbt_max_rate);
	else if (vbt_max_rate)
		max_rate = vbt_max_rate;

	if (max_rate)
		size = intel_dp_rate_limit_len(source_rates, size, max_rate);

	intel_dp->source_rates = source_rates;
	intel_dp->num_source_rates = size;
}