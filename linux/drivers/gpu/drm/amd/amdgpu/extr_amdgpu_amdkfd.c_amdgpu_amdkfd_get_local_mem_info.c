#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct kgd_dev {int dummy; } ;
struct kfd_local_mem_info {int mem_clk_max; scalar_t__ local_mem_size_private; scalar_t__ local_mem_size_public; int /*<<< orphan*/  vram_width; } ;
struct TYPE_8__ {scalar_t__ pp_funcs; } ;
struct TYPE_7__ {int default_mclk; } ;
struct TYPE_6__ {int aper_base; int aper_size; int /*<<< orphan*/  vram_width; scalar_t__ real_vram_size; scalar_t__ visible_vram_size; } ;
struct amdgpu_device {TYPE_4__ powerplay; TYPE_3__ clock; TYPE_2__ gmc; TYPE_1__* dev; } ;
typedef  int resource_size_t ;
struct TYPE_5__ {unsigned long long* dma_mask; } ;

/* Variables and functions */
 int amdgpu_dpm_get_mclk (struct amdgpu_device*,int) ; 
 int amdgpu_emu_mode ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  memset (struct kfd_local_mem_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int*,int*,scalar_t__,scalar_t__) ; 

void amdgpu_amdkfd_get_local_mem_info(struct kgd_dev *kgd,
				      struct kfd_local_mem_info *mem_info)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)kgd;
	uint64_t address_mask = adev->dev->dma_mask ? ~*adev->dev->dma_mask :
					     ~((1ULL << 32) - 1);
	resource_size_t aper_limit = adev->gmc.aper_base + adev->gmc.aper_size;

	memset(mem_info, 0, sizeof(*mem_info));
	if (!(adev->gmc.aper_base & address_mask || aper_limit & address_mask)) {
		mem_info->local_mem_size_public = adev->gmc.visible_vram_size;
		mem_info->local_mem_size_private = adev->gmc.real_vram_size -
				adev->gmc.visible_vram_size;
	} else {
		mem_info->local_mem_size_public = 0;
		mem_info->local_mem_size_private = adev->gmc.real_vram_size;
	}
	mem_info->vram_width = adev->gmc.vram_width;

	pr_debug("Address base: %pap limit %pap public 0x%llx private 0x%llx\n",
			&adev->gmc.aper_base, &aper_limit,
			mem_info->local_mem_size_public,
			mem_info->local_mem_size_private);

	if (amdgpu_sriov_vf(adev))
		mem_info->mem_clk_max = adev->clock.default_mclk / 100;
	else if (adev->powerplay.pp_funcs) {
		if (amdgpu_emu_mode == 1)
			mem_info->mem_clk_max = 0;
		else
			mem_info->mem_clk_max = amdgpu_dpm_get_mclk(adev, false) / 100;
	} else
		mem_info->mem_clk_max = 100;
}