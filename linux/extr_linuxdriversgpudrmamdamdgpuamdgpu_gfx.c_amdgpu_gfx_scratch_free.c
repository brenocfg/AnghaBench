#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint32_t ;
struct TYPE_3__ {unsigned int free_mask; unsigned int reg_base; } ;
struct TYPE_4__ {TYPE_1__ scratch; } ;
struct amdgpu_device {TYPE_2__ gfx; } ;

/* Variables and functions */

void amdgpu_gfx_scratch_free(struct amdgpu_device *adev, uint32_t reg)
{
	adev->gfx.scratch.free_mask |= 1u << (reg - adev->gfx.scratch.reg_base);
}