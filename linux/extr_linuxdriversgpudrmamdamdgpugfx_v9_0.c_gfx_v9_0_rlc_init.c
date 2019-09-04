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
typedef  int u32 ;
struct cs_section_def {int dummy; } ;
struct TYPE_3__ {int clear_state_size; int* cs_ptr; int cp_table_size; int /*<<< orphan*/  cp_table_obj; int /*<<< orphan*/  cp_table_ptr; int /*<<< orphan*/  cp_table_gpu_addr; int /*<<< orphan*/  clear_state_obj; int /*<<< orphan*/  clear_state_gpu_addr; struct cs_section_def* cs_data; } ;
struct TYPE_4__ {TYPE_1__ rlc; } ;
struct amdgpu_device {scalar_t__ asic_type; TYPE_2__ gfx; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_VRAM ; 
 scalar_t__ CHIP_RAVEN ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int amdgpu_bo_create_reserved (struct amdgpu_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  amdgpu_bo_kunmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_bo_unpin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct cs_section_def* gfx9_cs_data ; 
 int /*<<< orphan*/  gfx_v9_0_get_csb_buffer (struct amdgpu_device*,int volatile*) ; 
 int gfx_v9_0_get_csb_size (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v9_0_init_lbpw (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v9_0_rlc_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  rv_init_cp_jump_table (struct amdgpu_device*) ; 

__attribute__((used)) static int gfx_v9_0_rlc_init(struct amdgpu_device *adev)
{
	volatile u32 *dst_ptr;
	u32 dws;
	const struct cs_section_def *cs_data;
	int r;

	adev->gfx.rlc.cs_data = gfx9_cs_data;

	cs_data = adev->gfx.rlc.cs_data;

	if (cs_data) {
		/* clear state block */
		adev->gfx.rlc.clear_state_size = dws = gfx_v9_0_get_csb_size(adev);
		r = amdgpu_bo_create_reserved(adev, dws * 4, PAGE_SIZE,
					      AMDGPU_GEM_DOMAIN_VRAM,
					      &adev->gfx.rlc.clear_state_obj,
					      &adev->gfx.rlc.clear_state_gpu_addr,
					      (void **)&adev->gfx.rlc.cs_ptr);
		if (r) {
			dev_err(adev->dev, "(%d) failed to create rlc csb bo\n",
				r);
			gfx_v9_0_rlc_fini(adev);
			return r;
		}
		/* set up the cs buffer */
		dst_ptr = adev->gfx.rlc.cs_ptr;
		gfx_v9_0_get_csb_buffer(adev, dst_ptr);
		amdgpu_bo_kunmap(adev->gfx.rlc.clear_state_obj);
		amdgpu_bo_unpin(adev->gfx.rlc.clear_state_obj);
		amdgpu_bo_unreserve(adev->gfx.rlc.clear_state_obj);
	}

	if (adev->asic_type == CHIP_RAVEN) {
		/* TODO: double check the cp_table_size for RV */
		adev->gfx.rlc.cp_table_size = ALIGN(96 * 5 * 4, 2048) + (64 * 1024); /* JT + GDS */
		r = amdgpu_bo_create_reserved(adev, adev->gfx.rlc.cp_table_size,
					      PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM,
					      &adev->gfx.rlc.cp_table_obj,
					      &adev->gfx.rlc.cp_table_gpu_addr,
					      (void **)&adev->gfx.rlc.cp_table_ptr);
		if (r) {
			dev_err(adev->dev,
				"(%d) failed to create cp table bo\n", r);
			gfx_v9_0_rlc_fini(adev);
			return r;
		}

		rv_init_cp_jump_table(adev);
		amdgpu_bo_kunmap(adev->gfx.rlc.cp_table_obj);
		amdgpu_bo_unreserve(adev->gfx.rlc.cp_table_obj);

		gfx_v9_0_init_lbpw(adev);
	}

	return 0;
}