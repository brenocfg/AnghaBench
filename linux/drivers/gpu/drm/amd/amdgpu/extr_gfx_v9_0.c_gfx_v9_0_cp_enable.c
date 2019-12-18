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
struct amdgpu_device {scalar_t__ asic_type; } ;

/* Variables and functions */
 scalar_t__ CHIP_ARCTURUS ; 
 int /*<<< orphan*/  gfx_v9_0_cp_compute_enable (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  gfx_v9_0_cp_gfx_enable (struct amdgpu_device*,int) ; 

__attribute__((used)) static void gfx_v9_0_cp_enable(struct amdgpu_device *adev, bool enable)
{
	if (adev->asic_type != CHIP_ARCTURUS)
		gfx_v9_0_cp_gfx_enable(adev, enable);
	gfx_v9_0_cp_compute_enable(adev, enable);
}