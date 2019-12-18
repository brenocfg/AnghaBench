#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct common_firmware_header {int /*<<< orphan*/  ucode_size_bytes; int /*<<< orphan*/  ucode_version; } ;
struct TYPE_9__ {unsigned long max_handles; unsigned int fw_version; int num_uvd_inst; int harvest_config; int address_64_bit; int use_ctx_buf; int /*<<< orphan*/ ** filp; int /*<<< orphan*/ * handles; TYPE_2__* inst; TYPE_4__* fw; int /*<<< orphan*/  idle_work; } ;
struct TYPE_7__ {scalar_t__ load_type; } ;
struct amdgpu_device {int asic_type; TYPE_3__ uvd; int /*<<< orphan*/  dev; TYPE_1__ firmware; } ;
struct TYPE_10__ {scalar_t__ data; } ;
struct TYPE_8__ {int /*<<< orphan*/  cpu_addr; int /*<<< orphan*/  gpu_addr; int /*<<< orphan*/  vcpu_bo; } ;

/* Variables and functions */
 unsigned long AMDGPU_DEFAULT_UVD_HANDLES ; 
 scalar_t__ AMDGPU_FW_LOAD_PSP ; 
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_VRAM ; 
 scalar_t__ AMDGPU_GPU_PAGE_ALIGN (int) ; 
 void* AMDGPU_MAX_UVD_HANDLES ; 
 unsigned long AMDGPU_UVD_HEAP_SIZE ; 
 unsigned long AMDGPU_UVD_SESSION_SIZE ; 
 unsigned long AMDGPU_UVD_STACK_SIZE ; 
 int /*<<< orphan*/  AMD_IP_BLOCK_TYPE_UVD ; 
