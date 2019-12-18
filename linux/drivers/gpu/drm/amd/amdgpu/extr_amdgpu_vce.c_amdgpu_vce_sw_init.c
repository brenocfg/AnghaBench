#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct common_firmware_header {int /*<<< orphan*/  ucode_version; } ;
struct TYPE_5__ {unsigned int fw_version; int /*<<< orphan*/  idle_mutex; int /*<<< orphan*/  idle_work; int /*<<< orphan*/ ** filp; int /*<<< orphan*/ * handles; int /*<<< orphan*/  cpu_addr; int /*<<< orphan*/  gpu_addr; int /*<<< orphan*/  vcpu_bo; TYPE_2__* fw; } ;
struct amdgpu_device {int asic_type; TYPE_1__ vce; int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_VRAM ; 
 int AMDGPU_MAX_VCE_HANDLES ; 
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
 int /*<<< orphan*/  DRM_INFO (char*,unsigned int,unsigned int,unsigned int) ; 
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
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int amdgpu_bo_create_kernel (struct amdgpu_device*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int amdgpu_ucode_validate (TYPE_2__*) ; 
 int /*<<< orphan*/  amdgpu_vce_idle_work_handler ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_firmware (TYPE_2__*) ; 
 int request_firmware (TYPE_2__**,char const*,int /*<<< orphan*/ ) ; 

int amdgpu_vce_sw_init(struct amdgpu_device *adev, unsigned long size)
{
	const char *fw_name;
	const struct common_firmware_header *hdr;
	unsigned ucode_version, version_major, version_minor, binary_id;
	int i, r;

	switch (adev->asic_type) {
#ifdef CONFIG_DRM_AMDGPU_CIK
	case CHIP_BONAIRE:
		fw_name = FIRMWARE_BONAIRE;
		break;
	case CHIP_KAVERI:
		fw_name = FIRMWARE_KAVERI;
		break;
	case CHIP_KABINI:
		fw_name = FIRMWARE_KABINI;
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
	case CHIP_CARRIZO:
		fw_name = FIRMWARE_CARRIZO;
		break;
	case CHIP_FIJI:
		fw_name = FIRMWARE_FIJI;
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
	case CHIP_VEGAM:
		fw_name = FIRMWARE_VEGAM;
		break;
	case CHIP_VEGA10:
		fw_name = FIRMWARE_VEGA10;
		break;
	case CHIP_VEGA12:
		fw_name = FIRMWARE_VEGA12;
		break;
	case CHIP_VEGA20:
		fw_name = FIRMWARE_VEGA20;
		break;

	default:
		return -EINVAL;
	}

	r = request_firmware(&adev->vce.fw, fw_name, adev->dev);
	if (r) {
		dev_err(adev->dev, "amdgpu_vce: Can't load firmware \"%s\"\n",
			fw_name);
		return r;
	}

	r = amdgpu_ucode_validate(adev->vce.fw);
	if (r) {
		dev_err(adev->dev, "amdgpu_vce: Can't validate firmware \"%s\"\n",
			fw_name);
		release_firmware(adev->vce.fw);
		adev->vce.fw = NULL;
		return r;
	}

	hdr = (const struct common_firmware_header *)adev->vce.fw->data;

	ucode_version = le32_to_cpu(hdr->ucode_version);
	version_major = (ucode_version >> 20) & 0xfff;
	version_minor = (ucode_version >> 8) & 0xfff;
	binary_id = ucode_version & 0xff;
	DRM_INFO("Found VCE firmware Version: %hhd.%hhd Binary ID: %hhd\n",
		version_major, version_minor, binary_id);
	adev->vce.fw_version = ((version_major << 24) | (version_minor << 16) |
				(binary_id << 8));

	r = amdgpu_bo_create_kernel(adev, size, PAGE_SIZE,
				    AMDGPU_GEM_DOMAIN_VRAM, &adev->vce.vcpu_bo,
				    &adev->vce.gpu_addr, &adev->vce.cpu_addr);
	if (r) {
		dev_err(adev->dev, "(%d) failed to allocate VCE bo\n", r);
		return r;
	}

	for (i = 0; i < AMDGPU_MAX_VCE_HANDLES; ++i) {
		atomic_set(&adev->vce.handles[i], 0);
		adev->vce.filp[i] = NULL;
	}

	INIT_DELAYED_WORK(&adev->vce.idle_work, amdgpu_vce_idle_work_handler);
	mutex_init(&adev->vce.idle_mutex);

	return 0;
}