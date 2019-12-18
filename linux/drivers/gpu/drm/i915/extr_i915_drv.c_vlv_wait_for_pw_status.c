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
struct drm_i915_private {int /*<<< orphan*/  uncore; } ;
typedef  int /*<<< orphan*/  reg_value ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLV_GTLC_PW_STATUS ; 
 int intel_uncore_read_notrace (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_i915_reg_rw (int,int /*<<< orphan*/ ,int,int,int) ; 
 int wait_for (int,int) ; 

__attribute__((used)) static int vlv_wait_for_pw_status(struct drm_i915_private *i915,
				  u32 mask, u32 val)
{
	i915_reg_t reg = VLV_GTLC_PW_STATUS;
	u32 reg_value;
	int ret;

	/* The HW does not like us polling for PW_STATUS frequently, so
	 * use the sleeping loop rather than risk the busy spin within
	 * intel_wait_for_register().
	 *
	 * Transitioning between RC6 states should be at most 2ms (see
	 * valleyview_enable_rps) so use a 3ms timeout.
	 */
	ret = wait_for(((reg_value =
			 intel_uncore_read_notrace(&i915->uncore, reg)) & mask)
		       == val, 3);

	/* just trace the final value */
	trace_i915_reg_rw(false, reg, reg_value, sizeof(reg_value), true);

	return ret;
}