#define  CHIP_BONAIRE 143 
#define  CHIP_CARRIZO 142 
#define  CHIP_FIJI 141 
#define  CHIP_HAWAII 140 
#define  CHIP_KABINI 139 
#define  CHIP_KAVERI 138 
#define  CHIP_MULLINS 137 
#define  CHIP_POLARIS10 136 
#define  CHIP_POLARIS11 135 
#define  CHIP_POLARIS12 134 
#define  CHIP_STONEY 133 
#define  CHIP_TONGA 132 
#define  CHIP_VEGA10 131 
#define  CHIP_VEGA12 130 
#define  CHIP_VEGA20 129 
#define  CHIP_VEGAM 128 
 int /*<<< orphan*/  DRM_ERROR (char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  DRM_INFO (char*,unsigned int,unsigned int,unsigned int,...) ; 
 int EINVAL ; 
 char* FIRMWARE_BONAIRE ; 
 char* FIRMWARE_CARRIZO ; 
 char* FIRMWARE_FIJI ; 
 char* FIRMWARE_HAWAII ; 
 char* FIRMWARE_KABINI ; 
 char* FIRMWARE_KAVERI ; 
 char* FIRMWARE_MULLINS ; 
 char* FIRMWARE_POLARIS10 ; 
 char* FIRMWARE_POLARIS11 ; 
 char* FIRMWARE_POLARIS12 ; 
 char* FIRMWARE_STONEY ; 
 char* FIRMWARE_TONGA ; 
 char* FIRMWARE_VEGA10 ; 
 char* FIRMWARE_VEGA12 ; 
 char* FIRMWARE_VEGA20 ; 
 char* FIRMWARE_VEGAM ; 
 unsigned int FW_1_37_15 ; 
 unsigned int FW_1_65_10 ; 
 unsigned int FW_1_66_16 ; 
 unsigned int FW_1_87_11 ; 
 unsigned int FW_1_87_12 ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int amdgpu_bo_create_kernel (struct amdgpu_device*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_device_ip_block_version_cmp (struct amdgpu_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int amdgpu_ucode_validate (TYPE_4__*) ; 
 int /*<<< orphan*/  amdgpu_uvd_idle_work_handler ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (TYPE_4__*) ; 
 int request_firmware (TYPE_4__**,char const*,int /*<<< orphan*/ ) ; 

int amdgpu_uvd_sw_init(struct amdgpu_device *adev)
{
	unsigned long bo_size;
	const char *fw_name;
	const struct common_firmware_header *hdr;
	unsigned family_id;
	int i, j, r;

	INIT_DELAYED_WORK(&adev->uvd.idle_work, amdgpu_uvd_idle_work_handler);

	switch (adev->asic_type) {
#ifdef CONFIG_DRM_AMDGPU_CIK
	case CHIP_BONAIRE:
		fw_name = FIRMWARE_BONAIRE;
		break;
	case CHIP_KABINI:
		fw_name = FIRMWARE_KABINI;
		break;
	case CHIP_KAVERI:
		fw_name = FIRMWARE_KAVERI;
		break;
	case CHIP_HAWAII:
		fw_name = FIRMWARE_HAWAII;
		break;
	case CHIP_MULLINS:
		fw_name = FIRMWARE_MULLINS;
		break;
#endif
	case CHIP_TONGA:
		fw_name = FIRMWARE_TONGA;
		break;
	case CHIP_FIJI:
		fw_name = FIRMWARE_FIJI;
		break;
	case CHIP_CARRIZO:
		fw_name = FIRMWARE_CARRIZO;
		break;
	case CHIP_STONEY:
		fw_name = FIRMWARE_STONEY;
		break;
	case CHIP_POLARIS10:
		fw_name = FIRMWARE_POLARIS10;
		break;
	case CHIP_POLARIS11:
		fw_name = FIRMWARE_POLARIS11;
		break;
	case CHIP_POLARIS12:
		fw_name = FIRMWARE_POLARIS12;
		break;
	case CHIP_VEGA10:
		fw_name = FIRMWARE_VEGA10;
		break;
	case CHIP_VEGA12:
		fw_name = FIRMWARE_VEGA12;
		break;
	case CHIP_VEGAM:
		fw_name = FIRMWARE_VEGAM;
		break;
	case CHIP_VEGA20:
		fw_name = FIRMWARE_VEGA20;
		break;
	default:
		return -EINVAL;
	}

	r = request_firmware(&adev->uvd.fw, fw_name, adev->dev);
	if (r) {
		dev_err(adev->dev, "amdgpu_uvd: Can't load firmware \"%s\"\n",
			fw_name);
		return r;
	}

	r = amdgpu_ucode_validate(adev->uvd.fw);
	if (r) {
		dev_err(adev->dev, "amdgpu_uvd: Can't validate firmware \"%s\"\n",
			fw_name);
		release_firmware(adev->uvd.fw);
		adev->uvd.fw = NULL;
		return r;
	}

	/* Set the default UVD handles that the firmware can handle */
	adev->uvd.max_handles = AMDGPU_DEFAULT_UVD_HANDLES;

	hdr = (const struct common_firmware_header *)adev->uvd.fw->data;
	family_id = le32_to_cpu(hdr->ucode_version) & 0xff;

	if (adev->asic_type < CHIP_VEGA20) {
		unsigned version_major, version_minor;

		version_major = (le32_to_cpu(hdr->ucode_version) >> 24) & 0xff;
		version_minor = (le32_to_cpu(hdr->ucode_version) >> 8) & 0xff;
		DRM_INFO("Found UVD firmware Version: %hu.%hu Family ID: %hu\n",
			version_major, version_minor, family_id);

		/*
		 * Limit the number of UVD handles depending on microcode major
		 * and minor versions. The firmware version which has 40 UVD
		 * instances support is 1.80. So all subsequent versions should
		 * also have the same support.
		 */
		if ((version_major > 0x01) ||
		    ((version_major == 0x01) && (version_minor >= 0x50)))
			adev->uvd.max_handles = AMDGPU_MAX_UVD_HANDLES;

		adev->uvd.fw_version = ((version_major << 24) | (version_minor << 16) |
					(family_id << 8));

		if ((adev->asic_type == CHIP_POLARIS10 ||
		     adev->asic_type == CHIP_POLARIS11) &&
		    (adev->uvd.fw_version < FW_1_66_16))
			DRM_ERROR("POLARIS10/11 UVD firmware version %hu.%hu is too old.\n",
				  version_major, version_minor);
	} else {
		unsigned int enc_major, enc_minor, dec_minor;

		dec_minor = (le32_to_cpu(hdr->ucode_version) >> 8) & 0xff;
		enc_minor = (le32_to_cpu(hdr->ucode_version) >> 24) & 0x3f;
		enc_major = (le32_to_cpu(hdr->ucode_version) >> 30) & 0x3;
		DRM_INFO("Found UVD firmware ENC: %hu.%hu DEC: .%hu Family ID: %hu\n",
			enc_major, enc_minor, dec_minor, family_id);

		adev->uvd.max_handles = AMDGPU_MAX_UVD_HANDLES;

		adev->uvd.fw_version = le32_to_cpu(hdr->ucode_version);
	}

	bo_size = AMDGPU_UVD_STACK_SIZE + AMDGPU_UVD_HEAP_SIZE
		  +  AMDGPU_UVD_SESSION_SIZE * adev->uvd.max_handles;
	if (adev->firmware.load_type != AMDGPU_FW_LOAD_PSP)
		bo_size += AMDGPU_GPU_PAGE_ALIGN(le32_to_cpu(hdr->ucode_size_bytes) + 8);

	for (j = 0; j < adev->uvd.num_uvd_inst; j++) {
		if (adev->uvd.harvest_config & (1 << j))
			continue;
		r = amdgpu_bo_create_kernel(adev, bo_size, PAGE_SIZE,
					    AMDGPU_GEM_DOMAIN_VRAM, &adev->uvd.inst[j].vcpu_bo,
					    &adev->uvd.inst[j].gpu_addr, &adev->uvd.inst[j].cpu_addr);
		if (r) {
			dev_err(adev->dev, "(%d) failed to allocate UVD bo\n", r);
			return r;
		}
	}

	for (i = 0; i < adev->uvd.max_handles; ++i) {
		atomic_set(&adev->uvd.handles[i], 0);
		adev->uvd.filp[i] = NULL;
	}

	/* from uvd v5.0 HW addressing capacity increased to 64 bits */
	if (!amdgpu_device_ip_block_version_cmp(adev, AMD_IP_BLOCK_TYPE_UVD, 5, 0))
		adev->uvd.address_64_bit = true;

	switch (adev->asic_type) {
	case CHIP_TONGA:
		adev->uvd.use_ctx_buf = adev->uvd.fw_version >= FW_1_65_10;
		break;
	case CHIP_CARRIZO:
		adev->uvd.use_ctx_buf = adev->uvd.fw_version >= FW_1_87_11;
		break;
	case CHIP_FIJI:
		adev->uvd.use_ctx_buf = adev->uvd.fw_version >= FW_1_87_12;
		break;
	case CHIP_STONEY:
		adev->uvd.use_ctx_buf = adev->uvd.fw_version >= FW_1_37_15;
		break;
	default:
		adev->uvd.use_ctx_buf = adev->asic_type >= CHIP_POLARIS10;
	}

	return 0;
}