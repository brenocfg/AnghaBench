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
struct TYPE_11__ {int ucode_version; } ;
struct rlc_firmware_header_v2_0 {int ucode_feature_version; int save_and_restore_offset; int clear_state_descriptor_offset; int avail_scratch_ram_locations; int reg_restore_list_size; int reg_list_format_start; int reg_list_format_separate_start; int starting_offsets_start; int reg_list_format_size_bytes; int reg_list_size_bytes; int reg_list_format_array_offset_bytes; int reg_list_array_offset_bytes; TYPE_2__ header; } ;
struct TYPE_13__ {int ucode_version; } ;
struct gfx_firmware_header_v1_0 {int ucode_feature_version; int jt_size; TYPE_4__ header; } ;
struct common_firmware_header {int ucode_size_bytes; } ;
struct amdgpu_firmware_info {size_t ucode_id; TYPE_7__* fw; } ;
struct TYPE_12__ {int save_and_restore_offset; int clear_state_descriptor_offset; int avail_scratch_ram_locations; int reg_restore_list_size; int reg_list_format_start; int reg_list_format_separate_start; int starting_offsets_start; int reg_list_format_size_bytes; int reg_list_size_bytes; int* register_list_format; int* register_restore; } ;
struct TYPE_15__ {int pfp_fw_version; int pfp_feature_version; int me_fw_version; int me_feature_version; int ce_fw_version; int ce_feature_version; int rlc_fw_version; int rlc_feature_version; int mec_fw_version; int mec_feature_version; int mec2_fw_version; int mec2_feature_version; TYPE_7__* mec2_fw; TYPE_7__* mec_fw; TYPE_7__* rlc_fw; TYPE_7__* ce_fw; TYPE_7__* me_fw; TYPE_7__* pfp_fw; TYPE_3__ rlc; } ;
struct TYPE_14__ {int /*<<< orphan*/  fw_size; struct amdgpu_firmware_info* ucode; } ;
struct TYPE_10__ {int chained_ib_support; } ;
struct amdgpu_device {int asic_type; TYPE_6__ gfx; int /*<<< orphan*/  dev; TYPE_5__ firmware; TYPE_1__ virt; } ;
typedef  int /*<<< orphan*/  fw_name ;
struct TYPE_16__ {scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ ALIGN (int,int) ; 
 size_t AMDGPU_UCODE_ID_CP_CE ; 
 size_t AMDGPU_UCODE_ID_CP_ME ; 
 size_t AMDGPU_UCODE_ID_CP_MEC1 ; 
 size_t AMDGPU_UCODE_ID_CP_MEC2 ; 
 size_t AMDGPU_UCODE_ID_CP_PFP ; 
 size_t AMDGPU_UCODE_ID_RLC_G ; 
 size_t AMDGPU_UCODE_ID_STORAGE ; 
 int /*<<< orphan*/  BUG () ; 
#define  CHIP_CARRIZO 136 
#define  CHIP_FIJI 135 
#define  CHIP_POLARIS10 134 
#define  CHIP_POLARIS11 133 
#define  CHIP_POLARIS12 132 
#define  CHIP_STONEY 131 
#define  CHIP_TONGA 130 
#define  CHIP_TOPAZ 129 
#define  CHIP_VEGAM 128 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int amdgpu_ucode_validate (TYPE_7__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int) ; 
 int /*<<< orphan*/  release_firmware (TYPE_7__*) ; 
 int request_firmware (TYPE_7__**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 

__attribute__((used)) static int gfx_v8_0_init_microcode(struct amdgpu_device *adev)
{
	const char *chip_name;
	char fw_name[30];
	int err;
	struct amdgpu_firmware_info *info = NULL;
	const struct common_firmware_header *header = NULL;
	const struct gfx_firmware_header_v1_0 *cp_hdr;
	const struct rlc_firmware_header_v2_0 *rlc_hdr;
	unsigned int *tmp = NULL, i;

	DRM_DEBUG("\n");

	switch (adev->asic_type) {
	case CHIP_TOPAZ:
		chip_name = "topaz";
		break;
	case CHIP_TONGA:
		chip_name = "tonga";
		break;
	case CHIP_CARRIZO:
		chip_name = "carrizo";
		break;
	case CHIP_FIJI:
		chip_name = "fiji";
		break;
	case CHIP_STONEY:
		chip_name = "stoney";
		break;
	case CHIP_POLARIS10:
		chip_name = "polaris10";
		break;
	case CHIP_POLARIS11:
		chip_name = "polaris11";
		break;
	case CHIP_POLARIS12:
		chip_name = "polaris12";
		break;
	case CHIP_VEGAM:
		chip_name = "vegam";
		break;
	default:
		BUG();
	}

	if (adev->asic_type >= CHIP_POLARIS10 && adev->asic_type <= CHIP_POLARIS12) {
		snprintf(fw_name, sizeof(fw_name), "amdgpu/%s_pfp_2.bin", chip_name);
		err = request_firmware(&adev->gfx.pfp_fw, fw_name, adev->dev);
		if (err == -ENOENT) {
			snprintf(fw_name, sizeof(fw_name), "amdgpu/%s_pfp.bin", chip_name);
			err = request_firmware(&adev->gfx.pfp_fw, fw_name, adev->dev);
		}
	} else {
		snprintf(fw_name, sizeof(fw_name), "amdgpu/%s_pfp.bin", chip_name);
		err = request_firmware(&adev->gfx.pfp_fw, fw_name, adev->dev);
	}
	if (err)
		goto out;
	err = amdgpu_ucode_validate(adev->gfx.pfp_fw);
	if (err)
		goto out;
	cp_hdr = (const struct gfx_firmware_header_v1_0 *)adev->gfx.pfp_fw->data;
	adev->gfx.pfp_fw_version = le32_to_cpu(cp_hdr->header.ucode_version);
	adev->gfx.pfp_feature_version = le32_to_cpu(cp_hdr->ucode_feature_version);

	if (adev->asic_type >= CHIP_POLARIS10 && adev->asic_type <= CHIP_POLARIS12) {
		snprintf(fw_name, sizeof(fw_name), "amdgpu/%s_me_2.bin", chip_name);
		err = request_firmware(&adev->gfx.me_fw, fw_name, adev->dev);
		if (err == -ENOENT) {
			snprintf(fw_name, sizeof(fw_name), "amdgpu/%s_me.bin", chip_name);
			err = request_firmware(&adev->gfx.me_fw, fw_name, adev->dev);
		}
	} else {
		snprintf(fw_name, sizeof(fw_name), "amdgpu/%s_me.bin", chip_name);
		err = request_firmware(&adev->gfx.me_fw, fw_name, adev->dev);
	}
	if (err)
		goto out;
	err = amdgpu_ucode_validate(adev->gfx.me_fw);
	if (err)
		goto out;
	cp_hdr = (const struct gfx_firmware_header_v1_0 *)adev->gfx.me_fw->data;
	adev->gfx.me_fw_version = le32_to_cpu(cp_hdr->header.ucode_version);

	adev->gfx.me_feature_version = le32_to_cpu(cp_hdr->ucode_feature_version);

	if (adev->asic_type >= CHIP_POLARIS10 && adev->asic_type <= CHIP_POLARIS12) {
		snprintf(fw_name, sizeof(fw_name), "amdgpu/%s_ce_2.bin", chip_name);
		err = request_firmware(&adev->gfx.ce_fw, fw_name, adev->dev);
		if (err == -ENOENT) {
			snprintf(fw_name, sizeof(fw_name), "amdgpu/%s_ce.bin", chip_name);
			err = request_firmware(&adev->gfx.ce_fw, fw_name, adev->dev);
		}
	} else {
		snprintf(fw_name, sizeof(fw_name), "amdgpu/%s_ce.bin", chip_name);
		err = request_firmware(&adev->gfx.ce_fw, fw_name, adev->dev);
	}
	if (err)
		goto out;
	err = amdgpu_ucode_validate(adev->gfx.ce_fw);
	if (err)
		goto out;
	cp_hdr = (const struct gfx_firmware_header_v1_0 *)adev->gfx.ce_fw->data;
	adev->gfx.ce_fw_version = le32_to_cpu(cp_hdr->header.ucode_version);
	adev->gfx.ce_feature_version = le32_to_cpu(cp_hdr->ucode_feature_version);

	/*
	 * Support for MCBP/Virtualization in combination with chained IBs is
	 * formal released on feature version #46
	 */
	if (adev->gfx.ce_feature_version >= 46 &&
	    adev->gfx.pfp_feature_version >= 46) {
		adev->virt.chained_ib_support = true;
		DRM_INFO("Chained IB support enabled!\n");
	} else
		adev->virt.chained_ib_support = false;

	snprintf(fw_name, sizeof(fw_name), "amdgpu/%s_rlc.bin", chip_name);
	err = request_firmware(&adev->gfx.rlc_fw, fw_name, adev->dev);
	if (err)
		goto out;
	err = amdgpu_ucode_validate(adev->gfx.rlc_fw);
	rlc_hdr = (const struct rlc_firmware_header_v2_0 *)adev->gfx.rlc_fw->data;
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
	for (i = 0 ; i < (adev->gfx.rlc.reg_list_format_size_bytes >> 2); i++)
		adev->gfx.rlc.register_list_format[i] =	le32_to_cpu(tmp[i]);

	adev->gfx.rlc.register_restore = adev->gfx.rlc.register_list_format + i;

	tmp = (unsigned int *)((uintptr_t)rlc_hdr +
			le32_to_cpu(rlc_hdr->reg_list_array_offset_bytes));
	for (i = 0 ; i < (adev->gfx.rlc.reg_list_size_bytes >> 2); i++)
		adev->gfx.rlc.register_restore[i] = le32_to_cpu(tmp[i]);

	if (adev->asic_type >= CHIP_POLARIS10 && adev->asic_type <= CHIP_POLARIS12) {
		snprintf(fw_name, sizeof(fw_name), "amdgpu/%s_mec_2.bin", chip_name);
		err = request_firmware(&adev->gfx.mec_fw, fw_name, adev->dev);
		if (err == -ENOENT) {
			snprintf(fw_name, sizeof(fw_name), "amdgpu/%s_mec.bin", chip_name);
			err = request_firmware(&adev->gfx.mec_fw, fw_name, adev->dev);
		}
	} else {
		snprintf(fw_name, sizeof(fw_name), "amdgpu/%s_mec.bin", chip_name);
		err = request_firmware(&adev->gfx.mec_fw, fw_name, adev->dev);
	}
	if (err)
		goto out;
	err = amdgpu_ucode_validate(adev->gfx.mec_fw);
	if (err)
		goto out;
	cp_hdr = (const struct gfx_firmware_header_v1_0 *)adev->gfx.mec_fw->data;
	adev->gfx.mec_fw_version = le32_to_cpu(cp_hdr->header.ucode_version);
	adev->gfx.mec_feature_version = le32_to_cpu(cp_hdr->ucode_feature_version);

	if ((adev->asic_type != CHIP_STONEY) &&
	    (adev->asic_type != CHIP_TOPAZ)) {
		if (adev->asic_type >= CHIP_POLARIS10 && adev->asic_type <= CHIP_POLARIS12) {
			snprintf(fw_name, sizeof(fw_name), "amdgpu/%s_mec2_2.bin", chip_name);
			err = request_firmware(&adev->gfx.mec2_fw, fw_name, adev->dev);
			if (err == -ENOENT) {
				snprintf(fw_name, sizeof(fw_name), "amdgpu/%s_mec2.bin", chip_name);
				err = request_firmware(&adev->gfx.mec2_fw, fw_name, adev->dev);
			}
		} else {
			snprintf(fw_name, sizeof(fw_name), "amdgpu/%s_mec2.bin", chip_name);
			err = request_firmware(&adev->gfx.mec2_fw, fw_name, adev->dev);
		}
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
	}

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

	info = &adev->firmware.ucode[AMDGPU_UCODE_ID_CP_MEC1];
	info->ucode_id = AMDGPU_UCODE_ID_CP_MEC1;
	info->fw = adev->gfx.mec_fw;
	header = (const struct common_firmware_header *)info->fw->data;
	adev->firmware.fw_size +=
		ALIGN(le32_to_cpu(header->ucode_size_bytes), PAGE_SIZE);

	/* we need account JT in */
	cp_hdr = (const struct gfx_firmware_header_v1_0 *)adev->gfx.mec_fw->data;
	adev->firmware.fw_size +=
		ALIGN(le32_to_cpu(cp_hdr->jt_size) << 2, PAGE_SIZE);

	if (amdgpu_sriov_vf(adev)) {
		info = &adev->firmware.ucode[AMDGPU_UCODE_ID_STORAGE];
		info->ucode_id = AMDGPU_UCODE_ID_STORAGE;
		info->fw = adev->gfx.mec_fw;
		adev->firmware.fw_size +=
			ALIGN(le32_to_cpu(64 * PAGE_SIZE), PAGE_SIZE);
	}

	if (adev->gfx.mec2_fw) {
		info = &adev->firmware.ucode[AMDGPU_UCODE_ID_CP_MEC2];
		info->ucode_id = AMDGPU_UCODE_ID_CP_MEC2;
		info->fw = adev->gfx.mec2_fw;
		header = (const struct common_firmware_header *)info->fw->data;
		adev->firmware.fw_size +=
			ALIGN(le32_to_cpu(header->ucode_size_bytes), PAGE_SIZE);
	}

out:
	if (err) {
		dev_err(adev->dev,
			"gfx8: Failed to load firmware \"%s\"\n",
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
	return err;
}