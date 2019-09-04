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
struct rv7xx_power_info {int /*<<< orphan*/  s0_vid_lower_smio_cntl; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S0_VID_LOWER_SMIO_CNTL ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 

void rv770_read_voltage_smio_registers(struct radeon_device *rdev)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);

	pi->s0_vid_lower_smio_cntl =
		RREG32(S0_VID_LOWER_SMIO_CNTL);
}