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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct cs_section_def {int dummy; } ;
struct TYPE_3__ {int* reg_list; int reg_list_size; int clear_state_size; int* cs_ptr; int /*<<< orphan*/  clear_state_obj; scalar_t__ clear_state_gpu_addr; struct cs_section_def* cs_data; } ;
struct TYPE_4__ {TYPE_1__ rlc; } ;
struct amdgpu_device {TYPE_2__ gfx; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_VRAM ; 
 scalar_t__ ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int amdgpu_bo_create_reserved (struct amdgpu_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,void**) ; 
 int /*<<< orphan*/  amdgpu_bo_kunmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_gfx_rlc_fini (struct amdgpu_device*) ; 
 int amdgpu_gfx_rlc_init_sr (struct amdgpu_device*,int) ; 
 int cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gfx_v6_0_get_csb_buffer (struct amdgpu_device*,int volatile*) ; 
 int gfx_v6_0_get_csb_size (struct amdgpu_device*) ; 
 int lower_32_bits (scalar_t__) ; 
 struct cs_section_def* si_cs_data ; 
 int upper_32_bits (scalar_t__) ; 
 int* verde_rlc_save_restore_register_list ; 

__attribute__((used)) static int gfx_v6_0_rlc_init(struct amdgpu_device *adev)
{
	const u32 *src_ptr;
	volatile u32 *dst_ptr;
	u32 dws;
	u64 reg_list_mc_addr;
	const struct cs_section_def *cs_data;
	int r;

	adev->gfx.rlc.reg_list = verde_rlc_save_restore_register_list;
	adev->gfx.rlc.reg_list_size =
			(u32)ARRAY_SIZE(verde_rlc_save_restore_register_list);

	adev->gfx.rlc.cs_data = si_cs_data;
	src_ptr = adev->gfx.rlc.reg_list;
	dws = adev->gfx.rlc.reg_list_size;
	cs_data = adev->gfx.rlc.cs_data;

	if (src_ptr) {
		/* init save restore block */
		r = amdgpu_gfx_rlc_init_sr(adev, dws);
		if (r)
			return r;
	}

	if (cs_data) {
		/* clear state block */
		adev->gfx.rlc.clear_state_size = gfx_v6_0_get_csb_size(adev);
		dws = adev->gfx.rlc.clear_state_size + (256 / 4);

		r = amdgpu_bo_create_reserved(adev, dws * 4, PAGE_SIZE,
					      AMDGPU_GEM_DOMAIN_VRAM,
					      &adev->gfx.rlc.clear_state_obj,
					      &adev->gfx.rlc.clear_state_gpu_addr,
					      (void **)&adev->gfx.rlc.cs_ptr);
		if (r) {
			dev_warn(adev->dev, "(%d) create RLC c bo failed\n", r);
			amdgpu_gfx_rlc_fini(adev);
			return r;
		}

		/* set up the cs buffer */
		dst_ptr = adev->gfx.rlc.cs_ptr;
		reg_list_mc_addr = adev->gfx.rlc.clear_state_gpu_addr + 256;
		dst_ptr[0] = cpu_to_le32(upper_32_bits(reg_list_mc_addr));
		dst_ptr[1] = cpu_to_le32(lower_32_bits(reg_list_mc_addr));
		dst_ptr[2] = cpu_to_le32(adev->gfx.rlc.clear_state_size);
		gfx_v6_0_get_csb_buffer(adev, &dst_ptr[(256/4)]);
		amdgpu_bo_kunmap(adev->gfx.rlc.clear_state_obj);
		amdgpu_bo_unreserve(adev->gfx.rlc.clear_state_obj);
	}

	return 0;
}