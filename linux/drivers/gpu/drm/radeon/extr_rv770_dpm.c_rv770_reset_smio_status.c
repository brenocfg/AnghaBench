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
struct rv7xx_power_info {int s0_vid_lower_smio_cntl; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GENERAL_PWRMGT ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S0_VID_LOWER_SMIO_CNTL ; 
 int /*<<< orphan*/  S1_VID_LOWER_SMIO_CNTL ; 
 int /*<<< orphan*/  S2_VID_LOWER_SMIO_CNTL ; 
 int /*<<< orphan*/  S3_VID_LOWER_SMIO_CNTL ; 
 int /*<<< orphan*/  SW_SMIO_INDEX (int /*<<< orphan*/ ) ; 
 int SW_SMIO_INDEX_MASK ; 
 int SW_SMIO_INDEX_SHIFT ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 

void rv770_reset_smio_status(struct radeon_device *rdev)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	u32 sw_smio_index, vid_smio_cntl;

	sw_smio_index =
		(RREG32(GENERAL_PWRMGT) & SW_SMIO_INDEX_MASK) >> SW_SMIO_INDEX_SHIFT;
	switch (sw_smio_index) {
	case 3:
		vid_smio_cntl = RREG32(S3_VID_LOWER_SMIO_CNTL);
		break;
	case 2:
		vid_smio_cntl = RREG32(S2_VID_LOWER_SMIO_CNTL);
		break;
	case 1:
		vid_smio_cntl = RREG32(S1_VID_LOWER_SMIO_CNTL);
		break;
	case 0:
		return;
	default:
		vid_smio_cntl = pi->s0_vid_lower_smio_cntl;
		break;
	}

	WREG32(S0_VID_LOWER_SMIO_CNTL, vid_smio_cntl);
	WREG32_P(GENERAL_PWRMGT, SW_SMIO_INDEX(0), ~SW_SMIO_INDEX_MASK);
}