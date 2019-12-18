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
struct rv7xx_power_info {int dynamic_ss; void* mclk_ss; void* sclk_ss; } ;
struct radeon_device {int dummy; } ;
struct radeon_atom_ss {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_INTERNAL_ENGINE_SS ; 
 int /*<<< orphan*/  ASIC_INTERNAL_MEMORY_SS ; 
 void* radeon_atombios_get_asic_ss_info (struct radeon_device*,struct radeon_atom_ss*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 

void rv770_get_engine_memory_ss(struct radeon_device *rdev)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	struct radeon_atom_ss ss;

	pi->sclk_ss = radeon_atombios_get_asic_ss_info(rdev, &ss,
						       ASIC_INTERNAL_ENGINE_SS, 0);
	pi->mclk_ss = radeon_atombios_get_asic_ss_info(rdev, &ss,
						       ASIC_INTERNAL_MEMORY_SS, 0);

	if (pi->sclk_ss || pi->mclk_ss)
		pi->dynamic_ss = true;
	else
		pi->dynamic_ss = false;
}