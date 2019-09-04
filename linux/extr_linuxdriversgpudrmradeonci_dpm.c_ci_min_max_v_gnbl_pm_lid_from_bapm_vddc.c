#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct radeon_device {int dummy; } ;
struct TYPE_2__ {int* BapmVddCVidHiSidd; int* BapmVddCVidLoSidd; int GnbLPMLMaxVid; int GnbLPMLMinVid; } ;
struct ci_power_info {TYPE_1__ smc_powertune_table; } ;

/* Variables and functions */
 int EINVAL ; 
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 

__attribute__((used)) static int ci_min_max_v_gnbl_pm_lid_from_bapm_vddc(struct radeon_device *rdev)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	u8 *hi_vid = pi->smc_powertune_table.BapmVddCVidHiSidd;
	u8 *lo_vid = pi->smc_powertune_table.BapmVddCVidLoSidd;
	int i, min, max;

	min = max = hi_vid[0];
	for (i = 0; i < 8; i++) {
		if (0 != hi_vid[i]) {
			if (min > hi_vid[i])
				min = hi_vid[i];
			if (max < hi_vid[i])
				max = hi_vid[i];
		}

		if (0 != lo_vid[i]) {
			if (min > lo_vid[i])
				min = lo_vid[i];
			if (max < lo_vid[i])
				max = lo_vid[i];
		}
	}

	if ((min == 0) || (max == 0))
		return -EINVAL;
	pi->smc_powertune_table.GnbLPMLMaxVid = (u8)max;
	pi->smc_powertune_table.GnbLPMLMinVid = (u8)min;

	return 0;
}