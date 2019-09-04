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
struct TYPE_3__ {int* reg_list; int reg_list_size; int cp_table_size; int* sr_ptr; int clear_state_size; int* cs_ptr; int /*<<< orphan*/  cp_table_obj; int /*<<< orphan*/  cp_table_ptr; int /*<<< orphan*/  cp_table_gpu_addr; int /*<<< orphan*/  clear_state_obj; int /*<<< orphan*/  clear_state_gpu_addr; int /*<<< orphan*/  save_restore_obj; int /*<<< orphan*/  save_restore_gpu_addr; struct cs_section_def* cs_data; } ;
struct TYPE_4__ {TYPE_1__ rlc; } ;
struct amdgpu_device {int flags; scalar_t__ asic_type; TYPE_2__ gfx; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_VRAM ; 
 int AMD_IS_APU ; 
 scalar_t__ ARRAY_SIZE (void*) ; 
 scalar_t__ CHIP_KAVERI ; 
 int CP_ME_TABLE_SIZE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int amdgpu_bo_create_reserved (struct amdgpu_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  amdgpu_bo_kunmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (int /*<<< orphan*/ ) ; 
 struct cs_section_def* ci_cs_data ; 
 int cpu_to_le32 (int const) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gfx_v7_0_get_csb_buffer (struct amdgpu_device*,int volatile*) ; 
 int gfx_v7_0_get_csb_size (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v7_0_init_cp_pg_table (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v7_0_rlc_fini (struct amdgpu_device*) ; 
 void* kalindi_rlc_save_restore_register_list ; 
 void* spectre_rlc_save_restore_register_list ; 

__attribute__((used)) static int gfx_v7_0_rlc_init(struct amdgpu_device *adev)
{
	const u32 *src_ptr;
	volatile u32 *dst_ptr;
	u32 dws, i;
	const struct cs_section_def *cs_data;
	int r;

	/* allocate rlc buffers */
	if (adev->flags & AMD_IS_APU) {
		if (adev->asic_type == CHIP_KAVERI) {
			adev->gfx.rlc.reg_list = spectre_rlc_save_restore_register_list;
			adev->gfx.rlc.reg_list_size =
				(u32)ARRAY_SIZE(spectre_rlc_save_restore_register_list);
		} else {
			adev->gfx.rlc.reg_list = kalindi_rlc_save_restore_register_list;
			adev->gfx.rlc.reg_list_size =
				(u32)ARRAY_SIZE(kalindi_rlc_save_restore_register_list);
		}
	}
	adev->gfx.rlc.cs_data = ci_cs_data;
	adev->gfx.rlc.cp_table_size = ALIGN(CP_ME_TABLE_SIZE * 5 * 4, 2048); /* CP JT */
	adev->gfx.rlc.cp_table_size += 64 * 1024; /* GDS */

	src_ptr = adev->gfx.rlc.reg_list;
	dws = adev->gfx.rlc.reg_list_size;
	dws += (5 * 16) + 48 + 48 + 64;

	cs_data = adev->gfx.rlc.cs_data;

	if (src_ptr) {
		/* save restore block */
		r = amdgpu_bo_create_reserved(adev, dws * 4, PAGE_SIZE,
					      AMDGPU_GEM_DOMAIN_VRAM,
					      &adev->gfx.rlc.save_restore_obj,
					      &adev->gfx.rlc.save_restore_gpu_addr,
					      (void **)&adev->gfx.rlc.sr_ptr);
		if (r) {
			dev_warn(adev->dev, "(%d) create, pin or map of RLC sr bo failed\n", r);
			gfx_v7_0_rlc_fini(adev);
			return r;
		}

		/* write the sr buffer */
		dst_ptr = adev->gfx.rlc.sr_ptr;
		for (i = 0; i < adev->gfx.rlc.reg_list_size; i++)
			dst_ptr[i] = cpu_to_le32(src_ptr[i]);
		amdgpu_bo_kunmap(adev->gfx.rlc.save_restore_obj);
		amdgpu_bo_unreserve(adev->gfx.rlc.save_restore_obj);
	}

	if (cs_data) {
		/* clear state block */
		adev->gfx.rlc.clear_state_size = dws = gfx_v7_0_get_csb_size(adev);

		r = amdgpu_bo_create_reserved(adev, dws * 4, PAGE_SIZE,
					      AMDGPU_GEM_DOMAIN_VRAM,
					      &adev->gfx.rlc.clear_state_obj,
					      &adev->gfx.rlc.clear_state_gpu_addr,
					      (void **)&adev->gfx.rlc.cs_ptr);
		if (r) {
			dev_warn(adev->dev, "(%d) create RLC c bo failed\n", r);
			gfx_v7_0_rlc_fini(adev);
			return r;
		}

		/* set up the cs buffer */
		dst_ptr = adev->gfx.rlc.cs_ptr;
		gfx_v7_0_get_csb_buffer(adev, dst_ptr);
		amdgpu_bo_kunmap(adev->gfx.rlc.clear_state_obj);
		amdgpu_bo_unreserve(adev->gfx.rlc.clear_state_obj);
	}

	if (adev->gfx.rlc.cp_table_size) {

		r = amdgpu_bo_create_reserved(adev, adev->gfx.rlc.cp_table_size,
					      PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM,
					      &adev->gfx.rlc.cp_table_obj,
					      &adev->gfx.rlc.cp_table_gpu_addr,
					      (void **)&adev->gfx.rlc.cp_table_ptr);
		if (r) {
			dev_warn(adev->dev, "(%d) create RLC cp table bo failed\n", r);
			gfx_v7_0_rlc_fini(adev);
			return r;
		}

		gfx_v7_0_init_cp_pg_table(adev);

		amdgpu_bo_kunmap(adev->gfx.rlc.cp_table_obj);
		amdgpu_bo_unreserve(adev->gfx.rlc.cp_table_obj);

	}

	return 0;
}