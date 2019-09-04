#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct flash_section_entry {int /*<<< orphan*/  optype; int /*<<< orphan*/  type; } ;

/* Variables and functions */
#define  IMAGE_BOOT_CODE 139 
#define  IMAGE_FIRMWARE_BACKUP_ISCSI 138 
#define  IMAGE_FIRMWARE_ISCSI 137 
#define  IMAGE_FIRMWARE_PHY 136 
#define  IMAGE_FLASHISM_JUMPVECTOR 135 
#define  IMAGE_NCSI 134 
#define  IMAGE_OPTION_ROM_FCOE 133 
#define  IMAGE_OPTION_ROM_ISCSI 132 
#define  IMAGE_OPTION_ROM_PXE 131 
#define  IMAGE_REDBOOT_CONFIG 130 
#define  IMAGE_REDBOOT_DIR 129 
#define  IMAGE_UFI_DIR 128 
 int OPTYPE_BIOS ; 
 int OPTYPE_FCOE_BIOS ; 
 int OPTYPE_FLASHISM_JUMPVECTOR ; 
 int OPTYPE_ISCSI_ACTIVE ; 
 int OPTYPE_ISCSI_BACKUP ; 
 int OPTYPE_NCSI_FW ; 
 int OPTYPE_PXE_BIOS ; 
 int OPTYPE_REDBOOT ; 
 int OPTYPE_REDBOOT_CONFIG ; 
 int OPTYPE_REDBOOT_DIR ; 
 int OPTYPE_SH_PHY_FW ; 
 int OPTYPE_UFI_DIR ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 be_get_img_optype(struct flash_section_entry fsec_entry)
{
	u32 img_type = le32_to_cpu(fsec_entry.type);
	u16 img_optype = le16_to_cpu(fsec_entry.optype);

	if (img_optype != 0xFFFF)
		return img_optype;

	switch (img_type) {
	case IMAGE_FIRMWARE_ISCSI:
		img_optype = OPTYPE_ISCSI_ACTIVE;
		break;
	case IMAGE_BOOT_CODE:
		img_optype = OPTYPE_REDBOOT;
		break;
	case IMAGE_OPTION_ROM_ISCSI:
		img_optype = OPTYPE_BIOS;
		break;
	case IMAGE_OPTION_ROM_PXE:
		img_optype = OPTYPE_PXE_BIOS;
		break;
	case IMAGE_OPTION_ROM_FCOE:
		img_optype = OPTYPE_FCOE_BIOS;
		break;
	case IMAGE_FIRMWARE_BACKUP_ISCSI:
		img_optype = OPTYPE_ISCSI_BACKUP;
		break;
	case IMAGE_NCSI:
		img_optype = OPTYPE_NCSI_FW;
		break;
	case IMAGE_FLASHISM_JUMPVECTOR:
		img_optype = OPTYPE_FLASHISM_JUMPVECTOR;
		break;
	case IMAGE_FIRMWARE_PHY:
		img_optype = OPTYPE_SH_PHY_FW;
		break;
	case IMAGE_REDBOOT_DIR:
		img_optype = OPTYPE_REDBOOT_DIR;
		break;
	case IMAGE_REDBOOT_CONFIG:
		img_optype = OPTYPE_REDBOOT_CONFIG;
		break;
	case IMAGE_UFI_DIR:
		img_optype = OPTYPE_UFI_DIR;
		break;
	default:
		break;
	}

	return img_optype;
}