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
struct TYPE_4__ {scalar_t__ active; TYPE_1__* crtc; } ;
struct intel_crtc_state {scalar_t__ port_clock; scalar_t__ shared_dpll; TYPE_2__ base; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool has_bogus_dpll_config(const struct intel_crtc_state *crtc_state)
{
	struct drm_i915_private *dev_priv = to_i915(crtc_state->base.crtc->dev);

	/*
	 * Some SNB BIOSen (eg. ASUS K53SV) are known to misprogram
	 * the hardware when a high res displays plugged in. DPLL P
	 * divider is zero, and the pipe timings are bonkers. We'll
	 * try to disable everything in that case.
	 *
	 * FIXME would be nice to be able to sanitize this state
	 * without several WARNs, but for now let's take the easy
	 * road.
	 */
	return IS_GEN(dev_priv, 6) &&
		crtc_state->base.active &&
		crtc_state->shared_dpll &&
		crtc_state->port_clock == 0;
}