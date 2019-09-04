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
struct radeon_device {int dummy; } ;
typedef  enum r600_power_level { ____Placeholder_r600_power_level } r600_power_level ;

/* Variables and functions */
 int CTXSW_FREQ_GEN2PCIE_VOLT ; 
 scalar_t__ CTXSW_PROFILE_INDEX ; 
 int /*<<< orphan*/  WREG32_P (scalar_t__,int,int) ; 

void r600_power_level_set_pcie_gen2(struct radeon_device *rdev,
				    enum r600_power_level index, bool compatible)
{
	u32 ix = 3 - (3 & index);
	u32 tmp = 0;

	if (compatible)
		tmp = CTXSW_FREQ_GEN2PCIE_VOLT;
	WREG32_P(CTXSW_PROFILE_INDEX + (ix * 4), tmp, ~CTXSW_FREQ_GEN2PCIE_VOLT);
}