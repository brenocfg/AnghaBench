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
typedef  int /*<<< orphan*/  u32 ;
struct intel_dp {int dummy; } ;
struct intel_digital_port {scalar_t__ aux_ch; } ;
struct TYPE_3__ {int /*<<< orphan*/  cdclk; } ;
struct TYPE_4__ {TYPE_1__ hw; } ;
struct drm_i915_private {int /*<<< orphan*/  rawclk_freq; TYPE_2__ cdclk; } ;

/* Variables and functions */
 scalar_t__ AUX_CH_A ; 
 int /*<<< orphan*/  DIV_ROUND_CLOSEST (int /*<<< orphan*/ ,int) ; 
 struct intel_digital_port* dp_to_dig_port (struct intel_dp*) ; 
 struct drm_i915_private* dp_to_i915 (struct intel_dp*) ; 

__attribute__((used)) static u32 ilk_get_aux_clock_divider(struct intel_dp *intel_dp, int index)
{
	struct drm_i915_private *dev_priv = dp_to_i915(intel_dp);
	struct intel_digital_port *dig_port = dp_to_dig_port(intel_dp);

	if (index)
		return 0;

	/*
	 * The clock divider is based off the cdclk or PCH rawclk, and would
	 * like to run at 2MHz.  So, take the cdclk or PCH rawclk value and
	 * divide by 2000 and use that
	 */
	if (dig_port->aux_ch == AUX_CH_A)
		return DIV_ROUND_CLOSEST(dev_priv->cdclk.hw.cdclk, 2000);
	else
		return DIV_ROUND_CLOSEST(dev_priv->rawclk_freq, 2000);
}