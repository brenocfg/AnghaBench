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
typedef  int u16 ;
struct intel_dp {int* psr_dpcd; int /*<<< orphan*/  aux; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int DP_PSR2_SU_GRANULARITY_REQUIRED ; 
 int /*<<< orphan*/  DP_PSR2_SU_X_GRANULARITY ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int drm_dp_dpcd_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static u16 intel_dp_get_su_x_granulartiy(struct intel_dp *intel_dp)
{
	u16 val;
	ssize_t r;

	/*
	 * Returning the default X granularity if granularity not required or
	 * if DPCD read fails
	 */
	if (!(intel_dp->psr_dpcd[1] & DP_PSR2_SU_GRANULARITY_REQUIRED))
		return 4;

	r = drm_dp_dpcd_read(&intel_dp->aux, DP_PSR2_SU_X_GRANULARITY, &val, 2);
	if (r != 2)
		DRM_DEBUG_KMS("Unable to read DP_PSR2_SU_X_GRANULARITY\n");

	/*
	 * Spec says that if the value read is 0 the default granularity should
	 * be used instead.
	 */
	if (r != 2 || val == 0)
		val = 4;

	return val;
}