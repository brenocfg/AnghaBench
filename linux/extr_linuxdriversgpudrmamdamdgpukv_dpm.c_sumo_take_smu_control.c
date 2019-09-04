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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void sumo_take_smu_control(struct amdgpu_device *adev, bool enable)
{
/* This bit selects who handles display phy powergating.
 * Clear the bit to let atom handle it.
 * Set it to let the driver handle it.
 * For now we just let atom handle it.
 */
#if 0
	u32 v = RREG32(mmDOUT_SCRATCH3);

	if (enable)
		v |= 0x4;
	else
		v &= 0xFFFFFFFB;

	WREG32(mmDOUT_SCRATCH3, v);
#endif
}