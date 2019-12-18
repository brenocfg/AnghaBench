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
#define  DMA_STATUS_REG 134 
 int EINVAL ; 
#define  GRBM_STATUS 133 
#define  GRBM_STATUS_SE0 132 
#define  GRBM_STATUS_SE1 131 
 int RREG32 (int) ; 
#define  SRBM_STATUS 130 
#define  SRBM_STATUS2 129 
#define  UVD_STATUS 128 

int evergreen_get_allowed_info_register(struct radeon_device *rdev,
					u32 reg, u32 *val)
{
	switch (reg) {
	case GRBM_STATUS:
	case GRBM_STATUS_SE0:
	case GRBM_STATUS_SE1:
	case SRBM_STATUS:
	case SRBM_STATUS2:
	case DMA_STATUS_REG:
	case UVD_STATUS:
		*val = RREG32(reg);
		return 0;
	default:
		return -EINVAL;
	}
}