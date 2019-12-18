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
typedef  int /*<<< orphan*/  u16 ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int LC_CURRENT_DATA_RATE_MASK ; 
 int LC_CURRENT_DATA_RATE_SHIFT ; 
 int /*<<< orphan*/  PCIE_LC_SPEED_CNTL ; 
 int RREG32_PCIE_PORT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 si_get_current_pcie_speed(struct amdgpu_device *adev)
{
	u32 speed_cntl;

	speed_cntl = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL) & LC_CURRENT_DATA_RATE_MASK;
	speed_cntl >>= LC_CURRENT_DATA_RATE_SHIFT;

	return (u16)speed_cntl;
}