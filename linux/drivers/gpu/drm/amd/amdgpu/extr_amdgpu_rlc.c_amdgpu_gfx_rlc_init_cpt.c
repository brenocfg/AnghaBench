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
struct TYPE_3__ {int /*<<< orphan*/  cp_table_obj; int /*<<< orphan*/  cp_table_ptr; int /*<<< orphan*/  cp_table_gpu_addr; int /*<<< orphan*/  cp_table_size; } ;
struct TYPE_4__ {TYPE_1__ rlc; } ;
struct amdgpu_device {TYPE_2__ gfx; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_VRAM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int amdgpu_bo_create_reserved (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  amdgpu_bo_kunmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_gfx_rlc_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_gfx_rlc_setup_cp_table (struct amdgpu_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

int amdgpu_gfx_rlc_init_cpt(struct amdgpu_device *adev)
{
	int r;

	r = amdgpu_bo_create_reserved(adev, adev->gfx.rlc.cp_table_size,
				      PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM,
				      &adev->gfx.rlc.cp_table_obj,
				      &adev->gfx.rlc.cp_table_gpu_addr,
				      (void **)&adev->gfx.rlc.cp_table_ptr);
	if (r) {
		dev_err(adev->dev, "(%d) failed to create cp table bo\n", r);
		amdgpu_gfx_rlc_fini(adev);
		return r;
	}

	/* set up the cp table */
	amdgpu_gfx_rlc_setup_cp_table(adev);
	amdgpu_bo_kunmap(adev->gfx.rlc.cp_table_obj);
	amdgpu_bo_unreserve(adev->gfx.rlc.cp_table_obj);

	return 0;
}