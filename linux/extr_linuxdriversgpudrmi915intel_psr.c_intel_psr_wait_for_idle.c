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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {int /*<<< orphan*/  has_psr; TYPE_1__ base; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {TYPE_2__ base; } ;
struct TYPE_6__ {scalar_t__ psr2_enabled; } ;
struct drm_i915_private {TYPE_3__ psr; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 int /*<<< orphan*/  EDP_PSR2_STATUS ; 
 int /*<<< orphan*/  EDP_PSR2_STATUS_STATE_MASK ; 
 int /*<<< orphan*/  EDP_PSR_STATUS ; 
 int /*<<< orphan*/  EDP_PSR_STATUS_STATE_IDLE ; 
 int /*<<< orphan*/  EDP_PSR_STATUS_STATE_MASK ; 
 int intel_wait_for_register (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

int intel_psr_wait_for_idle(const struct intel_crtc_state *new_crtc_state)
{
	struct intel_crtc *crtc = to_intel_crtc(new_crtc_state->base.crtc);
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	i915_reg_t reg;
	u32 mask;

	if (!new_crtc_state->has_psr)
		return 0;

	/*
	 * The sole user right now is intel_pipe_update_start(),
	 * which won't race with psr_enable/disable, which is
	 * where psr2_enabled is written to. So, we don't need
	 * to acquire the psr.lock. More importantly, we want the
	 * latency inside intel_pipe_update_start() to be as low
	 * as possible, so no need to acquire psr.lock when it is
	 * not needed and will induce latencies in the atomic
	 * update path.
	 */
	if (dev_priv->psr.psr2_enabled) {
		reg = EDP_PSR2_STATUS;
		mask = EDP_PSR2_STATUS_STATE_MASK;
	} else {
		reg = EDP_PSR_STATUS;
		mask = EDP_PSR_STATUS_STATE_MASK;
	}

	/*
	 * Max time for PSR to idle = Inverse of the refresh rate +
	 * 6 ms of exit training time + 1.5 ms of aux channel
	 * handshake. 50 msec is defesive enough to cover everything.
	 */
	return intel_wait_for_register(dev_priv, reg, mask,
				       EDP_PSR_STATUS_STATE_IDLE, 50);
}