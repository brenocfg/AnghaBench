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
typedef  int /*<<< orphan*/  uint32_t ;
struct amdgpu_ring {struct amdgpu_device* adev; TYPE_1__* funcs; } ;
struct TYPE_4__ {int cp_fw_write_wait; } ;
struct amdgpu_device {TYPE_2__ gfx; } ;
struct TYPE_3__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_RING_TYPE_GFX ; 
 int /*<<< orphan*/  amdgpu_ring_emit_reg_write_reg_wait_helper (struct amdgpu_ring*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfx_v10_0_wait_reg_mem (struct amdgpu_ring*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void gfx_v10_0_ring_emit_reg_write_reg_wait(struct amdgpu_ring *ring,
						   uint32_t reg0, uint32_t reg1,
						   uint32_t ref, uint32_t mask)
{
	int usepfp = (ring->funcs->type == AMDGPU_RING_TYPE_GFX);
	struct amdgpu_device *adev = ring->adev;
	bool fw_version_ok = false;

	fw_version_ok = adev->gfx.cp_fw_write_wait;

	if (fw_version_ok)
		gfx_v10_0_wait_reg_mem(ring, usepfp, 0, 1, reg0, reg1,
				       ref, mask, 0x20);
	else
		amdgpu_ring_emit_reg_write_reg_wait_helper(ring, reg0, reg1,
							   ref, mask);
}