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
 int I915_READ_NOTRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLV_GTLC_PW_STATUS ; 
 int wait_for (int,int) ; 

__attribute__((used)) static int vlv_wait_for_pw_status(struct drm_i915_private *dev_priv,
				  u32 mask, u32 val)
{
	/* The HW does not like us polling for PW_STATUS frequently, so
	 * use the sleeping loop rather than risk the busy spin within
	 * intel_wait_for_register().
	 *
	 * Transitioning between RC6 states should be at most 2ms (see
	 * valleyview_enable_rps) so use a 3ms timeout.
	 */
	return wait_for((I915_READ_NOTRACE(VLV_GTLC_PW_STATUS) & mask) == val,
			3);
}