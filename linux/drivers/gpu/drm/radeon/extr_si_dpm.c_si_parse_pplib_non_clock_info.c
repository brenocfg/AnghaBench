#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct radeon_ps {int class; void* dclk; void* vclk; void* class2; void* caps; } ;
struct TYPE_3__ {struct radeon_ps* uvd_ps; struct radeon_ps* boot_ps; } ;
struct TYPE_4__ {TYPE_1__ dpm; } ;
struct radeon_device {TYPE_2__ pm; } ;
struct _ATOM_PPLIB_NONCLOCK_INFO {int /*<<< orphan*/  ulDCLK; int /*<<< orphan*/  ulVCLK; int /*<<< orphan*/  usClassification2; int /*<<< orphan*/  usClassification; int /*<<< orphan*/  ulCapsAndSettings; } ;

/* Variables and functions */
 int ATOM_PPLIB_CLASSIFICATION_BOOT ; 
 int ATOM_PPLIB_CLASSIFICATION_UVDSTATE ; 
 scalar_t__ ATOM_PPLIB_NONCLOCKINFO_VER1 ; 
 void* RV770_DEFAULT_DCLK_FREQ ; 
 void* RV770_DEFAULT_VCLK_FREQ ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ r600_is_uvd_state (int,void*) ; 

__attribute__((used)) static void si_parse_pplib_non_clock_info(struct radeon_device *rdev,
					  struct radeon_ps *rps,
					  struct _ATOM_PPLIB_NONCLOCK_INFO *non_clock_info,
					  u8 table_rev)
{
	rps->caps = le32_to_cpu(non_clock_info->ulCapsAndSettings);
	rps->class = le16_to_cpu(non_clock_info->usClassification);
	rps->class2 = le16_to_cpu(non_clock_info->usClassification2);

	if (ATOM_PPLIB_NONCLOCKINFO_VER1 < table_rev) {
		rps->vclk = le32_to_cpu(non_clock_info->ulVCLK);
		rps->dclk = le32_to_cpu(non_clock_info->ulDCLK);
	} else if (r600_is_uvd_state(rps->class, rps->class2)) {
		rps->vclk = RV770_DEFAULT_VCLK_FREQ;
		rps->dclk = RV770_DEFAULT_DCLK_FREQ;
	} else {
		rps->vclk = 0;
		rps->dclk = 0;
	}

	if (rps->class & ATOM_PPLIB_CLASSIFICATION_BOOT)
		rdev->pm.dpm.boot_ps = rps;
	if (rps->class & ATOM_PPLIB_CLASSIFICATION_UVDSTATE)
		rdev->pm.dpm.uvd_ps = rps;
}