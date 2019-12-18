#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct lpfc_vport {int fc_flag; } ;
struct lpfc_hba {int wait_4_mlo_maint_flg; int /*<<< orphan*/  fc_topology; int /*<<< orphan*/  hbalock; int /*<<< orphan*/  link_flag; } ;
struct TYPE_4__ {int* varWords; } ;
struct TYPE_5__ {int mbxCommand; TYPE_1__ un; } ;
typedef  TYPE_2__ MAILBOX_t ;

/* Variables and functions */
 int EPERM ; 
 int FC_OFFLINE_MODE ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  LOG_INIT ; 
 int /*<<< orphan*/  LOG_LIBDFC ; 
 int /*<<< orphan*/  LPFC_TOPOLOGY_PT_PT ; 
 int /*<<< orphan*/  LS_LOOPBACK_MODE ; 
#define  MBX_BEACON 172 
#define  MBX_CLEAR_LA 171 
#define  MBX_CONFIG_LINK 170 
#define  MBX_CONFIG_PORT 169 
#define  MBX_CONFIG_RING 168 
#define  MBX_DEL_LD_ENTRY 167 
#define  MBX_DOWN_LINK 166 
#define  MBX_DOWN_LOAD 165 
#define  MBX_DUMP_CONTEXT 164 
#define  MBX_DUMP_MEMORY 163 
#define  MBX_INIT_LINK 162 
#define  MBX_KILL_BOARD 161 
#define  MBX_LOAD_AREA 160 
#define  MBX_LOAD_EXP_ROM 159 
#define  MBX_LOAD_SM 158 
#define  MBX_PORT_CAPABILITIES 157 
#define  MBX_PORT_IOV_CONTROL 156 
#define  MBX_READ_CONFIG 155 
#define  MBX_READ_EVENT_LOG 154 
#define  MBX_READ_EVENT_LOG_STATUS 153 
#define  MBX_READ_LNK_STAT 152 
#define  MBX_READ_NV 151 
#define  MBX_READ_RCONFIG 150 
#define  MBX_READ_REV 149 
#define  MBX_READ_SPARM64 148 
#define  MBX_READ_STATUS 147 
#define  MBX_READ_TOPOLOGY 146 
#define  MBX_READ_XRI 145 
#define  MBX_REG_LOGIN 144 
#define  MBX_REG_LOGIN64 143 
#define  MBX_RESET_RING 142 
#define  MBX_RESTART 141 
#define  MBX_RUN_BIU_DIAG 140 
#define  MBX_RUN_BIU_DIAG64 139 
#define  MBX_RUN_DIAGS 138 
#define  MBX_SET_DEBUG 137 
#define  MBX_SET_MASK 136 
#define  MBX_SET_VARIABLE 135 
#define  MBX_SLI4_CONFIG 134 
#define  MBX_UNREG_LOGIN 133 
#define  MBX_UPDATE_CFG 132 
#define  MBX_WRITE_EVENT_LOG 131 
#define  MBX_WRITE_NV 130 
#define  MBX_WRITE_VPARMS 129 
#define  MBX_WRITE_WWN 128 
 int SETVAR_MLOMNT ; 
 int SETVAR_MLORST ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lpfc_bsg_check_cmd_access(struct lpfc_hba *phba,
	MAILBOX_t *mb, struct lpfc_vport *vport)
{
	/* return negative error values for bsg job */
	switch (mb->mbxCommand) {
	/* Offline only */
	case MBX_INIT_LINK:
	case MBX_DOWN_LINK:
	case MBX_CONFIG_LINK:
	case MBX_CONFIG_RING:
	case MBX_RESET_RING:
	case MBX_UNREG_LOGIN:
	case MBX_CLEAR_LA:
	case MBX_DUMP_CONTEXT:
	case MBX_RUN_DIAGS:
	case MBX_RESTART:
	case MBX_SET_MASK:
		if (!(vport->fc_flag & FC_OFFLINE_MODE)) {
			lpfc_printf_log(phba, KERN_WARNING, LOG_LIBDFC,
				"2743 Command 0x%x is illegal in on-line "
				"state\n",
				mb->mbxCommand);
			return -EPERM;
		}
	case MBX_WRITE_NV:
	case MBX_WRITE_VPARMS:
	case MBX_LOAD_SM:
	case MBX_READ_NV:
	case MBX_READ_CONFIG:
	case MBX_READ_RCONFIG:
	case MBX_READ_STATUS:
	case MBX_READ_XRI:
	case MBX_READ_REV:
	case MBX_READ_LNK_STAT:
	case MBX_DUMP_MEMORY:
	case MBX_DOWN_LOAD:
	case MBX_UPDATE_CFG:
	case MBX_KILL_BOARD:
	case MBX_READ_TOPOLOGY:
	case MBX_LOAD_AREA:
	case MBX_LOAD_EXP_ROM:
	case MBX_BEACON:
	case MBX_DEL_LD_ENTRY:
	case MBX_SET_DEBUG:
	case MBX_WRITE_WWN:
	case MBX_SLI4_CONFIG:
	case MBX_READ_EVENT_LOG:
	case MBX_READ_EVENT_LOG_STATUS:
	case MBX_WRITE_EVENT_LOG:
	case MBX_PORT_CAPABILITIES:
	case MBX_PORT_IOV_CONTROL:
	case MBX_RUN_BIU_DIAG64:
		break;
	case MBX_SET_VARIABLE:
		lpfc_printf_log(phba, KERN_INFO, LOG_INIT,
			"1226 mbox: set_variable 0x%x, 0x%x\n",
			mb->un.varWords[0],
			mb->un.varWords[1]);
		if ((mb->un.varWords[0] == SETVAR_MLOMNT)
			&& (mb->un.varWords[1] == 1)) {
			phba->wait_4_mlo_maint_flg = 1;
		} else if (mb->un.varWords[0] == SETVAR_MLORST) {
			spin_lock_irq(&phba->hbalock);
			phba->link_flag &= ~LS_LOOPBACK_MODE;
			spin_unlock_irq(&phba->hbalock);
			phba->fc_topology = LPFC_TOPOLOGY_PT_PT;
		}
		break;
	case MBX_READ_SPARM64:
	case MBX_REG_LOGIN:
	case MBX_REG_LOGIN64:
	case MBX_CONFIG_PORT:
	case MBX_RUN_BIU_DIAG:
	default:
		lpfc_printf_log(phba, KERN_WARNING, LOG_LIBDFC,
			"2742 Unknown Command 0x%x\n",
			mb->mbxCommand);
		return -EPERM;
	}

	return 0; /* ok */
}