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
struct TYPE_8__ {int /*<<< orphan*/  ucode_version; } ;
struct sdma_firmware_header_v1_0 {int /*<<< orphan*/  ucode_feature_version; TYPE_1__ header; } ;
struct common_firmware_header {int /*<<< orphan*/  ucode_size_bytes; } ;
struct amdgpu_firmware_info {int ucode_id; TYPE_5__* fw; } ;
struct TYPE_11__ {int num_instances; TYPE_3__* instance; } ;
struct TYPE_9__ {scalar_t__ load_type; int /*<<< orphan*/  fw_size; struct amdgpu_firmware_info* ucode; } ;
struct amdgpu_device {int asic_type; TYPE_4__ sdma; TYPE_2__ firmware; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  fw_name ;
struct TYPE_12__ {scalar_t__ data; } ;
struct TYPE_10__ {int feature_version; int burst_nop; TYPE_5__* fw; void* fw_version; } ;

/* Variables and functions */
 scalar_t__ ALIGN (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ AMDGPU_FW_LOAD_SMU ; 
 int AMDGPU_UCODE_ID_SDMA0 ; 
 int /*<<< orphan*/  BUG () ; 
#define  CHIP_TOPAZ 128 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int amdgpu_ucode_validate (TYPE_5__*) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,char*) ; 
 int /*<<< orphan*/  release_firmware (TYPE_5__*) ; 
 int request_firmware (TYPE_5__**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 

__attribute__((used)) static int sdma_v2_4_init_microcode(struct amdgpu_device *adev)
{
	const char *chip_name;
	char fw_name[30];
	int err = 0, i;
	struct amdgpu_firmware_info *info = NULL;
	const struct common_firmware_header *header = NULL;
	const struct sdma_firmware_header_v1_0 *hdr;

	DRM_DEBUG("\n");

	switch (adev->asic_type) {
	case CHIP_TOPAZ:
		chip_name = "topaz";
		break;
	default: BUG();
	}

	for (i = 0; i < adev->sdma.num_instances; i++) {
		if (i == 0)
			snprintf(fw_name, sizeof(fw_name), "amdgpu/%s_sdma.bin", chip_name);
		else
			snprintf(fw_name, sizeof(fw_name), "amdgpu/%s_sdma1.bin", chip_name);
		err = request_firmware(&adev->sdma.instance[i].fw, fw_name, adev->dev);
		if (err)
			goto out;
		err = amdgpu_ucode_validate(adev->sdma.instance[i].fw);
		if (err)
			goto out;
		hdr = (const struct sdma_firmware_header_v1_0 *)adev->sdma.instance[i].fw->data;
		adev->sdma.instance[i].fw_version = le32_to_cpu(hdr->header.ucode_version);
		adev->sdma.instance[i].feature_version = le32_to_cpu(hdr->ucode_feature_version);
		if (adev->sdma.instance[i].feature_version >= 20)
			adev->sdma.instance[i].burst_nop = true;

		if (adev->firmware.load_type == AMDGPU_FW_LOAD_SMU) {
			info = &adev->firmware.ucode[AMDGPU_UCODE_ID_SDMA0 + i];
			info->ucode_id = AMDGPU_UCODE_ID_SDMA0 + i;
			info->fw = adev->sdma.instance[i].fw;
			header = (const struct common_firmware_header *)info->fw->data;
			adev->firmware.fw_size +=
				ALIGN(le32_to_cpu(header->ucode_size_bytes), PAGE_SIZE);
		}
	}

out:
	if (err) {
		pr_err("sdma_v2_4: Failed to load firmware \"%s\"\n", fw_name);
		for (i = 0; i < adev->sdma.num_instances; i++) {
			release_firmware(adev->sdma.instance[i].fw);
			adev->sdma.instance[i].fw = NULL;
		}
	}
	return err;
}