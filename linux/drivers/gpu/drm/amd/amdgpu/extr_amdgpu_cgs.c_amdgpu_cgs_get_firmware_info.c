#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  void* uint32_t ;
typedef  void* uint16_t ;
struct TYPE_15__ {int /*<<< orphan*/  ucode_array_offset_bytes; int /*<<< orphan*/  ucode_size_bytes; int /*<<< orphan*/  ucode_version; } ;
struct smc_firmware_header_v1_0 {TYPE_8__ header; int /*<<< orphan*/  ucode_start_addr; } ;
struct TYPE_10__ {int /*<<< orphan*/  ucode_version; int /*<<< orphan*/  ucode_size_bytes; } ;
struct gfx_firmware_header_v1_0 {int /*<<< orphan*/  ucode_feature_version; int /*<<< orphan*/  jt_offset; TYPE_1__ header; int /*<<< orphan*/  jt_size; } ;
struct common_firmware_header {int /*<<< orphan*/  ucode_size_bytes; } ;
struct cgs_firmware_info {int image_size; int version; int is_kicker; void* kptr; void* ucode_start_address; void* feature_version; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  mc_addr; } ;
struct cgs_device {int dummy; } ;
struct amdgpu_firmware_info {size_t ucode_id; TYPE_5__* fw; void* kaddr; int /*<<< orphan*/  mc_addr; } ;
typedef  enum cgs_ucode_id { ____Placeholder_cgs_ucode_id } cgs_ucode_id ;
typedef  enum AMDGPU_UCODE_ID { ____Placeholder_AMDGPU_UCODE_ID } AMDGPU_UCODE_ID ;
struct TYPE_13__ {int fw_version; TYPE_5__* fw; } ;
struct TYPE_12__ {scalar_t__ load_type; int /*<<< orphan*/  fw_size; struct amdgpu_firmware_info* ucode; } ;
struct TYPE_16__ {int asic_type; TYPE_4__ pm; TYPE_3__ firmware; int /*<<< orphan*/  dev; TYPE_2__* pdev; } ;
struct TYPE_14__ {int data; } ;
struct TYPE_11__ {int revision; int device; } ;

/* Variables and functions */
 scalar_t__ ALIGN (int,int /*<<< orphan*/ ) ; 
 scalar_t__ AMDGPU_FW_LOAD_PSP ; 
 size_t AMDGPU_UCODE_ID_SMC ; 
 int /*<<< orphan*/  CGS_FUNC_ADEV ; 
 int CGS_UCODE_ID_CP_MEC ; 
 int CGS_UCODE_ID_CP_MEC_JT1 ; 
 int CGS_UCODE_ID_CP_MEC_JT2 ; 
 int CGS_UCODE_ID_SMU ; 
 int CGS_UCODE_ID_SMU_SK ; 
