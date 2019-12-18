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
typedef  int /*<<< orphan*/  const u8 ;
struct image_hdr {int dummy; } ;
struct flash_section_info {int dummy; } ;
struct flash_file_hdr_g3 {int dummy; } ;
struct flash_file_hdr_g2 {int dummy; } ;
struct flash_comp {scalar_t__ member_1; scalar_t__ const img_type; scalar_t__ const optype; int offset; int size; int /*<<< orphan*/  const member_3; int /*<<< orphan*/  const member_2; int /*<<< orphan*/  member_0; } ;
struct firmware {int size; int /*<<< orphan*/  const* data; } ;
struct device {int dummy; } ;
struct be_dma_mem {int dummy; } ;
struct be_adapter {int /*<<< orphan*/  fw_ver; TYPE_1__* pdev; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct flash_comp const*) ; 
#define  BE2_BIOS_COMP_MAX_SIZE 173 
#define  BE2_COMP_MAX_SIZE 172 
#define  BE2_FCOE_BACKUP_IMAGE_START 171 
#define  BE2_FCOE_BIOS_START 170 
#define  BE2_FCOE_PRIMARY_IMAGE_START 169 
#define  BE2_ISCSI_BACKUP_IMAGE_START 168 
#define  BE2_ISCSI_BIOS_START 167 
#define  BE2_ISCSI_PRIMARY_IMAGE_START 166 
#define  BE2_PXE_BIOS_START 165 
#define  BE2_REDBOOT_COMP_MAX_SIZE 164 
#define  BE2_REDBOOT_START 163 
#define  BE3_BIOS_COMP_MAX_SIZE 162 
#define  BE3_COMP_MAX_SIZE 161 
#define  BE3_FCOE_BACKUP_IMAGE_START 160 
#define  BE3_FCOE_BIOS_START 159 
#define  BE3_FCOE_PRIMARY_IMAGE_START 158 
#define  BE3_ISCSI_BACKUP_IMAGE_START 157 
#define  BE3_ISCSI_BIOS_START 156 
#define  BE3_ISCSI_PRIMARY_IMAGE_START 155 
#define  BE3_NCSI_COMP_MAX_SIZE 154 
#define  BE3_NCSI_START 153 
#define  BE3_PHY_FW_COMP_MAX_SIZE 152 
#define  BE3_PHY_FW_START 151 
#define  BE3_PXE_BIOS_START 150 
#define  BE3_REDBOOT_COMP_MAX_SIZE 149 
#define  BE3_REDBOOT_START 148 
 scalar_t__ BE3_chip (struct be_adapter*) ; 
#define  IMAGE_BOOT_CODE 147 
#define  IMAGE_FIRMWARE_BACKUP_FCOE 146 
#define  IMAGE_FIRMWARE_BACKUP_ISCSI 145 
#define  IMAGE_FIRMWARE_FCOE 144 
#define  IMAGE_FIRMWARE_ISCSI 143 
#define  IMAGE_FIRMWARE_PHY 142 
#define  IMAGE_NCSI 141 
#define  IMAGE_OPTION_ROM_FCOE 140 
#define  IMAGE_OPTION_ROM_ISCSI 139 
#define  IMAGE_OPTION_ROM_PXE 138 
 int /*<<< orphan*/  NCSI_UPDATE_LOG ; 
