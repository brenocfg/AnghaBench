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
typedef  size_t u32 ;
struct radeon_device {int dummy; } ;
struct TYPE_3__ {size_t last; TYPE_2__* mc_reg_address; } ;
struct evergreen_power_info {TYPE_1__ mc_reg_table; } ;
struct TYPE_4__ {int s1; int s0; } ;

/* Variables and functions */
 size_t RREG32 (int) ; 
 int /*<<< orphan*/  WREG32 (int,size_t) ; 
 struct evergreen_power_info* evergreen_get_pi (struct radeon_device*) ; 

__attribute__((used)) static void cypress_copy_ac_timing_from_s1_to_s0(struct radeon_device *rdev)
{
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);
	u32 value;
	u32 i;

	for (i = 0; i < eg_pi->mc_reg_table.last; i++) {
		value = RREG32(eg_pi->mc_reg_table.mc_reg_address[i].s1 << 2);
		WREG32(eg_pi->mc_reg_table.mc_reg_address[i].s0 << 2, value);
	}
}