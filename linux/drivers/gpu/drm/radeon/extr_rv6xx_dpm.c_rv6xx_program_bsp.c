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
typedef  int /*<<< orphan*/  u32 ;
struct rv6xx_power_info {int /*<<< orphan*/  bsp; int /*<<< orphan*/  bsu; } ;
struct TYPE_3__ {int /*<<< orphan*/  reference_freq; } ;
struct TYPE_4__ {TYPE_1__ spll; } ;
struct radeon_device {TYPE_2__ clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  R600_ASI_DFLT ; 
 int /*<<< orphan*/  r600_calculate_u_and_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r600_set_bsp (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rv6xx_power_info* rv6xx_get_pi (struct radeon_device*) ; 

__attribute__((used)) static void rv6xx_program_bsp(struct radeon_device *rdev)
{
	struct rv6xx_power_info *pi = rv6xx_get_pi(rdev);
	u32 ref_clk = rdev->clock.spll.reference_freq;

	r600_calculate_u_and_p(R600_ASI_DFLT,
			       ref_clk, 16,
			       &pi->bsp,
			       &pi->bsu);

	r600_set_bsp(rdev, pi->bsu, pi->bsp);
}