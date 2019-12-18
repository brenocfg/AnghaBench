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
typedef  int u64 ;
typedef  int u32 ;
struct radeon_device {int dummy; } ;
typedef  enum r600_power_level { ____Placeholder_r600_power_level } r600_power_level ;

/* Variables and functions */
 scalar_t__ CTXSW_VID_LOWER_GPIO_CNTL ; 
 int RREG32 (scalar_t__) ; 
 scalar_t__ VID_UPPER_GPIO_CNTL ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 

void r600_voltage_control_program_voltages(struct radeon_device *rdev,
					   enum r600_power_level index, u64 pins)
{
	u32 tmp, mask;
	u32 ix = 3 - (3 & index);

	WREG32(CTXSW_VID_LOWER_GPIO_CNTL + (ix * 4), pins & 0xffffffff);

	mask = 7 << (3 * ix);
	tmp = RREG32(VID_UPPER_GPIO_CNTL);
	tmp = (tmp & ~mask) | ((pins >> (32 - (3 * ix))) & mask);
	WREG32(VID_UPPER_GPIO_CNTL, tmp);
}