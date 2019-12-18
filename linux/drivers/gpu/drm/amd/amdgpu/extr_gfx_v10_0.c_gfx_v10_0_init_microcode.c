#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wks ;
typedef  int uint16_t ;
struct TYPE_11__ {unsigned int ucode_version; int /*<<< orphan*/  header_version_minor; int /*<<< orphan*/  header_version_major; } ;
struct rlc_firmware_header_v2_0 {unsigned int ucode_feature_version; unsigned int save_and_restore_offset; unsigned int clear_state_descriptor_offset; unsigned int avail_scratch_ram_locations; unsigned int reg_restore_list_size; unsigned int reg_list_format_start; unsigned int reg_list_format_separate_start; unsigned int starting_offsets_start; unsigned int reg_list_format_size_bytes; unsigned int reg_list_size_bytes; unsigned int reg_list_format_array_offset_bytes; unsigned int reg_list_array_offset_bytes; TYPE_2__ header; } ;
struct TYPE_12__ {unsigned int ucode_version; } ;
struct gfx_firmware_header_v1_0 {unsigned int ucode_feature_version; unsigned int jt_size; TYPE_3__ header; } ;
struct common_firmware_header {unsigned int ucode_size_bytes; } ;
struct amdgpu_firmware_info {size_t ucode_id; TYPE_7__* fw; } ;
struct TYPE_13__ {int is_rlc_v2_1; int save_and_restore_offset; int clear_state_descriptor_offset; int avail_scratch_ram_locations; int reg_restore_list_size; int reg_list_format_start; int reg_list_format_separate_start; int starting_offsets_start; int reg_list_format_size_bytes; int reg_list_size_bytes; int* register_list_format; int* register_restore; int save_restore_list_cntl_size_bytes; int save_restore_list_gpm_size_bytes; int save_restore_list_srm_size_bytes; } ;
struct TYPE_15__ {int pfp_fw_version; int pfp_feature_version; int me_fw_version; int me_feature_version; int ce_fw_version; int ce_feature_version; int rlc_fw_version; int rlc_feature_version; int mec_fw_version; int mec_feature_version; int mec2_fw_version; int mec2_feature_version; TYPE_7__* mec2_fw; TYPE_7__* mec_fw; TYPE_7__* rlc_fw; TYPE_7__* ce_fw; TYPE_7__* me_fw; TYPE_7__* pfp_fw; TYPE_4__ rlc; } ;
struct TYPE_14__ {scalar_t__ load_type; int /*<<< orphan*/  fw_size; struct amdgpu_firmware_info* ucode; } ;
struct amdgpu_device {int asic_type; TYPE_6__ gfx; int /*<<< orphan*/  dev; TYPE_5__ firmware; TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  fw_name ;
struct TYPE_16__ {scalar_t__ data; } ;
struct TYPE_10__ {int device; int revision; } ;

/* Variables and functions */
 scalar_t__ ALIGN (int,int /*<<< orphan*/ ) ; 
 scalar_t__ AMDGPU_FW_LOAD_PSP ; 
 size_t AMDGPU_UCODE_ID_CP_CE ; 
 size_t AMDGPU_UCODE_ID_CP_ME ; 
 size_t AMDGPU_UCODE_ID_CP_MEC1 ; 
 size_t AMDGPU_UCODE_ID_CP_MEC1_JT ; 
 size_t AMDGPU_UCODE_ID_CP_MEC2 ; 
 size_t AMDGPU_UCODE_ID_CP_MEC2_JT ; 
 size_t AMDGPU_UCODE_ID_CP_PFP ; 
 size_t AMDGPU_UCODE_ID_RLC_G ; 
 size_t AMDGPU_UCODE_ID_RLC_RESTORE_LIST_CNTL ; 
 size_t AMDGPU_UCODE_ID_RLC_RESTORE_LIST_GPM_MEM ; 
 size_t AMDGPU_UCODE_ID_RLC_RESTORE_LIST_SRM_MEM ; 
 int /*<<< orphan*/  BUG () ; 
#define  CHIP_NAVI10 130 
#define  CHIP_NAVI12 129 
#define  CHIP_NAVI14 128 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int amdgpu_ucode_validate (TYPE_7__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  gfx_v10_0_check_fw_write_wait (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v10_0_check_gfxoff_flag (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v10_0_init_rlc_ext_microcode (struct amdgpu_device*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (unsigned int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_firmware (TYPE_7__*) ; 
 int request_firmware (TYPE_7__**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

__attribute__((used)) static int gfx_v10_0_init_microcode(struct amdgpu_device *adev)
{
	const char *chip_name;
	char fw_name[40];
	char wks[10];
	int err;
	struct amdgpu_firmware_info *info = NULL;
	const struct common_firmware_header *header = NULL;
	const struct gfx_firmware_header_v1_0 *cp_hdr;
	const struct rlc_firmware_header_v2_0 *rlc_hdr;
	unsigned int *tmp = NULL;
	unsigned int i = 0;
	uint16_t version_major;
	uint16_t version_minor;

	DRM_DEBUG("\n");

	memset(wks, 0, sizeof(wks));
	switch (adev->asic_type) {
	case CHIP_NAVI10:
		chip_name = "navi10";
		break;
	case CHIP_NAVI14:
		chip_name = "navi14";
		if (!(adev->pdev->device == 0x7340 &&
		      adev->pdev->revision != 0x00))
			snprintf(wks, sizeof(wks), "_wks");
		break;
	case CHIP_NAVI12:
		chip_name = "navi12";
		break;
	default:
		BUG();
	}

	snprintf(fw_name, sizeof(fw_name), "amdgpu/%s_pfp%s.bin", chip_name, wks);
	err = request_firmware(&adev->gfx.pfp_fw, fw_name, adev->dev);
	if (err)
		goto out;
	err = amdgpu_ucode_validate(adev->gfx.pfp_fw);
	if (err)
		goto out;
	cp_hdr = (const struct gfx_firmware_header_v1_0 *)adev->gfx.pfp_fw->data;
	adev->gfx.pfp_fw_version = le32_to_cpu(cp_hdr->header.ucode_version);
	adev->gfx.pfp_feature_version = le32_to_cpu(cp_hdr->ucode_feature_version);

	snprintf(fw_name, sizeof(fw_name), "amdgpu/%s_me%s.bin", chip_name, wks);
	err = request_firmware(&adev->gfx.me_fw, fw_name, adev->dev);
	if (err)
		goto out;
	err = amdgpu_ucode_validate(adev->gfx.me_fw);
	if (err)
		goto out;
	cp_hdr = (const struct gfx_firmware_header_v1_0 *)adev->gfx.me_fw->data;
	adev->gfx.me_fw_version = le32_to_cpu(cp_hdr->header.ucode_version);
	adev->gfx.me_feature_version = le32_to_cpu(cp_hdr->ucode_feature_version);

	snprintf(fw_name, sizeof(fw_name), "amdgpu/%s_ce%s.bin", chip_name, wks);
	err = request_firmware(&adev->gfx.ce_fw, fw_name, adev->dev);
	if (err)
		goto out;
	err = amdgpu_ucode_validate(adev->gfx.ce_fw);
	if (err)
		goto out;
	cp_hdr = (const struct gfx_firmware_header_v1_0 *)adev->gfx.ce_fw->data;
	adev->gfx.ce_fw_version = le32_to_cpu(cp_hdr->header.ucode_version);
	adev->gfx.ce_feature_version = le32_to_cpu(cp_hdr->ucode_feature_version);

	snprintf(fw_name, sizeof(fw_name), "amdgpu/%s_rlc.bin", chip_name);
	err = request_firmware(&adev->gfx.rlc_fw, fw_name, adev->dev);
	if (err)
		goto out;
	err = amdgpu_ucode_validate(adev->gfx.rlc_fw);
	rlc_hdr = (const struct rlc_firmware_header_v2_0 *)adev->gfx.rlc_fw->data;
	version_major = le16_to_cpu(rlc_hdr->header.header_version_major);
	version_minor = le16_to_cpu(rlc_hdr->header.header_version_minor);
	if (version_major == 2 && version_minor == 1)
		adev->gfx.rlc.is_rlc_v2_1 = true;

	adev->gfx.rlc_fw_version = le32_to_cpu(rlc_hdr->header.ucode_version);
	adev->gfx.rlc_feature_version = le32_to_cpu(rlc_hdr->ucode_feature_version);
	adev->gfx.rlc.save_and_restore_offset =
			le32_to_cpu(rlc_hdr->save_and_restore_offset);
	adev->gfx.rlc.clear_state_descriptor_offset =
			le32_to_cpu(rlc_hdr->clear_state_descriptor_offset);
	adev->gfx.rlc.avail_scratch_ram_locations =
			le32_to_cpu(rlc_hdr->avail_scratch_ram_locations);
	adev->gfx.rlc.reg_restore_list_size =
			le32_to_cpu(rlc_hdr->reg_restore_list_size);
	adev->gfx.rlc.reg_list_format_start =
			le32_to_cpu(rlc_hdr->reg_list_format_start);
	adev->gfx.rlc.reg_list_format_separate_start =
			le32_to_cpu(rlc_hdr->reg_list_format_separate_start);
	adev->gfx.rlc.starting_offsets_start =
			le32_to_cpu(rlc_hdr->starting_offsets_start);
	adev->gfx.rlc.reg_list_format_size_bytes =
			le32_to_cpu(rlc_hdr->reg_list_format_size_bytes);
	adev->gfx.rlc.reg_list_size_bytes =
			le32_to_cpu(rlc_hdr->reg_list_size_bytes);
	adev->gfx.rlc.register_list_format =
			kmalloc(adev->gfx.rlc.reg_list_format_size_bytes +
				adev->gfx.rlc.reg_list_size_bytes, GFP_KERNEL);
	if (!adev->gfx.rlc.register_list_format) {
		err = -ENOMEM;
		goto out;
	}

	tmp = (unsigned int *)((uintptr_t)rlc_hdr +
			le32_to_cpu(rlc_hdr->reg_list_format_array_offset_bytes));
	for (i = 0 ; i < (rlc_hdr->reg_list_format_size_bytes >> 2); i++)
		adev->gfx.rlc.register_list_format[i] =	le32_to_cpu(tmp[i]);

	adev->gfx.rlc.register_restore = adev->gfx.rlc.register_list_format + i;

	tmp = (unsigned int *)((uintptr_t)rlc_hdr +
			le32_to_cpu(rlc_hdr->reg_list_array_offset_bytes));
	for (i = 0 ; i < (rlc_hdr->reg_list_size_bytes >> 2); i++)
		adev->gfx.rlc.register_restore[i] = le32_to_cpu(tmp[i]);

	if (adev->gfx.rlc.is_rlc_v2_1)
		gfx_v10_0_init_rlc_ext_microcode(adev);

	snprintf(fw_name, sizeof(fw_name), "amdgpu/%s_mec%s.bin", chip_name, wks);
	err = request_firmware(&adev->gfx.mec_fw, fw_name, adev->dev);
	if (err)
		goto out;
	err = amdgpu_ucode_validate(adev->gfx.mec_fw);
	if (err)
		goto out;
	cp_hdr = (const struct gfx_firmware_header_v1_0 *)adev->gfx.mec_fw->data;
	adev->gfx.mec_fw_version = le32_to_cpu(cp_hdr->header.ucode_version);
	adev->gfx.mec_feature_version = le32_to_cpu(cp_hdr->ucode_feature_version);

	snprintf(fw_name, sizeof(fw_name), "amdgpu/%s_mec2%s.bin", chip_name, wks);
	err = request_firmware(&adev->gfx.mec2_fw, fw_name, adev->dev);
	if (!err) {
		err = amdgpu_ucode_validate(adev->gfx.mec2_fw);
		if (err)
			goto out;
		cp_hdr = (const struct gfx_firmware_header_v1_0 *)
		adev->gfx.mec2_fw->data;
		adev->gfx.mec2_fw_version =
		le32_to_cpu(cp_hdr->header.ucode_version);
		adev->gfx.mec2_feature_version =
		le32_to_cpu(cp_hdr->ucode_feature_version);
	} else {
		err = 0;
		adev->gfx.mec2_fw = NULL;
	}

	if (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) {
		info = &adev->firmware.ucode[AMDGPU_UCODE_ID_CP_PFP];
		info->ucode_id = AMDGPU_UCODE_ID_CP_PFP;
		info->fw = adev->gfx.pfp_fw;
		header = (const struct common_firmware_header *)info->fw->data;
		adev->firmware.fw_size +=
			ALIGN(le32_to_cpu(header->ucode_size_bytes), PAGE_SIZE);

		info = &adev->firmware.ucode[AMDGPU_UCODE_ID_CP_ME];
		info->ucode_id = AMDGPU_UCODE_ID_CP_ME;
		info->fw = adev->gfx.me_fw;
		header = (const struct common_firmware_header *)info->fw->data;
		adev->firmware.fw_size +=
			ALIGN(le32_to_cpu(header->ucode_size_bytes), PAGE_SIZE);

		info = &adev->firmware.ucode[AMDGPU_UCODE_ID_CP_CE];
		info->ucode_id = AMDGPU_UCODE_ID_CP_CE;
		info->fw = adev->gfx.ce_fw;
		header = (const struct common_firmware_header *)info->fw->data;
		adev->firmware.fw_size +=
			ALIGN(le32_to_cpu(header->ucode_size_bytes), PAGE_SIZE);

		info = &adev->firmware.ucode[AMDGPU_UCODE_ID_RLC_G];
		info->ucode_id = AMDGPU_UCODE_ID_RLC_G;
		info->fw = adev->gfx.rlc_fw;
		header = (const struct common_firmware_header *)info->fw->data;
		adev->firmware.fw_size +=
			ALIGN(le32_to_cpu(header->ucode_size_bytes), PAGE_SIZE);

		if (adev->gfx.rlc.is_rlc_v2_1 &&
		    adev->gfx.rlc.save_restore_list_cntl_size_bytes &&
		    adev->gfx.rlc.save_restore_list_gpm_size_bytes &&
		    adev->gfx.rlc.save_restore_list_srm_size_bytes) {
			info = &adev->firmware.ucode[AMDGPU_UCODE_ID_RLC_RESTORE_LIST_CNTL];
			info->ucode_id = AMDGPU_UCODE_ID_RLC_RESTORE_LIST_CNTL;
			info->fw = adev->gfx.rlc_fw;
			adev->firmware.fw_size +=
				ALIGN(adev->gfx.rlc.save_restore_list_cntl_size_bytes, PAGE_SIZE);

			info = &adev->firmware.ucode[AMDGPU_UCODE_ID_RLC_RESTORE_LIST_GPM_MEM];
			info->ucode_id = AMDGPU_UCODE_ID_RLC_RESTORE_LIST_GPM_MEM;
			info->fw = adev->gfx.rlc_fw;
			adev->firmware.fw_size +=
				ALIGN(adev->gfx.rlc.save_restore_list_gpm_size_bytes, PAGE_SIZE);

			info = &adev->firmware.ucode[AMDGPU_UCODE_ID_RLC_RESTORE_LIST_SRM_MEM];
			info->ucode_id = AMDGPU_UCODE_ID_RLC_RESTORE_LIST_SRM_MEM;
			info->fw = adev->gfx.rlc_fw;
			adev->firmware.fw_size +=
				ALIGN(adev->gfx.rlc.save_restore_list_srm_size_bytes, PAGE_SIZE);
		}

		info = &adev->firmware.ucode[AMDGPU_UCODE_ID_CP_MEC1];
		info->ucode_id = AMDGPU_UCODE_ID_CP_MEC1;
		info->fw = adev->gfx.mec_fw;
		header = (const struct common_firmware_header *)info->fw->data;
		cp_hdr = (const struct gfx_firmware_header_v1_0 *)info->fw->data;
		adev->firmware.fw_size +=
			ALIGN(le32_to_cpu(header->ucode_size_bytes) -
			      le32_to_cpu(cp_hdr->jt_size) * 4, PAGE_SIZE);

		info = &adev->firmware.ucode[AMDGPU_UCODE_ID_CP_MEC1_JT];
		info->ucode_id = AMDGPU_UCODE_ID_CP_MEC1_JT;
		info->fw = adev->gfx.mec_fw;
		adev->firmware.fw_size +=
			ALIGN(le32_to_cpu(cp_hdr->jt_size) * 4, PAGE_SIZE);

		if (adev->gfx.mec2_fw) {
			info = &adev->firmware.ucode[AMDGPU_UCODE_ID_CP_MEC2];
			info->ucode_id = AMDGPU_UCODE_ID_CP_MEC2;
			info->fw = adev->gfx.mec2_fw;
			header = (const struct common_firmware_header *)info->fw->data;
			cp_hdr = (const struct gfx_firmware_header_v1_0 *)info->fw->data;
			adev->firmware.fw_size +=
				ALIGN(le32_to_cpu(header->ucode_size_bytes) -
				      le32_to_cpu(cp_hdr->jt_size) * 4,
				      PAGE_SIZE);
			info = &adev->firmware.ucode[AMDGPU_UCODE_ID_CP_MEC2_JT];
			info->ucode_id = AMDGPU_UCODE_ID_CP_MEC2_JT;
			info->fw = adev->gfx.mec2_fw;
			adev->firmware.fw_size +=
				ALIGN(le32_to_cpu(cp_hdr->jt_size) * 4,
				      PAGE_SIZE);
		}
	}

	gfx_v10_0_check_fw_write_wait(adev);
out:
	if (err) {
		dev_err(adev->dev,
			"gfx10: Failed to load firmware \"%s\"\n",
			fw_name);
		release_firmware(adev->gfx.pfp_fw);
		adev->gfx.pfp_fw = NULL;
		release_firmware(adev->gfx.me_fw);
		adev->gfx.me_fw = NULL;
		release_firmware(adev->gfx.ce_fw);
		adev->gfx.ce_fw = NULL;
		release_firmware(adev->gfx.rlc_fw);
		adev->gfx.rlc_fw = NULL;
		release_firmware(adev->gfx.mec_fw);
		adev->gfx.mec_fw = NULL;
		release_firmware(adev->gfx.mec2_fw);
		adev->gfx.mec2_fw = NULL;
	}

	gfx_v10_0_check_gfxoff_flag(adev);

	return err;
}