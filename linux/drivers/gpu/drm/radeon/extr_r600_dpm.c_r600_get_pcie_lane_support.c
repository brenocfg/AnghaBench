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
struct radeon_device {int dummy; } ;

/* Variables and functions */

u16 r600_get_pcie_lane_support(struct radeon_device *rdev,
			       u16 asic_lanes,
			       u16 default_lanes)
{
	switch (asic_lanes) {
	case 0:
	default:
		return default_lanes;
	case 1:
		return 1;
	case 2:
		return 2;
	case 4:
		return 4;
	case 8:
		return 8;
	case 12:
		return 12;
	case 16:
		return 16;
	}
}