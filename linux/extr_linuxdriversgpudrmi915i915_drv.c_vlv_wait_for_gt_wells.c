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
typedef  int u32 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ) ; 
 int VLV_GTLC_PW_MEDIA_STATUS_MASK ; 
 int VLV_GTLC_PW_RENDER_STATUS_MASK ; 
 int /*<<< orphan*/  onoff (int) ; 
 scalar_t__ vlv_wait_for_pw_status (struct drm_i915_private*,int,int) ; 

__attribute__((used)) static void vlv_wait_for_gt_wells(struct drm_i915_private *dev_priv,
				  bool wait_for_on)
{
	u32 mask;
	u32 val;

	mask = VLV_GTLC_PW_MEDIA_STATUS_MASK | VLV_GTLC_PW_RENDER_STATUS_MASK;
	val = wait_for_on ? mask : 0;

	/*
	 * RC6 transitioning can be delayed up to 2 msec (see
	 * valleyview_enable_rps), use 3 msec for safety.
	 *
	 * This can fail to turn off the rc6 if the GPU is stuck after a failed
	 * reset and we are trying to force the machine to sleep.
	 */
	if (vlv_wait_for_pw_status(dev_priv, mask, val))
		DRM_DEBUG_DRIVER("timeout waiting for GT wells to go %s\n",
				 onoff(wait_for_on));
}