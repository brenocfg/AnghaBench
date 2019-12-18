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
struct drm_dp_aux {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_LANE0_1_STATUS ; 
 int /*<<< orphan*/  DP_LINK_STATUS_SIZE ; 
 int drm_dp_dpcd_read (struct drm_dp_aux*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int drm_dp_dpcd_read_link_status(struct drm_dp_aux *aux,
				 u8 status[DP_LINK_STATUS_SIZE])
{
	return drm_dp_dpcd_read(aux, DP_LANE0_1_STATUS, status,
				DP_LINK_STATUS_SIZE);
}