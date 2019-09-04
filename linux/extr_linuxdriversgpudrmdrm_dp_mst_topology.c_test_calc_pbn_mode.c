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

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int,int,int,int) ; 
 int EINVAL ; 
 int drm_dp_calc_pbn_mode (int,int) ; 

__attribute__((used)) static int test_calc_pbn_mode(void)
{
	int ret;
	ret = drm_dp_calc_pbn_mode(154000, 30);
	if (ret != 689) {
		DRM_ERROR("PBN calculation test failed - clock %d, bpp %d, expected PBN %d, actual PBN %d.\n",
				154000, 30, 689, ret);
		return -EINVAL;
	}
	ret = drm_dp_calc_pbn_mode(234000, 30);
	if (ret != 1047) {
		DRM_ERROR("PBN calculation test failed - clock %d, bpp %d, expected PBN %d, actual PBN %d.\n",
				234000, 30, 1047, ret);
		return -EINVAL;
	}
	ret = drm_dp_calc_pbn_mode(297000, 24);
	if (ret != 1063) {
		DRM_ERROR("PBN calculation test failed - clock %d, bpp %d, expected PBN %d, actual PBN %d.\n",
				297000, 24, 1063, ret);
		return -EINVAL;
	}
	return 0;
}