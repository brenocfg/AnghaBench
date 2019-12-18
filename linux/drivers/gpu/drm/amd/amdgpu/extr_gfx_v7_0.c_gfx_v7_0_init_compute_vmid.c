#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct amdgpu_device {int /*<<< orphan*/  srbm_mutex; } ;
struct TYPE_2__ {int /*<<< orphan*/  oa; int /*<<< orphan*/  gws; int /*<<< orphan*/  mem_size; int /*<<< orphan*/  mem_base; } ;

/* Variables and functions */
 int DEFAULT_SH_MEM_BASES ; 
 int FIRST_COMPUTE_VMID ; 
 int LAST_COMPUTE_VMID ; 
 int MTYPE_NONCACHED ; 
 int SH_MEM_ALIGNMENT_MODE_UNALIGNED ; 
 int SH_MEM_CONFIG__ALIGNMENT_MODE__SHIFT ; 
 int SH_MEM_CONFIG__DEFAULT_MTYPE__SHIFT ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* amdgpu_gds_reg_offset ; 
 int /*<<< orphan*/  cik_srbm_select (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmSH_MEM_APE1_BASE ; 
 int /*<<< orphan*/  mmSH_MEM_APE1_LIMIT ; 
 int /*<<< orphan*/  mmSH_MEM_BASES ; 
 int /*<<< orphan*/  mmSH_MEM_CONFIG ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gfx_v7_0_init_compute_vmid(struct amdgpu_device *adev)
{
	int i;
	uint32_t sh_mem_config;
	uint32_t sh_mem_bases;

	/*
	 * Configure apertures:
	 * LDS:         0x60000000'00000000 - 0x60000001'00000000 (4GB)
	 * Scratch:     0x60000001'00000000 - 0x60000002'00000000 (4GB)
	 * GPUVM:       0x60010000'00000000 - 0x60020000'00000000 (1TB)
	*/
	sh_mem_bases = DEFAULT_SH_MEM_BASES | (DEFAULT_SH_MEM_BASES << 16);
	sh_mem_config = SH_MEM_ALIGNMENT_MODE_UNALIGNED <<
			SH_MEM_CONFIG__ALIGNMENT_MODE__SHIFT;
	sh_mem_config |= MTYPE_NONCACHED << SH_MEM_CONFIG__DEFAULT_MTYPE__SHIFT;
	mutex_lock(&adev->srbm_mutex);
	for (i = FIRST_COMPUTE_VMID; i < LAST_COMPUTE_VMID; i++) {
		cik_srbm_select(adev, 0, 0, 0, i);
		/* CP and shaders */
		WREG32(mmSH_MEM_CONFIG, sh_mem_config);
		WREG32(mmSH_MEM_APE1_BASE, 1);
		WREG32(mmSH_MEM_APE1_LIMIT, 0);
		WREG32(mmSH_MEM_BASES, sh_mem_bases);
	}
	cik_srbm_select(adev, 0, 0, 0, 0);
	mutex_unlock(&adev->srbm_mutex);

	/* Initialize all compute VMIDs to have no GDS, GWS, or OA
	   acccess. These should be enabled by FW for target VMIDs. */
	for (i = FIRST_COMPUTE_VMID; i < LAST_COMPUTE_VMID; i++) {
		WREG32(amdgpu_gds_reg_offset[i].mem_base, 0);
		WREG32(amdgpu_gds_reg_offset[i].mem_size, 0);
		WREG32(amdgpu_gds_reg_offset[i].gws, 0);
		WREG32(amdgpu_gds_reg_offset[i].oa, 0);
	}
}