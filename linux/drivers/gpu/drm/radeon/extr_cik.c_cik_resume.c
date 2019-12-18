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
struct TYPE_4__ {scalar_t__ pm_method; } ;
struct TYPE_3__ {int /*<<< orphan*/  atom_context; } ;
struct radeon_device {int accel_working; TYPE_2__ pm; TYPE_1__ mode_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 scalar_t__ PM_METHOD_DPM ; 
 int /*<<< orphan*/  atom_asic_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cik_init_golden_registers (struct radeon_device*) ; 
 int cik_startup (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_pm_resume (struct radeon_device*) ; 

int cik_resume(struct radeon_device *rdev)
{
	int r;

	/* post card */
	atom_asic_init(rdev->mode_info.atom_context);

	/* init golden registers */
	cik_init_golden_registers(rdev);

	if (rdev->pm.pm_method == PM_METHOD_DPM)
		radeon_pm_resume(rdev);

	rdev->accel_working = true;
	r = cik_startup(rdev);
	if (r) {
		DRM_ERROR("cik startup failed on resume\n");
		rdev->accel_working = false;
		return r;
	}

	return r;

}