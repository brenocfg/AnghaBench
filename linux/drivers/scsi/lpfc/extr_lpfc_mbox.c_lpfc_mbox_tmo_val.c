#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct lpfc_hba {int dummy; } ;
struct TYPE_8__ {int mbxCommand; } ;
struct TYPE_7__ {TYPE_2__ mb; } ;
struct TYPE_9__ {TYPE_1__ u; } ;
typedef  TYPE_2__ MAILBOX_t ;
typedef  TYPE_3__ LPFC_MBOXQ_t ;

/* Variables and functions */
#define  LPFC_MBOX_OPCODE_DELETE_OBJECT 154 
#define  LPFC_MBOX_OPCODE_FCOE_SET_FCLINK_SETTINGS 153 
#define  LPFC_MBOX_OPCODE_GET_FACTORY_PROFILE_CONFIG 152 
#define  LPFC_MBOX_OPCODE_GET_PROFILE_CAPACITIES 151 
#define  LPFC_MBOX_OPCODE_GET_PROFILE_CONFIG 150 
#define  LPFC_MBOX_OPCODE_GET_PROFILE_LIST 149 
#define  LPFC_MBOX_OPCODE_GET_VPD_DATA 148 
#define  LPFC_MBOX_OPCODE_READ_OBJECT 147 
#define  LPFC_MBOX_OPCODE_READ_OBJECT_LIST 146 
#define  LPFC_MBOX_OPCODE_RESET_LICENSES 145 
#define  LPFC_MBOX_OPCODE_SEND_ACTIVATION 144 
#define  LPFC_MBOX_OPCODE_SET_ACT_PROFILE 143 
#define  LPFC_MBOX_OPCODE_SET_BOOT_CONFIG 142 
#define  LPFC_MBOX_OPCODE_SET_PHYSICAL_LINK_CONFIG 141 
#define  LPFC_MBOX_OPCODE_SET_PROFILE_CONFIG 140 
#define  LPFC_MBOX_OPCODE_WRITE_OBJECT 139 
 int LPFC_MBOX_SLI4_CONFIG_EXTENDED_TMO ; 
 int LPFC_MBOX_SLI4_CONFIG_TMO ; 
 int /*<<< orphan*/  LPFC_MBOX_SUBSYSTEM_COMMON ; 
 int /*<<< orphan*/  LPFC_MBOX_SUBSYSTEM_FCOE ; 
 int LPFC_MBOX_TMO ; 
 int LPFC_MBOX_TMO_FLASH_CMD ; 
#define  MBX_ACCESS_VDATA 138 
#define  MBX_DEL_LD_ENTRY 137 
#define  MBX_DOWN_LOAD 136 
#define  MBX_DUMP_MEMORY 135 
#define  MBX_LOAD_AREA 134 
#define  MBX_LOAD_EXP_ROM 133 
#define  MBX_SLI4_CONFIG 132 
#define  MBX_UPDATE_CFG 131 
#define  MBX_WRITE_NV 130 
#define  MBX_WRITE_VPARMS 129 
#define  MBX_WRITE_WWN 128 
 int /*<<< orphan*/  lpfc_sli_config_mbox_opcode_get (struct lpfc_hba*,TYPE_3__*) ; 
 int /*<<< orphan*/  lpfc_sli_config_mbox_subsys_get (struct lpfc_hba*,TYPE_3__*) ; 

int
lpfc_mbox_tmo_val(struct lpfc_hba *phba, LPFC_MBOXQ_t *mboxq)
{
	MAILBOX_t *mbox = &mboxq->u.mb;
	uint8_t subsys, opcode;

	switch (mbox->mbxCommand) {
	case MBX_WRITE_NV:	/* 0x03 */
	case MBX_DUMP_MEMORY:	/* 0x17 */
	case MBX_UPDATE_CFG:	/* 0x1B */
	case MBX_DOWN_LOAD:	/* 0x1C */
	case MBX_DEL_LD_ENTRY:	/* 0x1D */
	case MBX_WRITE_VPARMS:	/* 0x32 */
	case MBX_LOAD_AREA:	/* 0x81 */
	case MBX_WRITE_WWN:     /* 0x98 */
	case MBX_LOAD_EXP_ROM:	/* 0x9C */
	case MBX_ACCESS_VDATA:	/* 0xA5 */
		return LPFC_MBOX_TMO_FLASH_CMD;
	case MBX_SLI4_CONFIG:	/* 0x9b */
		subsys = lpfc_sli_config_mbox_subsys_get(phba, mboxq);
		opcode = lpfc_sli_config_mbox_opcode_get(phba, mboxq);
		if (subsys == LPFC_MBOX_SUBSYSTEM_COMMON) {
			switch (opcode) {
			case LPFC_MBOX_OPCODE_READ_OBJECT:
			case LPFC_MBOX_OPCODE_WRITE_OBJECT:
			case LPFC_MBOX_OPCODE_READ_OBJECT_LIST:
			case LPFC_MBOX_OPCODE_DELETE_OBJECT:
			case LPFC_MBOX_OPCODE_GET_PROFILE_LIST:
			case LPFC_MBOX_OPCODE_SET_ACT_PROFILE:
			case LPFC_MBOX_OPCODE_GET_PROFILE_CONFIG:
			case LPFC_MBOX_OPCODE_SET_PROFILE_CONFIG:
			case LPFC_MBOX_OPCODE_GET_FACTORY_PROFILE_CONFIG:
			case LPFC_MBOX_OPCODE_GET_PROFILE_CAPACITIES:
			case LPFC_MBOX_OPCODE_SEND_ACTIVATION:
			case LPFC_MBOX_OPCODE_RESET_LICENSES:
			case LPFC_MBOX_OPCODE_SET_BOOT_CONFIG:
			case LPFC_MBOX_OPCODE_GET_VPD_DATA:
			case LPFC_MBOX_OPCODE_SET_PHYSICAL_LINK_CONFIG:
				return LPFC_MBOX_SLI4_CONFIG_EXTENDED_TMO;
			}
		}
		if (subsys == LPFC_MBOX_SUBSYSTEM_FCOE) {
			switch (opcode) {
			case LPFC_MBOX_OPCODE_FCOE_SET_FCLINK_SETTINGS:
				return LPFC_MBOX_SLI4_CONFIG_EXTENDED_TMO;
			}
		}
		return LPFC_MBOX_SLI4_CONFIG_TMO;
	}
	return LPFC_MBOX_TMO;
}