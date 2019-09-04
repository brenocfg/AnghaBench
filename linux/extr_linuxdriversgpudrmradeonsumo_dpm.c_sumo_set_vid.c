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

/* Variables and functions */
 int /*<<< orphan*/  CG_DPM_VOLTAGE_CNTL ; 
 int DPM_STATE0_LEVEL_MASK ; 
 int DPM_STATE0_LEVEL_SHIFT ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sumo_set_vid(struct radeon_device *rdev, u32 index, u32 vid)
{
	u32 voltage_cntl = RREG32(CG_DPM_VOLTAGE_CNTL);

	voltage_cntl &= ~(DPM_STATE0_LEVEL_MASK << (index * 2));
	voltage_cntl |= (vid << (DPM_STATE0_LEVEL_SHIFT + index * 2));
	WREG32(CG_DPM_VOLTAGE_CNTL, voltage_cntl);
}