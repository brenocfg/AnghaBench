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
struct TYPE_5__ {int /*<<< orphan*/  crtc_clock; } ;
struct TYPE_6__ {TYPE_2__ adjusted_mode; } ;
struct intel_crtc_state {int /*<<< orphan*/  fdi_m_n; TYPE_3__ base; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i9xx_crtc_clock_get (struct intel_crtc*,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_dotclock_calculate (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_fdi_link_freq (struct drm_i915_private*,struct intel_crtc_state*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ironlake_pch_clock_get(struct intel_crtc *crtc,
				   struct intel_crtc_state *pipe_config)
{
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);

	/* read out port_clock from the DPLL */
	i9xx_crtc_clock_get(crtc, pipe_config);

	/*
	 * In case there is an active pipe without active ports,
	 * we may need some idea for the dotclock anyway.
	 * Calculate one based on the FDI configuration.
	 */
	pipe_config->base.adjusted_mode.crtc_clock =
		intel_dotclock_calculate(intel_fdi_link_freq(dev_priv, pipe_config),
					 &pipe_config->fdi_m_n);
}