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
 int PCIE_LC_SPEED_CNTL__LC_CURRENT_DATA_RATE_MASK ; 
 int PCIE_LC_SPEED_CNTL__LC_CURRENT_DATA_RATE__SHIFT ; 
 int RREG32_PCIE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixPCIE_LC_SPEED_CNTL ; 

__attribute__((used)) static u16 ci_get_current_pcie_speed(struct amdgpu_device *adev)
{
	u32 speed_cntl = 0;

	speed_cntl = RREG32_PCIE(ixPCIE_LC_SPEED_CNTL) &
		PCIE_LC_SPEED_CNTL__LC_CURRENT_DATA_RATE_MASK;
	speed_cntl >>= PCIE_LC_SPEED_CNTL__LC_CURRENT_DATA_RATE__SHIFT;

	return (u16)speed_cntl;
}