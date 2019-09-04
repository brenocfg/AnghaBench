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

/* Variables and functions */
 int /*<<< orphan*/  DCM ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UVD_CGC_CTRL ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  si_set_uvd_dcm (struct radeon_device*,int) ; 

void si_init_uvd_internal_cg(struct radeon_device *rdev)
{
	bool hw_mode = true;

	if (hw_mode) {
		si_set_uvd_dcm(rdev, false);
	} else {
		u32 tmp = RREG32(UVD_CGC_CTRL);
		tmp &= ~DCM;
		WREG32(UVD_CGC_CTRL, tmp);
	}
}