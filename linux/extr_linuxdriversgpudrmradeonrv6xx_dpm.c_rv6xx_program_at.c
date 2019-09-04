#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int* rp; int* lp; } ;
struct rv6xx_power_info {int bsp; TYPE_1__ hw; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  r600_set_at (struct radeon_device*,int,int,int,int) ; 
 struct rv6xx_power_info* rv6xx_get_pi (struct radeon_device*) ; 

__attribute__((used)) static void rv6xx_program_at(struct radeon_device *rdev)
{
	struct rv6xx_power_info *pi = rv6xx_get_pi(rdev);

	r600_set_at(rdev,
		    (pi->hw.rp[0] * pi->bsp) / 200,
		    (pi->hw.rp[1] * pi->bsp) / 200,
		    (pi->hw.lp[2] * pi->bsp) / 200,
		    (pi->hw.lp[1] * pi->bsp) / 200);
}