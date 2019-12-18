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
typedef  int u64 ;
typedef  unsigned long long u32 ;
struct TYPE_2__ {int vram_width; unsigned long long mc_vram_size; unsigned long long real_vram_size; int aper_base; unsigned long long aper_size; unsigned long long visible_vram_size; unsigned long long gart_size; } ;
struct amdgpu_device {int flags; int asic_type; TYPE_1__ gmc; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int AMD_IS_APU ; 
 int /*<<< orphan*/  CHANSIZE ; 
#define  CHIP_CARRIZO 135 
#define  CHIP_FIJI 134 
#define  CHIP_POLARIS10 133 
#define  CHIP_POLARIS11 132 
#define  CHIP_POLARIS12 131 
#define  CHIP_STONEY 130 
#define  CHIP_TONGA 129 
#define  CHIP_VEGAM 128 
 int /*<<< orphan*/  MC_ARB_RAMCFG ; 
 int /*<<< orphan*/  MC_SHARED_CHMAP ; 
 int /*<<< orphan*/  NOOFCHAN ; 
 int REG_GET_FIELD (unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long long RREG32 (int /*<<< orphan*/ ) ; 
 int amdgpu_atombios_get_vram_width (struct amdgpu_device*) ; 
 int amdgpu_device_resize_fb_bar (struct amdgpu_device*) ; 
 int amdgpu_gart_size ; 
 int /*<<< orphan*/  gmc_v8_0_vram_gtt_location (struct amdgpu_device*,TYPE_1__*) ; 
 int /*<<< orphan*/  mmCONFIG_MEMSIZE ; 
 int /*<<< orphan*/  mmMC_ARB_RAMCFG ; 
 int /*<<< orphan*/  mmMC_SHARED_CHMAP ; 
 int /*<<< orphan*/  mmMC_VM_FB_OFFSET ; 
 unsigned long long pci_resource_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pci_resource_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gmc_v8_0_mc_init(struct amdgpu_device *adev)
{
	int r;

	adev->gmc.vram_width = amdgpu_atombios_get_vram_width(adev);
	if (!adev->gmc.vram_width) {
		u32 tmp;
		int chansize, numchan;

		/* Get VRAM informations */
		tmp = RREG32(mmMC_ARB_RAMCFG);
		if (REG_GET_FIELD(tmp, MC_ARB_RAMCFG, CHANSIZE)) {
			chansize = 64;
		} else {
			chansize = 32;
		}
		tmp = RREG32(mmMC_SHARED_CHMAP);
		switch (REG_GET_FIELD(tmp, MC_SHARED_CHMAP, NOOFCHAN)) {
		case 0:
		default:
			numchan = 1;
			break;
		case 1:
			numchan = 2;
			break;
		case 2:
			numchan = 4;
			break;
		case 3:
			numchan = 8;
			break;
		case 4:
			numchan = 3;
			break;
		case 5:
			numchan = 6;
			break;
		case 6:
			numchan = 10;
			break;
		case 7:
			numchan = 12;
			break;
		case 8:
			numchan = 16;
			break;
		}
		adev->gmc.vram_width = numchan * chansize;
	}
	/* size in MB on si */
	adev->gmc.mc_vram_size = RREG32(mmCONFIG_MEMSIZE) * 1024ULL * 1024ULL;
	adev->gmc.real_vram_size = RREG32(mmCONFIG_MEMSIZE) * 1024ULL * 1024ULL;

	if (!(adev->flags & AMD_IS_APU)) {
		r = amdgpu_device_resize_fb_bar(adev);
		if (r)
			return r;
	}
	adev->gmc.aper_base = pci_resource_start(adev->pdev, 0);
	adev->gmc.aper_size = pci_resource_len(adev->pdev, 0);

#ifdef CONFIG_X86_64
	if (adev->flags & AMD_IS_APU) {
		adev->gmc.aper_base = ((u64)RREG32(mmMC_VM_FB_OFFSET)) << 22;
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
		case CHIP_POLARIS10: /* all engines support GPUVM */
		case CHIP_POLARIS11: /* all engines support GPUVM */
		case CHIP_POLARIS12: /* all engines support GPUVM */
		case CHIP_VEGAM:     /* all engines support GPUVM */
		default:
			adev->gmc.gart_size = 256ULL << 20;
			break;
		case CHIP_TONGA:   /* UVD, VCE do not support GPUVM */
		case CHIP_FIJI:    /* UVD, VCE do not support GPUVM */
		case CHIP_CARRIZO: /* UVD, VCE do not support GPUVM, DCE SG support */
		case CHIP_STONEY:  /* UVD does not support GPUVM, DCE SG support */
			adev->gmc.gart_size = 1024ULL << 20;
			break;
		}
	} else {
		adev->gmc.gart_size = (u64)amdgpu_gart_size << 20;
	}

	gmc_v8_0_vram_gtt_location(adev, &adev->gmc);

	return 0;
}