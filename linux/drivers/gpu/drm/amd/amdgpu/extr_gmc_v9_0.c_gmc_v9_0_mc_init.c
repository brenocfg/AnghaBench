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
typedef  int u64 ;
struct TYPE_6__ {int vram_width; unsigned long long mc_vram_size; unsigned long long real_vram_size; unsigned long long aper_size; unsigned long long visible_vram_size; unsigned long long gart_size; int /*<<< orphan*/  aper_base; } ;
struct amdgpu_device {int flags; int asic_type; TYPE_3__ gmc; int /*<<< orphan*/  pdev; TYPE_2__* nbio_funcs; TYPE_1__* df_funcs; } ;
struct TYPE_5__ {unsigned long long (* get_memsize ) (struct amdgpu_device*) ;} ;
struct TYPE_4__ {int (* get_hbm_channel_number ) (struct amdgpu_device*) ;} ;

/* Variables and functions */
 int AMD_IS_APU ; 
#define  CHIP_ARCTURUS 133 
#define  CHIP_RAVEN 132 
#define  CHIP_RENOIR 131 
#define  CHIP_VEGA10 130 
#define  CHIP_VEGA12 129 
#define  CHIP_VEGA20 128 
 int amdgpu_atomfirmware_get_vram_width (struct amdgpu_device*) ; 
 int amdgpu_device_resize_fb_bar (struct amdgpu_device*) ; 
 int amdgpu_emu_mode ; 
 int amdgpu_gart_size ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfxhub_v1_0_get_mc_fb_offset (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gmc_v9_0_vram_gtt_location (struct amdgpu_device*,TYPE_3__*) ; 
 unsigned long long pci_resource_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct amdgpu_device*) ; 
 unsigned long long stub2 (struct amdgpu_device*) ; 

__attribute__((used)) static int gmc_v9_0_mc_init(struct amdgpu_device *adev)
{
	int chansize, numchan;
	int r;

	if (amdgpu_sriov_vf(adev)) {
		/* For Vega10 SR-IOV, vram_width can't be read from ATOM as RAVEN,
		 * and DF related registers is not readable, seems hardcord is the
		 * only way to set the correct vram_width
		 */
		adev->gmc.vram_width = 2048;
	} else if (amdgpu_emu_mode != 1) {
		adev->gmc.vram_width = amdgpu_atomfirmware_get_vram_width(adev);
	}

	if (!adev->gmc.vram_width) {
		/* hbm memory channel size */
		if (adev->flags & AMD_IS_APU)
			chansize = 64;
		else
			chansize = 128;

		numchan = adev->df_funcs->get_hbm_channel_number(adev);
		adev->gmc.vram_width = numchan * chansize;
	}

	/* size in MB on si */
	adev->gmc.mc_vram_size =
		adev->nbio_funcs->get_memsize(adev) * 1024ULL * 1024ULL;
	adev->gmc.real_vram_size = adev->gmc.mc_vram_size;

	if (!(adev->flags & AMD_IS_APU)) {
		r = amdgpu_device_resize_fb_bar(adev);
		if (r)
			return r;
	}
	adev->gmc.aper_base = pci_resource_start(adev->pdev, 0);
	adev->gmc.aper_size = pci_resource_len(adev->pdev, 0);

#ifdef CONFIG_X86_64
	if (adev->flags & AMD_IS_APU) {
		adev->gmc.aper_base = gfxhub_v1_0_get_mc_fb_offset(adev);
		adev->gmc.aper_size = adev->gmc.real_vram_size;
	}
#endif
	/* In case the PCI BAR is larger than the actual amount of vram */
	adev->gmc.visible_vram_size = adev->gmc.aper_size;
	if (adev->gmc.visible_vram_size > adev->gmc.real_vram_size)
		adev->gmc.visible_vram_size = adev->gmc.real_vram_size;

	/* set the gart size */
	if (amdgpu_gart_size == -1) {
		switch (adev->asic_type) {
		case CHIP_VEGA10:  /* all engines support GPUVM */
		case CHIP_VEGA12:  /* all engines support GPUVM */
		case CHIP_VEGA20:
		case CHIP_ARCTURUS:
		default:
			adev->gmc.gart_size = 512ULL << 20;
			break;
		case CHIP_RAVEN:   /* DCE SG support */
		case CHIP_RENOIR:
			adev->gmc.gart_size = 1024ULL << 20;
			break;
		}
	} else {
		adev->gmc.gart_size = (u64)amdgpu_gart_size << 20;
	}

	gmc_v9_0_vram_gtt_location(adev, &adev->gmc);

	return 0;
}