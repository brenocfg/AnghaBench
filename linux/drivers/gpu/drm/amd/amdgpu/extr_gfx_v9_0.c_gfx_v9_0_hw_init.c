#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* funcs; } ;
struct TYPE_6__ {TYPE_2__ rlc; } ;
struct amdgpu_device {scalar_t__ asic_type; TYPE_3__ gfx; } ;
struct TYPE_4__ {int (* resume ) (struct amdgpu_device*) ;} ;

/* Variables and functions */
 scalar_t__ CHIP_ARCTURUS ; 
 int /*<<< orphan*/  amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v9_0_constants_init (struct amdgpu_device*) ; 
 int gfx_v9_0_cp_resume (struct amdgpu_device*) ; 
 int gfx_v9_0_csb_vram_pin (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v9_0_init_golden_registers (struct amdgpu_device*) ; 
 int gfx_v9_0_ngg_en (struct amdgpu_device*) ; 
 int stub1 (struct amdgpu_device*) ; 

__attribute__((used)) static int gfx_v9_0_hw_init(void *handle)
{
	int r;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	if (!amdgpu_sriov_vf(adev))
		gfx_v9_0_init_golden_registers(adev);

	gfx_v9_0_constants_init(adev);

	r = gfx_v9_0_csb_vram_pin(adev);
	if (r)
		return r;

	r = adev->gfx.rlc.funcs->resume(adev);
	if (r)
		return r;

	r = gfx_v9_0_cp_resume(adev);
	if (r)
		return r;

	if (adev->asic_type != CHIP_ARCTURUS) {
		r = gfx_v9_0_ngg_en(adev);
		if (r)
			return r;
	}

	return r;
}