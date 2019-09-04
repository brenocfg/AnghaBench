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
struct rv6xx_power_info {int mpll_ref_div; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int R600_MPLLLOCKTIME_DFLT ; 
 int /*<<< orphan*/  R600_MPLLRESETTIME_DFLT ; 
 int /*<<< orphan*/  r600_set_mpll_lock_time (struct radeon_device*,int) ; 
 int /*<<< orphan*/  r600_set_mpll_reset_time (struct radeon_device*,int /*<<< orphan*/ ) ; 
 struct rv6xx_power_info* rv6xx_get_pi (struct radeon_device*) ; 

__attribute__((used)) static void rv6xx_program_mpll_timing_parameters(struct radeon_device *rdev)
{
	struct rv6xx_power_info *pi = rv6xx_get_pi(rdev);

	r600_set_mpll_lock_time(rdev, R600_MPLLLOCKTIME_DFLT *
				pi->mpll_ref_div);
	r600_set_mpll_reset_time(rdev, R600_MPLLRESETTIME_DFLT);
}