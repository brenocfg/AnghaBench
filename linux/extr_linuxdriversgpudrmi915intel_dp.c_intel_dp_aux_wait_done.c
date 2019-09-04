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
typedef  int uint32_t ;
struct intel_dp {int /*<<< orphan*/  (* aux_ch_ctl_reg ) (struct intel_dp*) ;} ;
struct drm_i915_private {int /*<<< orphan*/  gmbus_wait_queue; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 int DP_AUX_CH_CTL_SEND_BUSY ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int I915_READ_NOTRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_dp_to_dev (struct intel_dp*) ; 
 int /*<<< orphan*/  msecs_to_jiffies_timeout (int) ; 
 int /*<<< orphan*/  stub1 (struct intel_dp*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
intel_dp_aux_wait_done(struct intel_dp *intel_dp)
{
	struct drm_i915_private *dev_priv = to_i915(intel_dp_to_dev(intel_dp));
	i915_reg_t ch_ctl = intel_dp->aux_ch_ctl_reg(intel_dp);
	uint32_t status;
	bool done;

#define C (((status = I915_READ_NOTRACE(ch_ctl)) & DP_AUX_CH_CTL_SEND_BUSY) == 0)
	done = wait_event_timeout(dev_priv->gmbus_wait_queue, C,
				  msecs_to_jiffies_timeout(10));
	if (!done)
		DRM_ERROR("dp aux hw did not signal timeout!\n");
#undef C

	return status;
}