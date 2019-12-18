#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct common_firmware_header {int /*<<< orphan*/  ucode_size_bytes; int /*<<< orphan*/  ucode_version; } ;
struct TYPE_11__ {int indirect_sram; int fw_version; int num_vcn_inst; int harvest_config; int /*<<< orphan*/  dpg_sram_cpu_addr; int /*<<< orphan*/  dpg_sram_gpu_addr; int /*<<< orphan*/  dpg_sram_bo; TYPE_3__* inst; TYPE_5__* fw; int /*<<< orphan*/  idle_work; } ;
struct TYPE_9__ {scalar_t__ load_type; } ;
struct amdgpu_device {int asic_type; int rev_id; int pg_flags; int /*<<< orphan*/  dev; TYPE_4__ vcn; TYPE_2__ firmware; TYPE_1__* pdev; } ;
struct TYPE_12__ {scalar_t__ data; } ;
struct TYPE_10__ {int /*<<< orphan*/  cpu_addr; int /*<<< orphan*/  gpu_addr; int /*<<< orphan*/  vcpu_bo; } ;
struct TYPE_8__ {int device; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_FW_LOAD_PSP ; 
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_VRAM ; 
 scalar_t__ AMDGPU_GPU_PAGE_ALIGN (int) ; 
 unsigned long AMDGPU_VCN_CONTEXT_SIZE ; 
 unsigned long AMDGPU_VCN_STACK_SIZE ; 
 int AMD_PG_SUPPORT_VCN_DPG ; 
#define  CHIP_ARCTURUS 133 
#define  CHIP_NAVI10 132 
#define  CHIP_NAVI12 131 
#define  CHIP_NAVI14 130 
#define  CHIP_RAVEN 129 
#define  CHIP_RENOIR 128 
 int /*<<< orphan*/  DRM_INFO (char*,unsigned int,unsigned int,unsigned int,...) ; 
 int EINVAL ; 
 char* FIRMWARE_ARCTURUS ; 
 char* FIRMWARE_NAVI10 ; 
 char* FIRMWARE_NAVI12 ; 
 char* FIRMWARE_NAVI14 ; 
 char* FIRMWARE_PICASSO ; 
 char* FIRMWARE_RAVEN ; 
 char* FIRMWARE_RAVEN2 ; 
 char* FIRMWARE_RENOIR ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int amdgpu_bo_create_kernel (struct amdgpu_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int amdgpu_ucode_validate (TYPE_5__*) ; 
 int /*<<< orphan*/  amdgpu_vcn_idle_work_handler ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (TYPE_5__*) ; 
 int request_firmware (TYPE_5__**,char const*,int /*<<< orphan*/ ) ; 

int amdgpu_vcn_sw_init(struct amdgpu_device *adev)
{
	unsigned long bo_size;
	const char *fw_name;
	const struct common_firmware_header *hdr;
	unsigned char fw_check;
	int i, r;

	INIT_DELAYED_WORK(&adev->vcn.idle_work, amdgpu_vcn_idle_work_handler);

	switch (adev->asic_type) {
	case CHIP_RAVEN:
		if (adev->rev_id >= 8)
			fw_name = FIRMWARE_RAVEN2;
		else if (adev->pdev->device == 0x15d8)
			fw_name = FIRMWARE_PICASSO;
		else
			fw_name = FIRMWARE_RAVEN;
		break;
	case CHIP_ARCTURUS:
		fw_name = FIRMWARE_ARCTURUS;
		break;
	case CHIP_RENOIR:
		fw_name = FIRMWARE_RENOIR;
		if ((adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) &&
		    (adev->pg_flags & AMD_PG_SUPPORT_VCN_DPG))
			adev->vcn.indirect_sram = true;
		break;
	case CHIP_NAVI10:
		fw_name = FIRMWARE_NAVI10;
		if ((adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) &&
		    (adev->pg_flags & AMD_PG_SUPPORT_VCN_DPG))
			adev->vcn.indirect_sram = true;
		break;
	case CHIP_NAVI14:
		fw_name = FIRMWARE_NAVI14;
		if ((adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) &&
		    (adev->pg_flags & AMD_PG_SUPPORT_VCN_DPG))
			adev->vcn.indirect_sram = true;
		break;
	case CHIP_NAVI12:
		fw_name = FIRMWARE_NAVI12;
		if ((adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) &&
		    (adev->pg_flags & AMD_PG_SUPPORT_VCN_DPG))
			adev->vcn.indirect_sram = true;
		break;
	default:
		return -EINVAL;
	}

	r = request_firmware(&adev->vcn.fw, fw_name, adev->dev);
	if (r) {
		dev_err(adev->dev, "amdgpu_vcn: Can't load firmware \"%s\"\n",
			fw_name);
		return r;
	}

	r = amdgpu_ucode_validate(adev->vcn.fw);
	if (r) {
		dev_err(adev->dev, "amdgpu_vcn: Can't validate firmware \"%s\"\n",
			fw_name);
		release_firmware(adev->vcn.fw);
		adev->vcn.fw = NULL;
		return r;
	}

	hdr = (const struct common_firmware_header *)adev->vcn.fw->data;
	adev->vcn.fw_version = le32_to_cpu(hdr->ucode_version);

	/* Bit 20-23, it is encode major and non-zero for new naming convention.
	 * This field is part of version minor and DRM_DISABLED_FLAG in old naming
	 * convention. Since the l:wq!atest version minor is 0x5B and DRM_DISABLED_FLAG
	 * is zero in old naming convention, this field is always zero so far.
	 * These four bits are used to tell which naming convention is present.
	 */
	fw_check = (le32_to_cpu(hdr->ucode_version) >> 20) & 0xf;
	if (fw_check) {
		unsigned int dec_ver, enc_major, enc_minor, vep, fw_rev;

		fw_rev = le32_to_cpu(hdr->ucode_version) & 0xfff;
		enc_minor = (le32_to_cpu(hdr->ucode_version) >> 12) & 0xff;
		enc_major = fw_check;
		dec_ver = (le32_to_cpu(hdr->ucode_version) >> 24) & 0xf;
		vep = (le32_to_cpu(hdr->ucode_version) >> 28) & 0xf;
		DRM_INFO("Found VCN firmware Version ENC: %hu.%hu DEC: %hu VEP: %hu Revision: %hu\n",
			enc_major, enc_minor, dec_ver, vep, fw_rev);
	} else {
		unsigned int version_major, version_minor, family_id;

		family_id = le32_to_cpu(hdr->ucode_version) & 0xff;
		version_major = (le32_to_cpu(hdr->ucode_version) >> 24) & 0xff;
		version_minor = (le32_to_cpu(hdr->ucode_version) >> 8) & 0xff;
		DRM_INFO("Found VCN firmware Version: %hu.%hu Family ID: %hu\n",
			version_major, version_minor, family_id);
	}

	bo_size = AMDGPU_VCN_STACK_SIZE + AMDGPU_VCN_CONTEXT_SIZE;
	if (adev->firmware.load_type != AMDGPU_FW_LOAD_PSP)
		bo_size += AMDGPU_GPU_PAGE_ALIGN(le32_to_cpu(hdr->ucode_size_bytes) + 8);

	for (i = 0; i < adev->vcn.num_vcn_inst; i++) {
		if (adev->vcn.harvest_config & (1 << i))
			continue;

		r = amdgpu_bo_create_kernel(adev, bo_size, PAGE_SIZE,
						AMDGPU_GEM_DOMAIN_VRAM, &adev->vcn.inst[i].vcpu_bo,
						&adev->vcn.inst[i].gpu_addr, &adev->vcn.inst[i].cpu_addr);
		if (r) {
			dev_err(adev->dev, "(%d) failed to allocate vcn bo\n", r);
			return r;
		}
	}

	if (adev->vcn.indirect_sram) {
		r = amdgpu_bo_create_kernel(adev, 64 * 2 * 4, PAGE_SIZE,
			    AMDGPU_GEM_DOMAIN_VRAM, &adev->vcn.dpg_sram_bo,
			    &adev->vcn.dpg_sram_gpu_addr, &adev->vcn.dpg_sram_cpu_addr);
		if (r) {
			dev_err(adev->dev, "(%d) failed to allocate DPG bo\n", r);
			return r;
		}
	}

	return 0;
}