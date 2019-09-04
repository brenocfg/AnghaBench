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
struct TYPE_4__ {int /*<<< orphan*/  clear_state_obj; int /*<<< orphan*/  clear_state_gpu_addr; } ;
struct TYPE_3__ {TYPE_2__ rlc; } ;
struct amdgpu_device {TYPE_1__ gfx; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_VRAM ; 
 int /*<<< orphan*/  amdgpu_bo_gpu_offset (int /*<<< orphan*/ ) ; 
 int amdgpu_bo_pin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int amdgpu_bo_reserve (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int gfx_v9_0_csb_vram_pin(struct amdgpu_device *adev)
{
	int r;

	r = amdgpu_bo_reserve(adev->gfx.rlc.clear_state_obj, false);
	if (unlikely(r != 0))
		return r;

	r = amdgpu_bo_pin(adev->gfx.rlc.clear_state_obj,
			AMDGPU_GEM_DOMAIN_VRAM);
	if (!r)
		adev->gfx.rlc.clear_state_gpu_addr =
			amdgpu_bo_gpu_offset(adev->gfx.rlc.clear_state_obj);

	amdgpu_bo_unreserve(adev->gfx.rlc.clear_state_obj);

	return r;
}