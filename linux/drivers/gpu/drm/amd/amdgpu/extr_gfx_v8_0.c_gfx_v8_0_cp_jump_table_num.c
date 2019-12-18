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
 scalar_t__ CHIP_CARRIZO ; 

__attribute__((used)) static int gfx_v8_0_cp_jump_table_num(struct amdgpu_device *adev)
{
	if (adev->asic_type == CHIP_CARRIZO)
		return 5;
	else
		return 4;
}