#define  CHIP_BONAIRE 144 
#define  CHIP_FIJI 143 
#define  CHIP_HAINAN 142 
#define  CHIP_HAWAII 141 
#define  CHIP_OLAND 140 
#define  CHIP_PITCAIRN 139 
#define  CHIP_POLARIS10 138 
#define  CHIP_POLARIS11 137 
#define  CHIP_POLARIS12 136 
#define  CHIP_TAHITI 135 
#define  CHIP_TONGA 134 
#define  CHIP_TOPAZ 133 
#define  CHIP_VEGA10 132 
#define  CHIP_VEGA12 131 
#define  CHIP_VEGA20 130 
#define  CHIP_VEGAM 129 
#define  CHIP_VERDE 128 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 TYPE_9__* adev ; 
 int /*<<< orphan*/  amdgpu_get_firmware_version (struct cgs_device*,int) ; 
 int /*<<< orphan*/  amdgpu_ucode_print_smc_hdr (TYPE_8__*) ; 
 int amdgpu_ucode_validate (TYPE_5__*) ; 
 int fw_type_convert (struct cgs_device*,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (TYPE_5__*) ; 
 int request_firmware (TYPE_5__**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static int amdgpu_cgs_get_firmware_info(struct cgs_device *cgs_device,
					enum cgs_ucode_id type,
					struct cgs_firmware_info *info)
{
	CGS_FUNC_ADEV;

	if ((CGS_UCODE_ID_SMU != type) && (CGS_UCODE_ID_SMU_SK != type)) {
		uint64_t gpu_addr;
		uint32_t data_size;
		const struct gfx_firmware_header_v1_0 *header;
		enum AMDGPU_UCODE_ID id;
		struct amdgpu_firmware_info *ucode;

		id = fw_type_convert(cgs_device, type);
		ucode = &adev->firmware.ucode[id];
		if (ucode->fw == NULL)
			return -EINVAL;

		gpu_addr  = ucode->mc_addr;
		header = (const struct gfx_firmware_header_v1_0 *)ucode->fw->data;
		data_size = le32_to_cpu(header->header.ucode_size_bytes);

		if ((type == CGS_UCODE_ID_CP_MEC_JT1) ||
		    (type == CGS_UCODE_ID_CP_MEC_JT2)) {
			gpu_addr += ALIGN(le32_to_cpu(header->header.ucode_size_bytes), PAGE_SIZE);
			data_size = le32_to_cpu(header->jt_size) << 2;
		}

		info->kptr = ucode->kaddr;
		info->image_size = data_size;
		info->mc_addr = gpu_addr;
		info->version = (uint16_t)le32_to_cpu(header->header.ucode_version);

		if (CGS_UCODE_ID_CP_MEC == type)
			info->image_size = le32_to_cpu(header->jt_offset) << 2;

		info->fw_version = amdgpu_get_firmware_version(cgs_device, type);
		info->feature_version = (uint16_t)le32_to_cpu(header->ucode_feature_version);
	} else {
		char fw_name[30] = {0};
		int err = 0;
		uint32_t ucode_size;
		uint32_t ucode_start_address;
		const uint8_t *src;
		const struct smc_firmware_header_v1_0 *hdr;
		const struct common_firmware_header *header;
		struct amdgpu_firmware_info *ucode = NULL;

		if (!adev->pm.fw) {
			switch (adev->asic_type) {
			case CHIP_TAHITI:
				strcpy(fw_name, "radeon/tahiti_smc.bin");
				break;
			case CHIP_PITCAIRN:
				if ((adev->pdev->revision == 0x81) &&
				    ((adev->pdev->device == 0x6810) ||
				    (adev->pdev->device == 0x6811))) {
					info->is_kicker = true;
					strcpy(fw_name, "radeon/pitcairn_k_smc.bin");
				} else {
					strcpy(fw_name, "radeon/pitcairn_smc.bin");
				}
				break;
			case CHIP_VERDE:
				if (((adev->pdev->device == 0x6820) &&
					((adev->pdev->revision == 0x81) ||
					(adev->pdev->revision == 0x83))) ||
				    ((adev->pdev->device == 0x6821) &&
					((adev->pdev->revision == 0x83) ||
					(adev->pdev->revision == 0x87))) ||
				    ((adev->pdev->revision == 0x87) &&
					((adev->pdev->device == 0x6823) ||
					(adev->pdev->device == 0x682b)))) {
					info->is_kicker = true;
					strcpy(fw_name, "radeon/verde_k_smc.bin");
				} else {
					strcpy(fw_name, "radeon/verde_smc.bin");
				}
				break;
			case CHIP_OLAND:
				if (((adev->pdev->revision == 0x81) &&
					((adev->pdev->device == 0x6600) ||
					(adev->pdev->device == 0x6604) ||
					(adev->pdev->device == 0x6605) ||
					(adev->pdev->device == 0x6610))) ||
				    ((adev->pdev->revision == 0x83) &&
					(adev->pdev->device == 0x6610))) {
					info->is_kicker = true;
					strcpy(fw_name, "radeon/oland_k_smc.bin");
				} else {
					strcpy(fw_name, "radeon/oland_smc.bin");
				}
				break;
			case CHIP_HAINAN:
				if (((adev->pdev->revision == 0x81) &&
					(adev->pdev->device == 0x6660)) ||
				    ((adev->pdev->revision == 0x83) &&
					((adev->pdev->device == 0x6660) ||
					(adev->pdev->device == 0x6663) ||
					(adev->pdev->device == 0x6665) ||
					 (adev->pdev->device == 0x6667)))) {
					info->is_kicker = true;
					strcpy(fw_name, "radeon/hainan_k_smc.bin");
				} else if ((adev->pdev->revision == 0xc3) &&
					 (adev->pdev->device == 0x6665)) {
					info->is_kicker = true;
					strcpy(fw_name, "radeon/banks_k_2_smc.bin");
				} else {
					strcpy(fw_name, "radeon/hainan_smc.bin");
				}
				break;
			case CHIP_BONAIRE:
				if ((adev->pdev->revision == 0x80) ||
					(adev->pdev->revision == 0x81) ||
					(adev->pdev->device == 0x665f)) {
					info->is_kicker = true;
					strcpy(fw_name, "amdgpu/bonaire_k_smc.bin");
				} else {
					strcpy(fw_name, "amdgpu/bonaire_smc.bin");
				}
				break;
			case CHIP_HAWAII:
				if (adev->pdev->revision == 0x80) {
					info->is_kicker = true;
					strcpy(fw_name, "amdgpu/hawaii_k_smc.bin");
				} else {
					strcpy(fw_name, "amdgpu/hawaii_smc.bin");
				}
				break;
			case CHIP_TOPAZ:
				if (((adev->pdev->device == 0x6900) && (adev->pdev->revision == 0x81)) ||
				    ((adev->pdev->device == 0x6900) && (adev->pdev->revision == 0x83)) ||
				    ((adev->pdev->device == 0x6907) && (adev->pdev->revision == 0x87)) ||
				    ((adev->pdev->device == 0x6900) && (adev->pdev->revision == 0xD1)) ||
				    ((adev->pdev->device == 0x6900) && (adev->pdev->revision == 0xD3))) {
					info->is_kicker = true;
					strcpy(fw_name, "amdgpu/topaz_k_smc.bin");
				} else
					strcpy(fw_name, "amdgpu/topaz_smc.bin");
				break;
			case CHIP_TONGA:
				if (((adev->pdev->device == 0x6939) && (adev->pdev->revision == 0xf1)) ||
				    ((adev->pdev->device == 0x6938) && (adev->pdev->revision == 0xf1))) {
					info->is_kicker = true;
					strcpy(fw_name, "amdgpu/tonga_k_smc.bin");
				} else
					strcpy(fw_name, "amdgpu/tonga_smc.bin");
				break;
			case CHIP_FIJI:
				strcpy(fw_name, "amdgpu/fiji_smc.bin");
				break;
			case CHIP_POLARIS11:
				if (type == CGS_UCODE_ID_SMU) {
					if (((adev->pdev->device == 0x67ef) &&
					     ((adev->pdev->revision == 0xe0) ||
					      (adev->pdev->revision == 0xe5))) ||
					    ((adev->pdev->device == 0x67ff) &&
					     ((adev->pdev->revision == 0xcf) ||
					      (adev->pdev->revision == 0xef) ||
					      (adev->pdev->revision == 0xff)))) {
						info->is_kicker = true;
						strcpy(fw_name, "amdgpu/polaris11_k_smc.bin");
					} else if ((adev->pdev->device == 0x67ef) &&
						   (adev->pdev->revision == 0xe2)) {
						info->is_kicker = true;
						strcpy(fw_name, "amdgpu/polaris11_k2_smc.bin");
					} else {
						strcpy(fw_name, "amdgpu/polaris11_smc.bin");
					}
				} else if (type == CGS_UCODE_ID_SMU_SK) {
					strcpy(fw_name, "amdgpu/polaris11_smc_sk.bin");
				}
				break;
			case CHIP_POLARIS10:
				if (type == CGS_UCODE_ID_SMU) {
					if (((adev->pdev->device == 0x67df) &&
					     ((adev->pdev->revision == 0xe0) ||
					      (adev->pdev->revision == 0xe3) ||
					      (adev->pdev->revision == 0xe4) ||
					      (adev->pdev->revision == 0xe5) ||
					      (adev->pdev->revision == 0xe7) ||
					      (adev->pdev->revision == 0xef))) ||
					    ((adev->pdev->device == 0x6fdf) &&
					     ((adev->pdev->revision == 0xef) ||
					      (adev->pdev->revision == 0xff)))) {
						info->is_kicker = true;
						strcpy(fw_name, "amdgpu/polaris10_k_smc.bin");
					} else if ((adev->pdev->device == 0x67df) &&
						   ((adev->pdev->revision == 0xe1) ||
						    (adev->pdev->revision == 0xf7))) {
						info->is_kicker = true;
						strcpy(fw_name, "amdgpu/polaris10_k2_smc.bin");
					} else {
						strcpy(fw_name, "amdgpu/polaris10_smc.bin");
					}
				} else if (type == CGS_UCODE_ID_SMU_SK) {
					strcpy(fw_name, "amdgpu/polaris10_smc_sk.bin");
				}
				break;
			case CHIP_POLARIS12:
				if (((adev->pdev->device == 0x6987) &&
				     ((adev->pdev->revision == 0xc0) ||
				      (adev->pdev->revision == 0xc3))) ||
				    ((adev->pdev->device == 0x6981) &&
				     ((adev->pdev->revision == 0x00) ||
				      (adev->pdev->revision == 0x01) ||
				      (adev->pdev->revision == 0x10)))) {
					info->is_kicker = true;
					strcpy(fw_name, "amdgpu/polaris12_k_smc.bin");
				} else {
					strcpy(fw_name, "amdgpu/polaris12_smc.bin");
				}
				break;
			case CHIP_VEGAM:
				strcpy(fw_name, "amdgpu/vegam_smc.bin");
				break;
			case CHIP_VEGA10:
				if ((adev->pdev->device == 0x687f) &&
					((adev->pdev->revision == 0xc0) ||
					(adev->pdev->revision == 0xc1) ||
					(adev->pdev->revision == 0xc3)))
					strcpy(fw_name, "amdgpu/vega10_acg_smc.bin");
				else
					strcpy(fw_name, "amdgpu/vega10_smc.bin");
				break;
			case CHIP_VEGA12:
				strcpy(fw_name, "amdgpu/vega12_smc.bin");
				break;
			case CHIP_VEGA20:
				strcpy(fw_name, "amdgpu/vega20_smc.bin");
				break;
			default:
				DRM_ERROR("SMC firmware not supported\n");
				return -EINVAL;
			}

			err = request_firmware(&adev->pm.fw, fw_name, adev->dev);
			if (err) {
				DRM_ERROR("Failed to request firmware\n");
				return err;
			}

			err = amdgpu_ucode_validate(adev->pm.fw);
			if (err) {
				DRM_ERROR("Failed to load firmware \"%s\"", fw_name);
				release_firmware(adev->pm.fw);
				adev->pm.fw = NULL;
				return err;
			}

			if (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) {
				ucode = &adev->firmware.ucode[AMDGPU_UCODE_ID_SMC];
				ucode->ucode_id = AMDGPU_UCODE_ID_SMC;
				ucode->fw = adev->pm.fw;
				header = (const struct common_firmware_header *)ucode->fw->data;
				adev->firmware.fw_size +=
					ALIGN(le32_to_cpu(header->ucode_size_bytes), PAGE_SIZE);
			}
		}

		hdr = (const struct smc_firmware_header_v1_0 *)	adev->pm.fw->data;
		amdgpu_ucode_print_smc_hdr(&hdr->header);
		adev->pm.fw_version = le32_to_cpu(hdr->header.ucode_version);
		ucode_size = le32_to_cpu(hdr->header.ucode_size_bytes);
		ucode_start_address = le32_to_cpu(hdr->ucode_start_addr);
		src = (const uint8_t *)(adev->pm.fw->data +
		       le32_to_cpu(hdr->header.ucode_array_offset_bytes));

		info->version = adev->pm.fw_version;
		info->image_size = ucode_size;
		info->ucode_start_address = ucode_start_address;
		info->kptr = (void *)src;
	}
	return 0;
}