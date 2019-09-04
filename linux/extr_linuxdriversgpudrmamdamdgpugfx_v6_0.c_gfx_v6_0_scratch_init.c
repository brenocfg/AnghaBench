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
struct TYPE_3__ {int num_reg; unsigned int free_mask; int /*<<< orphan*/  reg_base; } ;
struct TYPE_4__ {TYPE_1__ scratch; } ;
struct amdgpu_device {TYPE_2__ gfx; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmSCRATCH_REG0 ; 

__attribute__((used)) static void gfx_v6_0_scratch_init(struct amdgpu_device *adev)
{
	adev->gfx.scratch.num_reg = 8;
	adev->gfx.scratch.reg_base = mmSCRATCH_REG0;
	adev->gfx.scratch.free_mask = (1u << adev->gfx.scratch.num_reg) - 1;
}