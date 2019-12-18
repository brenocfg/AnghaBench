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
struct TYPE_11__ {int /*<<< orphan*/  ucode_version; int /*<<< orphan*/  ucode_size_bytes; } ;
struct dmcu_firmware_header_v1_0 {TYPE_4__ header; int /*<<< orphan*/  intv_size_bytes; } ;
struct TYPE_10__ {scalar_t__ dmcu_fw_version; TYPE_5__* fw_dmcu; } ;
struct TYPE_9__ {scalar_t__ load_type; int /*<<< orphan*/  fw_size; TYPE_1__* ucode; } ;
struct amdgpu_device {int asic_type; TYPE_3__ dm; TYPE_2__ firmware; int /*<<< orphan*/  dev; int /*<<< orphan*/  external_rev_id; } ;
struct TYPE_12__ {scalar_t__ data; } ;
struct TYPE_8__ {size_t ucode_id; TYPE_5__* fw; } ;

/* Variables and functions */
 scalar_t__ ALIGN (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ AMDGPU_FW_LOAD_PSP ; 
 size_t AMDGPU_UCODE_ID_DMCU_ERAM ; 
 size_t AMDGPU_UCODE_ID_DMCU_INTV ; 
 int /*<<< orphan*/  ASICREV_IS_PICASSO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASICREV_IS_RAVEN2 (int /*<<< orphan*/ ) ; 
#define  CHIP_BONAIRE 148 
#define  CHIP_CARRIZO 147 
#define  CHIP_FIJI 146 
#define  CHIP_HAWAII 145 
#define  CHIP_KABINI 144 
#define  CHIP_KAVERI 143 
#define  CHIP_MULLINS 142 
#define  CHIP_NAVI10 141 
#define  CHIP_NAVI12 140 
#define  CHIP_NAVI14 139 
#define  CHIP_POLARIS10 138 
#define  CHIP_POLARIS11 137 
#define  CHIP_POLARIS12 136 
#define  CHIP_RAVEN 135 
#define  CHIP_RENOIR 134 
#define  CHIP_STONEY 133 
#define  CHIP_TONGA 132 
#define  CHIP_VEGA10 131 
#define  CHIP_VEGA12 130 
#define  CHIP_VEGA20 129 
#define  CHIP_VEGAM 128 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int EINVAL ; 
 int ENOENT ; 
 char* FIRMWARE_RAVEN_DMCU ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int amdgpu_ucode_validate (TYPE_5__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (TYPE_5__*) ; 
 int request_firmware_direct (TYPE_5__**,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int load_dmcu_fw(struct amdgpu_device *adev)
{
	const char *fw_name_dmcu = NULL;
	int r;
	const struct dmcu_firmware_header_v1_0 *hdr;

	switch(adev->asic_type) {
	case CHIP_BONAIRE:
	case CHIP_HAWAII:
	case CHIP_KAVERI:
	case CHIP_KABINI:
	case CHIP_MULLINS:
	case CHIP_TONGA:
	case CHIP_FIJI:
	case CHIP_CARRIZO:
	case CHIP_STONEY:
	case CHIP_POLARIS11:
	case CHIP_POLARIS10:
	case CHIP_POLARIS12:
	case CHIP_VEGAM:
	case CHIP_VEGA10:
	case CHIP_VEGA12:
	case CHIP_VEGA20:
	case CHIP_NAVI10:
	case CHIP_NAVI14:
	case CHIP_NAVI12:
	case CHIP_RENOIR:
		return 0;
	case CHIP_RAVEN:
		if (ASICREV_IS_PICASSO(adev->external_rev_id))
			fw_name_dmcu = FIRMWARE_RAVEN_DMCU;
		else if (ASICREV_IS_RAVEN2(adev->external_rev_id))
			fw_name_dmcu = FIRMWARE_RAVEN_DMCU;
		else
			return 0;
		break;
	default:
		DRM_ERROR("Unsupported ASIC type: 0x%X\n", adev->asic_type);
		return -EINVAL;
	}

	if (adev->firmware.load_type != AMDGPU_FW_LOAD_PSP) {
		DRM_DEBUG_KMS("dm: DMCU firmware not supported on direct or SMU loading\n");
		return 0;
	}

	r = request_firmware_direct(&adev->dm.fw_dmcu, fw_name_dmcu, adev->dev);
	if (r == -ENOENT) {
		/* DMCU firmware is not necessary, so don't raise a fuss if it's missing */
		DRM_DEBUG_KMS("dm: DMCU firmware not found\n");
		adev->dm.fw_dmcu = NULL;
		return 0;
	}
	if (r) {
		dev_err(adev->dev, "amdgpu_dm: Can't load firmware \"%s\"\n",
			fw_name_dmcu);
		return r;
	}

	r = amdgpu_ucode_validate(adev->dm.fw_dmcu);
	if (r) {
		dev_err(adev->dev, "amdgpu_dm: Can't validate firmware \"%s\"\n",
			fw_name_dmcu);
		release_firmware(adev->dm.fw_dmcu);
		adev->dm.fw_dmcu = NULL;
		return r;
	}

	hdr = (const struct dmcu_firmware_header_v1_0 *)adev->dm.fw_dmcu->data;
	adev->firmware.ucode[AMDGPU_UCODE_ID_DMCU_ERAM].ucode_id = AMDGPU_UCODE_ID_DMCU_ERAM;
	adev->firmware.ucode[AMDGPU_UCODE_ID_DMCU_ERAM].fw = adev->dm.fw_dmcu;
	adev->firmware.fw_size +=
		ALIGN(le32_to_cpu(hdr->header.ucode_size_bytes) - le32_to_cpu(hdr->intv_size_bytes), PAGE_SIZE);

	adev->firmware.ucode[AMDGPU_UCODE_ID_DMCU_INTV].ucode_id = AMDGPU_UCODE_ID_DMCU_INTV;
	adev->firmware.ucode[AMDGPU_UCODE_ID_DMCU_INTV].fw = adev->dm.fw_dmcu;
	adev->firmware.fw_size +=
		ALIGN(le32_to_cpu(hdr->intv_size_bytes), PAGE_SIZE);

	adev->dm.dmcu_fw_version = le32_to_cpu(hdr->header.ucode_version);

	DRM_DEBUG_KMS("PSP loading DMCU firmware\n");

	return 0;
}