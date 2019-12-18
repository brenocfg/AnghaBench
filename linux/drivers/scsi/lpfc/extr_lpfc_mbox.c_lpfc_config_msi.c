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
typedef  void* uint32_t ;
struct lpfc_hba {int cfg_use_msi; int sli_rev; } ;
struct TYPE_9__ {int* messageNumberByHA; void** autoClearHA; void** attentionConditions; } ;
struct TYPE_10__ {TYPE_2__ varCfgMSI; } ;
struct TYPE_11__ {int /*<<< orphan*/  mbxOwner; int /*<<< orphan*/  mbxCommand; TYPE_3__ un; } ;
struct TYPE_8__ {TYPE_4__ mb; } ;
struct TYPE_12__ {TYPE_1__ u; } ;
typedef  TYPE_4__ MAILBOX_t ;
typedef  TYPE_5__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int EINVAL ; 
 int HA_ERATT ; 
 int HA_LATT ; 
 int HA_MBATT ; 
 int HA_R0ATT ; 
 size_t HA_R0_POS ; 
 int HA_R1ATT ; 
 size_t HA_R1_POS ; 
 int HA_R2ATT ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_INIT ; 
 int /*<<< orphan*/  MBX_CONFIG_MSI ; 
 int /*<<< orphan*/  OWN_HOST ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 

int
lpfc_config_msi(struct lpfc_hba *phba, LPFC_MBOXQ_t *pmb)
{
	MAILBOX_t *mb = &pmb->u.mb;
	uint32_t attentionConditions[2];

	/* Sanity check */
	if (phba->cfg_use_msi != 2) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"0475 Not configured for supporting MSI-X "
				"cfg_use_msi: 0x%x\n", phba->cfg_use_msi);
		return -EINVAL;
	}

	if (phba->sli_rev < 3) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"0476 HBA not supporting SLI-3 or later "
				"SLI Revision: 0x%x\n", phba->sli_rev);
		return -EINVAL;
	}

	/* Clear mailbox command fields */
	memset(pmb, 0, sizeof(LPFC_MBOXQ_t));

	/*
	 * SLI-3, Message Signaled Interrupt Fearure.
	 */

	/* Multi-message attention configuration */
	attentionConditions[0] = (HA_R0ATT | HA_R1ATT | HA_R2ATT | HA_ERATT |
				  HA_LATT | HA_MBATT);
	attentionConditions[1] = 0;

	mb->un.varCfgMSI.attentionConditions[0] = attentionConditions[0];
	mb->un.varCfgMSI.attentionConditions[1] = attentionConditions[1];

	/*
	 * Set up message number to HA bit association
	 */
#ifdef __BIG_ENDIAN_BITFIELD
	/* RA0 (FCP Ring) */
	mb->un.varCfgMSI.messageNumberByHA[HA_R0_POS] = 1;
	/* RA1 (Other Protocol Extra Ring) */
	mb->un.varCfgMSI.messageNumberByHA[HA_R1_POS] = 1;
#else   /*  __LITTLE_ENDIAN_BITFIELD */
	/* RA0 (FCP Ring) */
	mb->un.varCfgMSI.messageNumberByHA[HA_R0_POS^3] = 1;
	/* RA1 (Other Protocol Extra Ring) */
	mb->un.varCfgMSI.messageNumberByHA[HA_R1_POS^3] = 1;
#endif
	/* Multi-message interrupt autoclear configuration*/
	mb->un.varCfgMSI.autoClearHA[0] = attentionConditions[0];
	mb->un.varCfgMSI.autoClearHA[1] = attentionConditions[1];

	/* For now, HBA autoclear does not work reliably, disable it */
	mb->un.varCfgMSI.autoClearHA[0] = 0;
	mb->un.varCfgMSI.autoClearHA[1] = 0;

	/* Set command and owner bit */
	mb->mbxCommand = MBX_CONFIG_MSI;
	mb->mbxOwner = OWN_HOST;

	return 0;
}