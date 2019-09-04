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
struct drm_dp_aux {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_BRANCH_ID ; 
 int drm_dp_dpcd_read (struct drm_dp_aux*,int /*<<< orphan*/ ,char*,int) ; 

int drm_dp_downstream_id(struct drm_dp_aux *aux, char id[6])
{
	return drm_dp_dpcd_read(aux, DP_BRANCH_ID, id, 6);
}