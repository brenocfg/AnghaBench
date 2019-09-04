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
typedef  int /*<<< orphan*/  u32 ;
struct intel_crtc_state {int /*<<< orphan*/  port_clock; } ;
struct drm_i915_private {int /*<<< orphan*/  fdi_pll_freq; } ;

/* Variables and functions */
 scalar_t__ HAS_DDI (struct drm_i915_private*) ; 

__attribute__((used)) static inline u32 /* units of 100MHz */
intel_fdi_link_freq(struct drm_i915_private *dev_priv,
		    const struct intel_crtc_state *pipe_config)
{
	if (HAS_DDI(dev_priv))
		return pipe_config->port_clock; /* SPLL */
	else
		return dev_priv->fdi_pll_freq;
}