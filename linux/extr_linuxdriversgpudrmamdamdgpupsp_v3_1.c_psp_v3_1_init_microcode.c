#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int /*<<< orphan*/  ucode_array_offset_bytes; int /*<<< orphan*/  ucode_size_bytes; int /*<<< orphan*/  ucode_version; } ;
struct psp_firmware_header_v1_0 {TYPE_1__ header; int /*<<< orphan*/  ucode_feature_version; int /*<<< orphan*/  sos_offset_bytes; int /*<<< orphan*/  sos_size_bytes; } ;
struct psp_context {struct amdgpu_device* adev; } ;
struct TYPE_7__ {int sos_fw_version; int sos_feature_version; int sos_bin_size; int sys_bin_size; int asd_fw_version; int asd_feature_version; int asd_ucode_size; TYPE_3__* asd_fw; TYPE_3__* sos_fw; int /*<<< orphan*/ * asd_start_addr; int /*<<< orphan*/ * sys_start_addr; int /*<<< orphan*/ * sos_start_addr; } ;
struct amdgpu_device {int asic_type; TYPE_2__ psp; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  fw_name ;
struct TYPE_8__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  CHIP_VEGA10 129 
#define  CHIP_VEGA12 128 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int amdgpu_ucode_validate (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (TYPE_3__*) ; 
 int request_firmware (TYPE_3__**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 

__attribute__((used)) static int psp_v3_1_init_microcode(struct psp_context *psp)
{
	struct amdgpu_device *adev = psp->adev;
	const char *chip_name;
	char fw_name[30];
	int err = 0;
	const struct psp_firmware_header_v1_0 *hdr;

	DRM_DEBUG("\n");

	switch (adev->asic_type) {
	case CHIP_VEGA10:
		chip_name = "vega10";
		break;
	case CHIP_VEGA12:
		chip_name = "vega12";
		break;
	default: BUG();
	}

	snprintf(fw_name, sizeof(fw_name), "amdgpu/%s_sos.bin", chip_name);
	err = request_firmware(&adev->psp.sos_fw, fw_name, adev->dev);
	if (err)
		goto out;

	err = amdgpu_ucode_validate(adev->psp.sos_fw);
	if (err)
		goto out;

	hdr = (const struct psp_firmware_header_v1_0 *)adev->psp.sos_fw->data;
	adev->psp.sos_fw_version = le32_to_cpu(hdr->header.ucode_version);
	adev->psp.sos_feature_version = le32_to_cpu(hdr->ucode_feature_version);
	adev->psp.sos_bin_size = le32_to_cpu(hdr->sos_size_bytes);
	adev->psp.sys_bin_size = le32_to_cpu(hdr->header.ucode_size_bytes) -
					le32_to_cpu(hdr->sos_size_bytes);
	adev->psp.sys_start_addr = (uint8_t *)hdr +
				le32_to_cpu(hdr->header.ucode_array_offset_bytes);
	adev->psp.sos_start_addr = (uint8_t *)adev->psp.sys_start_addr +
				le32_to_cpu(hdr->sos_offset_bytes);

	snprintf(fw_name, sizeof(fw_name), "amdgpu/%s_asd.bin", chip_name);
	err = request_firmware(&adev->psp.asd_fw, fw_name, adev->dev);
	if (err)
		goto out;

	err = amdgpu_ucode_validate(adev->psp.asd_fw);
	if (err)
		goto out;

	hdr = (const struct psp_firmware_header_v1_0 *)adev->psp.asd_fw->data;
	adev->psp.asd_fw_version = le32_to_cpu(hdr->header.ucode_version);
	adev->psp.asd_feature_version = le32_to_cpu(hdr->ucode_feature_version);
	adev->psp.asd_ucode_size = le32_to_cpu(hdr->header.ucode_size_bytes);
	adev->psp.asd_start_addr = (uint8_t *)hdr +
				le32_to_cpu(hdr->header.ucode_array_offset_bytes);

	return 0;
out:
	if (err) {
		dev_err(adev->dev,
			"psp v3.1: Failed to load firmware \"%s\"\n",
			fw_name);
		release_firmware(adev->psp.sos_fw);
		adev->psp.sos_fw = NULL;
		release_firmware(adev->psp.asd_fw);
		adev->psp.asd_fw = NULL;
	}

	return err;
}