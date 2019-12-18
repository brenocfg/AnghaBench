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
struct radeon_device {int dummy; } ;

/* Variables and functions */
#define  DMA_STATUS_REG 132 
 int EINVAL ; 
#define  GRBM_STATUS 131 
#define  GRBM_STATUS2 130 
 int RREG32 (int) ; 
#define  R_000E50_SRBM_STATUS 129 
#define  UVD_STATUS 128 

int r600_get_allowed_info_register(struct radeon_device *rdev,
				   u32 reg, u32 *val)
{
	switch (reg) {
	case GRBM_STATUS:
	case GRBM_STATUS2:
	case R_000E50_SRBM_STATUS:
	case DMA_STATUS_REG:
	case UVD_STATUS:
		*val = RREG32(reg);
		return 0;
	default:
		return -EINVAL;
	}
}