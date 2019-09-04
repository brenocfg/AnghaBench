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
typedef  int u32 ;
struct rv7xx_power_info {int mem_gddr5; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MC_SEQ_MISC0 ; 
 int MC_SEQ_MISC0_GDDR5_MASK ; 
 int MC_SEQ_MISC0_GDDR5_SHIFT ; 
 int MC_SEQ_MISC0_GDDR5_VALUE ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 

void rv770_get_memory_type(struct radeon_device *rdev)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	u32 tmp;

	tmp = RREG32(MC_SEQ_MISC0);

	if (((tmp & MC_SEQ_MISC0_GDDR5_MASK) >> MC_SEQ_MISC0_GDDR5_SHIFT) ==
	    MC_SEQ_MISC0_GDDR5_VALUE)
		pi->mem_gddr5 = true;
	else
		pi->mem_gddr5 = false;

}