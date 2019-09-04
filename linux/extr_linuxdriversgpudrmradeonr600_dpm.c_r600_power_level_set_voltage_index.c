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
 int /*<<< orphan*/  CTXSW_FREQ_VIDS_CFG_INDEX (int) ; 
 int /*<<< orphan*/  CTXSW_FREQ_VIDS_CFG_INDEX_MASK ; 
 scalar_t__ CTXSW_PROFILE_INDEX ; 
 int /*<<< orphan*/  WREG32_P (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void r600_power_level_set_voltage_index(struct radeon_device *rdev,
					enum r600_power_level index, u32 voltage_index)
{
	u32 ix = 3 - (3 & index);

	WREG32_P(CTXSW_PROFILE_INDEX + (ix * 4),
		 CTXSW_FREQ_VIDS_CFG_INDEX(voltage_index), ~CTXSW_FREQ_VIDS_CFG_INDEX_MASK);
}