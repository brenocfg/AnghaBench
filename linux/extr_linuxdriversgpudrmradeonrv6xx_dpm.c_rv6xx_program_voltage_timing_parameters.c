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
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  backbias_response_time; int /*<<< orphan*/  voltage_response_time; } ;
struct TYPE_4__ {TYPE_1__ dpm; } ;
struct radeon_device {TYPE_2__ pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  R600_VRU_DFLT ; 
 int /*<<< orphan*/  r600_vid_rt_set_vrt (struct radeon_device*,int) ; 
 int /*<<< orphan*/  r600_vid_rt_set_vru (struct radeon_device*,int /*<<< orphan*/ ) ; 
 int rv6xx_compute_count_for_delay (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rv6xx_vid_response_set_brt (struct radeon_device*,int) ; 

__attribute__((used)) static void rv6xx_program_voltage_timing_parameters(struct radeon_device *rdev)
{
	u32 rt;

	r600_vid_rt_set_vru(rdev, R600_VRU_DFLT);

	r600_vid_rt_set_vrt(rdev,
			    rv6xx_compute_count_for_delay(rdev,
							  rdev->pm.dpm.voltage_response_time,
							  R600_VRU_DFLT));

	rt = rv6xx_compute_count_for_delay(rdev,
					   rdev->pm.dpm.backbias_response_time,
					   R600_VRU_DFLT);

	rv6xx_vid_response_set_brt(rdev, (rt + 0x1F) >> 5);
}