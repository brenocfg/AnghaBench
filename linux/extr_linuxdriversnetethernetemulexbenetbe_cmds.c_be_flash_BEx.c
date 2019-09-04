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
struct flash_comp {scalar_t__ member_1; scalar_t__ img_type; scalar_t__ optype; int offset; int size; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_0; } ;
struct firmware {int size; int /*<<< orphan*/  const* data; } ;
struct device {int dummy; } ;
struct be_dma_mem {int dummy; } ;
struct be_adapter {int /*<<< orphan*/  fw_ver; TYPE_1__* pdev; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct flash_comp*) ; 
 int /*<<< orphan*/  BE2_BIOS_COMP_MAX_SIZE ; 
 int /*<<< orphan*/  BE2_COMP_MAX_SIZE ; 
 int /*<<< orphan*/  BE2_FCOE_BACKUP_IMAGE_START ; 
 int /*<<< orphan*/  BE2_FCOE_BIOS_START ; 
 int /*<<< orphan*/  BE2_FCOE_PRIMARY_IMAGE_START ; 
 int /*<<< orphan*/  BE2_ISCSI_BACKUP_IMAGE_START ; 
 int /*<<< orphan*/  BE2_ISCSI_BIOS_START ; 
 int /*<<< orphan*/  BE2_ISCSI_PRIMARY_IMAGE_START ; 
 int /*<<< orphan*/  BE2_PXE_BIOS_START ; 
 int /*<<< orphan*/  BE2_REDBOOT_COMP_MAX_SIZE ; 
 int /*<<< orphan*/  BE2_REDBOOT_START ; 
 int /*<<< orphan*/  BE3_BIOS_COMP_MAX_SIZE ; 
 int /*<<< orphan*/  BE3_COMP_MAX_SIZE ; 
 int /*<<< orphan*/  BE3_FCOE_BACKUP_IMAGE_START ; 
 int /*<<< orphan*/  BE3_FCOE_BIOS_START ; 
 int /*<<< orphan*/  BE3_FCOE_PRIMARY_IMAGE_START ; 
 int /*<<< orphan*/  BE3_ISCSI_BACKUP_IMAGE_START ; 
 int /*<<< orphan*/  BE3_ISCSI_BIOS_START ; 
 int /*<<< orphan*/  BE3_ISCSI_PRIMARY_IMAGE_START ; 
 int /*<<< orphan*/  BE3_NCSI_COMP_MAX_SIZE ; 
 int /*<<< orphan*/  BE3_NCSI_START ; 
 int /*<<< orphan*/  BE3_PHY_FW_COMP_MAX_SIZE ; 
 int /*<<< orphan*/  BE3_PHY_FW_START ; 
 int /*<<< orphan*/  BE3_PXE_BIOS_START ; 
 int /*<<< orphan*/  BE3_REDBOOT_COMP_MAX_SIZE ; 
 int /*<<< orphan*/  BE3_REDBOOT_START ; 
 scalar_t__ BE3_chip (struct be_adapter*) ; 
 int /*<<< orphan*/  IMAGE_BOOT_CODE ; 
 int /*<<< orphan*/  IMAGE_FIRMWARE_BACKUP_FCOE ; 
 int /*<<< orphan*/  IMAGE_FIRMWARE_BACKUP_ISCSI ; 
 int /*<<< orphan*/  IMAGE_FIRMWARE_FCOE ; 
 int /*<<< orphan*/  IMAGE_FIRMWARE_ISCSI ; 
 int /*<<< orphan*/  IMAGE_FIRMWARE_PHY ; 
 int /*<<< orphan*/  IMAGE_NCSI ; 
 int /*<<< orphan*/  IMAGE_OPTION_ROM_FCOE ; 
 int /*<<< orphan*/  IMAGE_OPTION_ROM_ISCSI ; 
 int /*<<< orphan*/  IMAGE_OPTION_ROM_PXE ; 
 int /*<<< orphan*/  NCSI_UPDATE_LOG ; 
 scalar_t__ OPTYPE_BIOS ; 
 scalar_t__ OPTYPE_FCOE_BIOS ; 
 scalar_t__ OPTYPE_FCOE_FW_ACTIVE ; 
 scalar_t__ OPTYPE_FCOE_FW_BACKUP ; 
 scalar_t__ OPTYPE_ISCSI_ACTIVE ; 
 scalar_t__ OPTYPE_ISCSI_BACKUP ; 
 scalar_t__ OPTYPE_NCSI_FW ; 
 scalar_t__ OPTYPE_PHY_FW ; 
 scalar_t__ OPTYPE_PXE_BIOS ; 
 scalar_t__ OPTYPE_REDBOOT ; 
 int be_check_flash_crc (struct be_adapter*,int /*<<< orphan*/  const*,int,int,int,scalar_t__,int*) ; 
 int be_flash (struct be_adapter*,int /*<<< orphan*/  const*,struct be_dma_mem*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be_fw_ncsi_supported (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct flash_section_info* get_fsec_info (struct be_adapter*,int,struct firmware const*) ; 
 int /*<<< orphan*/  is_comp_in_ufi (struct be_adapter*,struct flash_section_info*,scalar_t__) ; 
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

	struct flash_comp gen3_flash_types[] = {
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

	struct flash_comp gen2_flash_types[] = {
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