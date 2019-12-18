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
typedef  int /*<<< orphan*/  u8 ;
struct intel_dp {int /*<<< orphan*/  aux; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_LANE0_1_STATUS ; 
 scalar_t__ DP_LINK_STATUS_SIZE ; 
 scalar_t__ drm_dp_dpcd_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

bool
intel_dp_get_link_status(struct intel_dp *intel_dp, u8 link_status[DP_LINK_STATUS_SIZE])
{
	return drm_dp_dpcd_read(&intel_dp->aux, DP_LANE0_1_STATUS, link_status,
				DP_LINK_STATUS_SIZE) == DP_LINK_STATUS_SIZE;
}