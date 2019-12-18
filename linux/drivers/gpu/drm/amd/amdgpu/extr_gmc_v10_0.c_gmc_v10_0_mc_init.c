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
typedef  int u64 ;
struct TYPE_4__ {int vram_width; unsigned long long aper_size; unsigned long long mc_vram_size; unsigned long long real_vram_size; unsigned long long visible_vram_size; unsigned long long gart_size; int /*<<< orphan*/  aper_base; } ;
struct amdgpu_device {int asic_type; TYPE_2__ gmc; TYPE_1__* nbio_funcs; int /*<<< orphan*/  pdev; } ;
struct TYPE_3__ {unsigned long long (* get_memsize ) (struct amdgpu_device*) ;} ;

/* Variables and functions */
#define  CHIP_NAVI10 130 
#define  CHIP_NAVI12 129 
#define  CHIP_NAVI14 128 
 int amdgpu_atomfirmware_get_vram_width (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_emu_mode ; 
 int amdgpu_gart_size ; 
 int /*<<< orphan*/  gmc_v10_0_vram_gtt_location (struct amdgpu_device*,TYPE_2__*) ; 
 unsigned long long pci_resource_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long long stub1 (struct amdgpu_device*) ; 

__attribute__((used)) static int gmc_v10_0_mc_init(struct amdgpu_device *adev)
{
	int chansize, numchan;

	if (!amdgpu_emu_mode)
		adev->gmc.vram_width = amdgpu_atomfirmware_get_vram_width(adev);
	else {
		/* hard code vram_width for emulation */
		chansize = 128;
		numchan = 1;
		adev->gmc.vram_width = numchan * chansize;
	}

	/* Could aper size report 0 ? */
	adev->gmc.aper_base = pci_resource_start(adev->pdev, 0);
	adev->gmc.aper_size = pci_resource_len(adev->pdev, 0);

	/* size in MB on si */
	adev->gmc.mc_vram_size =
		adev->nbio_funcs->get_memsize(adev) * 1024ULL * 1024ULL;
	adev->gmc.real_vram_size = adev->gmc.mc_vram_size;
	adev->gmc.visible_vram_size = adev->gmc.aper_size;

	/* In case the PCI BAR is larger than the actual amount of vram */
	if (adev->gmc.visible_vram_size > adev->gmc.real_vram_size)
		adev->gmc.visible_vram_size = adev->gmc.real_vram_size;

	/* set the gart size */
	if (amdgpu_gart_size == -1) {
		switch (adev->asic_type) {
		case CHIP_NAVI10:
		case CHIP_NAVI14:
		case CHIP_NAVI12:
		default:
			adev->gmc.gart_size = 512ULL << 20;
			break;
		}
	} else
		adev->gmc.gart_size = (u64)amdgpu_gart_size << 20;

	gmc_v10_0_vram_gtt_location(adev, &adev->gmc);

	return 0;
}