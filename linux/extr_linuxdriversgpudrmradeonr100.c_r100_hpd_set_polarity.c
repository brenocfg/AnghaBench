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
typedef  int /*<<< orphan*/  u32 ;
struct radeon_device {int dummy; } ;
typedef  enum radeon_hpd_id { ____Placeholder_radeon_hpd_id } radeon_hpd_id ;

/* Variables and functions */
 int /*<<< orphan*/  RADEON_FP2_DETECT_INT_POL ; 
 int /*<<< orphan*/  RADEON_FP2_GEN_CNTL ; 
 int /*<<< orphan*/  RADEON_FP_DETECT_INT_POL ; 
 int /*<<< orphan*/  RADEON_FP_GEN_CNTL ; 
#define  RADEON_HPD_1 129 
#define  RADEON_HPD_2 128 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int r100_hpd_sense (struct radeon_device*,int) ; 

void r100_hpd_set_polarity(struct radeon_device *rdev,
			   enum radeon_hpd_id hpd)
{
	u32 tmp;
	bool connected = r100_hpd_sense(rdev, hpd);

	switch (hpd) {
	case RADEON_HPD_1:
		tmp = RREG32(RADEON_FP_GEN_CNTL);
		if (connected)
			tmp &= ~RADEON_FP_DETECT_INT_POL;
		else
			tmp |= RADEON_FP_DETECT_INT_POL;
		WREG32(RADEON_FP_GEN_CNTL, tmp);
		break;
	case RADEON_HPD_2:
		tmp = RREG32(RADEON_FP2_GEN_CNTL);
		if (connected)
			tmp &= ~RADEON_FP2_DETECT_INT_POL;
		else
			tmp |= RADEON_FP2_DETECT_INT_POL;
		WREG32(RADEON_FP2_GEN_CNTL, tmp);
		break;
	default:
		break;
	}
}