#define  OPTYPE_BIOS 137 
#define  OPTYPE_FCOE_BIOS 136 
#define  OPTYPE_FCOE_FW_ACTIVE 135 
#define  OPTYPE_FCOE_FW_BACKUP 134 
#define  OPTYPE_ISCSI_ACTIVE 133 
#define  OPTYPE_ISCSI_BACKUP 132 
#define  OPTYPE_NCSI_FW 131 
#define  OPTYPE_PHY_FW 130 
#define  OPTYPE_PXE_BIOS 129 
#define  OPTYPE_REDBOOT 128 
 int be_check_flash_crc (struct be_adapter*,int /*<<< orphan*/  const*,int,int,int,scalar_t__ const,int*) ; 
 int be_flash (struct be_adapter*,int /*<<< orphan*/  const*,struct be_dma_mem*,scalar_t__ const,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be_fw_ncsi_supported (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct flash_section_info* get_fsec_info (struct be_adapter*,int,struct firmware const*) ; 
 int /*<<< orphan*/  is_comp_in_ufi (struct be_adapter*,struct flash_section_info*,scalar_t__ const) ; 
 int /*<<< orphan*/  phy_flashing_required (struct be_adapter*) ; 

__attribute__((used)) static int be_flash_BEx(struct be_adapter *adapter,
			const struct firmware *fw,
			struct be_dma_mem *flash_cmd, int num_of_images)
{
	int img_hdrs_size = (num_of_images * sizeof(struct image_hdr));
	struct device *dev = &adapter->pdev->dev;
	struct flash_section_info *fsec = NULL;
	int status, i, filehdr_size, num_comp;
	const struct flash_comp *pflashcomp;
	bool crc_match;
	const u8 *p;

	static const struct flash_comp gen3_flash_types[] = {
		{ BE3_ISCSI_PRIMARY_IMAGE_START, OPTYPE_ISCSI_ACTIVE,
			BE3_COMP_MAX_SIZE, IMAGE_FIRMWARE_ISCSI},
		{ BE3_REDBOOT_START, OPTYPE_REDBOOT,
			BE3_REDBOOT_COMP_MAX_SIZE, IMAGE_BOOT_CODE},
		{ BE3_ISCSI_BIOS_START, OPTYPE_BIOS,
			BE3_BIOS_COMP_MAX_SIZE, IMAGE_OPTION_ROM_ISCSI},
		{ BE3_PXE_BIOS_START, OPTYPE_PXE_BIOS,
			BE3_BIOS_COMP_MAX_SIZE, IMAGE_OPTION_ROM_PXE},
		{ BE3_FCOE_BIOS_START, OPTYPE_FCOE_BIOS,
			BE3_BIOS_COMP_MAX_SIZE, IMAGE_OPTION_ROM_FCOE},
		{ BE3_ISCSI_BACKUP_IMAGE_START, OPTYPE_ISCSI_BACKUP,
			BE3_COMP_MAX_SIZE, IMAGE_FIRMWARE_BACKUP_ISCSI},
		{ BE3_FCOE_PRIMARY_IMAGE_START, OPTYPE_FCOE_FW_ACTIVE,
			BE3_COMP_MAX_SIZE, IMAGE_FIRMWARE_FCOE},
		{ BE3_FCOE_BACKUP_IMAGE_START, OPTYPE_FCOE_FW_BACKUP,
			BE3_COMP_MAX_SIZE, IMAGE_FIRMWARE_BACKUP_FCOE},
		{ BE3_NCSI_START, OPTYPE_NCSI_FW,
			BE3_NCSI_COMP_MAX_SIZE, IMAGE_NCSI},
		{ BE3_PHY_FW_START, OPTYPE_PHY_FW,
			BE3_PHY_FW_COMP_MAX_SIZE, IMAGE_FIRMWARE_PHY}
	};

	static const struct flash_comp gen2_flash_types[] = {
		{ BE2_ISCSI_PRIMARY_IMAGE_START, OPTYPE_ISCSI_ACTIVE,
			BE2_COMP_MAX_SIZE, IMAGE_FIRMWARE_ISCSI},
		{ BE2_REDBOOT_START, OPTYPE_REDBOOT,
			BE2_REDBOOT_COMP_MAX_SIZE, IMAGE_BOOT_CODE},
		{ BE2_ISCSI_BIOS_START, OPTYPE_BIOS,
			BE2_BIOS_COMP_MAX_SIZE, IMAGE_OPTION_ROM_ISCSI},
		{ BE2_PXE_BIOS_START, OPTYPE_PXE_BIOS,
			BE2_BIOS_COMP_MAX_SIZE, IMAGE_OPTION_ROM_PXE},
		{ BE2_FCOE_BIOS_START, OPTYPE_FCOE_BIOS,
			BE2_BIOS_COMP_MAX_SIZE, IMAGE_OPTION_ROM_FCOE},
		{ BE2_ISCSI_BACKUP_IMAGE_START, OPTYPE_ISCSI_BACKUP,
			BE2_COMP_MAX_SIZE, IMAGE_FIRMWARE_BACKUP_ISCSI},
		{ BE2_FCOE_PRIMARY_IMAGE_START, OPTYPE_FCOE_FW_ACTIVE,
			BE2_COMP_MAX_SIZE, IMAGE_FIRMWARE_FCOE},
		{ BE2_FCOE_BACKUP_IMAGE_START, OPTYPE_FCOE_FW_BACKUP,
			 BE2_COMP_MAX_SIZE, IMAGE_FIRMWARE_BACKUP_FCOE}
	};

	if (BE3_chip(adapter)) {
		pflashcomp = gen3_flash_types;
		filehdr_size = sizeof(struct flash_file_hdr_g3);
		num_comp = ARRAY_SIZE(gen3_flash_types);
	} else {
		pflashcomp = gen2_flash_types;
		filehdr_size = sizeof(struct flash_file_hdr_g2);
		num_comp = ARRAY_SIZE(gen2_flash_types);
		img_hdrs_size = 0;
	}

	/* Get flash section info*/
	fsec = get_fsec_info(adapter, filehdr_size + img_hdrs_size, fw);
	if (!fsec) {
		dev_err(dev, "Invalid Cookie. FW image may be corrupted\n");
		return -1;
	}
	for (i = 0; i < num_comp; i++) {
		if (!is_comp_in_ufi(adapter, fsec, pflashcomp[i].img_type))
			continue;

		if ((pflashcomp[i].optype == OPTYPE_NCSI_FW) &&
		    !be_fw_ncsi_supported(adapter->fw_ver)) {
			dev_info(dev, NCSI_UPDATE_LOG, adapter->fw_ver);
			continue;
		}

		if (pflashcomp[i].optype == OPTYPE_PHY_FW  &&
		    !phy_flashing_required(adapter))
			continue;

		if (pflashcomp[i].optype == OPTYPE_REDBOOT) {
			status = be_check_flash_crc(adapter, fw->data,
						    pflashcomp[i].offset,
						    pflashcomp[i].size,
						    filehdr_size +
						    img_hdrs_size,
						    OPTYPE_REDBOOT, &crc_match);
			if (status) {
				dev_err(dev,
					"Could not get CRC for 0x%x region\n",
					pflashcomp[i].optype);
				continue;
			}

			if (crc_match)
				continue;
		}

		p = fw->data + filehdr_size + pflashcomp[i].offset +
			img_hdrs_size;
		if (p + pflashcomp[i].size > fw->data + fw->size)
			return -1;

		status = be_flash(adapter, p, flash_cmd, pflashcomp[i].optype,
				  pflashcomp[i].size, 0);
		if (status) {
			dev_err(dev, "Flashing section type 0x%x failed\n",
				pflashcomp[i].img_type);
			return status;
		}
	}
	return 0;
}