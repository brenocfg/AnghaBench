#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {scalar_t__ device; } ;
struct TYPE_6__ {int err_code; int bus_type; int /*<<< orphan*/  init_state; TYPE_2__* cfg; int /*<<< orphan*/  bug_fix_cntl; int /*<<< orphan*/  iop_base; } ;
struct TYPE_4__ {TYPE_3__ asc_dvc_var; } ;
struct asc_board {TYPE_1__ dvc_var; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_5__ {int cmd_qng_enabled; int disc_enable; scalar_t__ chip_scsi_id; int /*<<< orphan*/  isa_dma_speed; int /*<<< orphan*/  isa_dma_channel; } ;
typedef  int /*<<< orphan*/  PortAddr ;
typedef  TYPE_3__ ASC_DVC_VAR ;

/* Variables and functions */
 int /*<<< orphan*/  ASC_BUG_FIX_ASYN_USE_SYN ; 
 int /*<<< orphan*/  ASC_BUG_FIX_IF_NOT_DWB ; 
 unsigned short ASC_CFG_MSW_CLR_MASK ; 
 scalar_t__ ASC_CHIP_VER_ASYN_BUG ; 
 int ASC_IERR_BAD_SIGNATURE ; 
 int ASC_IERR_SET_SCSI_ID ; 
 int /*<<< orphan*/  ASC_INIT_STATE_BEG_SET_CFG ; 
 int /*<<< orphan*/  ASC_INIT_STATE_END_SET_CFG ; 
 int ASC_IS_ISA ; 
 int ASC_IS_ISAPNP ; 
 int ASC_IS_PCI ; 
 int ASC_IS_PCI_ULTRA ; 
#define  ASC_WARN_AUTO_CONFIG 132 
 unsigned short ASC_WARN_CFG_MSW_RECOVER ; 
#define  ASC_WARN_CMD_QNG_CONFLICT 131 
#define  ASC_WARN_EEPROM_CHKSUM 130 
#define  ASC_WARN_IO_PORT_ROTATE 129 
#define  ASC_WARN_IRQ_MODIFIED 128 
 int /*<<< orphan*/  AscFindSignature (int /*<<< orphan*/ ) ; 
 unsigned short AscGetChipCfgMsw (int /*<<< orphan*/ ) ; 
 int AscGetChipStatus (int /*<<< orphan*/ ) ; 
 scalar_t__ AscGetChipVersion (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AscSetChipCfgMsw (int /*<<< orphan*/ ,unsigned short) ; 
 scalar_t__ AscSetChipScsiID (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  AscSetIsaDmaChannel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AscSetIsaDmaSpeed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CSW_AUTO_CONFIG ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 scalar_t__ PCI_DEVICE_ID_ASP_1200A ; 
 scalar_t__ PCI_DEVICE_ID_ASP_ABP940 ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,struct Scsi_Host*,char*,...) ; 
 struct asc_board* shost_priv (struct Scsi_Host*) ; 

__attribute__((used)) static int AscInitSetConfig(struct pci_dev *pdev, struct Scsi_Host *shost)
{
	struct asc_board *board = shost_priv(shost);
	ASC_DVC_VAR *asc_dvc = &board->dvc_var.asc_dvc_var;
	PortAddr iop_base = asc_dvc->iop_base;
	unsigned short cfg_msw;
	unsigned short warn_code = 0;

	asc_dvc->init_state |= ASC_INIT_STATE_BEG_SET_CFG;
	if (asc_dvc->err_code != 0)
		return asc_dvc->err_code;
	if (!AscFindSignature(asc_dvc->iop_base)) {
		asc_dvc->err_code = ASC_IERR_BAD_SIGNATURE;
		return asc_dvc->err_code;
	}

	cfg_msw = AscGetChipCfgMsw(iop_base);
	if ((cfg_msw & ASC_CFG_MSW_CLR_MASK) != 0) {
		cfg_msw &= ~ASC_CFG_MSW_CLR_MASK;
		warn_code |= ASC_WARN_CFG_MSW_RECOVER;
		AscSetChipCfgMsw(iop_base, cfg_msw);
	}
	if ((asc_dvc->cfg->cmd_qng_enabled & asc_dvc->cfg->disc_enable) !=
	    asc_dvc->cfg->cmd_qng_enabled) {
		asc_dvc->cfg->disc_enable = asc_dvc->cfg->cmd_qng_enabled;
		warn_code |= ASC_WARN_CMD_QNG_CONFLICT;
	}
	if (AscGetChipStatus(iop_base) & CSW_AUTO_CONFIG) {
		warn_code |= ASC_WARN_AUTO_CONFIG;
	}
#ifdef CONFIG_PCI
	if (asc_dvc->bus_type & ASC_IS_PCI) {
		cfg_msw &= 0xFFC0;
		AscSetChipCfgMsw(iop_base, cfg_msw);
		if ((asc_dvc->bus_type & ASC_IS_PCI_ULTRA) == ASC_IS_PCI_ULTRA) {
		} else {
			if ((pdev->device == PCI_DEVICE_ID_ASP_1200A) ||
			    (pdev->device == PCI_DEVICE_ID_ASP_ABP940)) {
				asc_dvc->bug_fix_cntl |= ASC_BUG_FIX_IF_NOT_DWB;
				asc_dvc->bug_fix_cntl |=
				    ASC_BUG_FIX_ASYN_USE_SYN;
			}
		}
	} else
#endif /* CONFIG_PCI */
	if (asc_dvc->bus_type == ASC_IS_ISAPNP) {
		if (AscGetChipVersion(iop_base, asc_dvc->bus_type)
		    == ASC_CHIP_VER_ASYN_BUG) {
			asc_dvc->bug_fix_cntl |= ASC_BUG_FIX_ASYN_USE_SYN;
		}
	}
	if (AscSetChipScsiID(iop_base, asc_dvc->cfg->chip_scsi_id) !=
	    asc_dvc->cfg->chip_scsi_id) {
		asc_dvc->err_code |= ASC_IERR_SET_SCSI_ID;
	}
#ifdef CONFIG_ISA
	if (asc_dvc->bus_type & ASC_IS_ISA) {
		AscSetIsaDmaChannel(iop_base, asc_dvc->cfg->isa_dma_channel);
		AscSetIsaDmaSpeed(iop_base, asc_dvc->cfg->isa_dma_speed);
	}
#endif /* CONFIG_ISA */

	asc_dvc->init_state |= ASC_INIT_STATE_END_SET_CFG;

	switch (warn_code) {
	case 0:	/* No error. */
		break;
	case ASC_WARN_IO_PORT_ROTATE:
		shost_printk(KERN_WARNING, shost, "I/O port address "
				"modified\n");
		break;
	case ASC_WARN_AUTO_CONFIG:
		shost_printk(KERN_WARNING, shost, "I/O port increment switch "
				"enabled\n");
		break;
	case ASC_WARN_EEPROM_CHKSUM:
		shost_printk(KERN_WARNING, shost, "EEPROM checksum error\n");
		break;
	case ASC_WARN_IRQ_MODIFIED:
		shost_printk(KERN_WARNING, shost, "IRQ modified\n");
		break;
	case ASC_WARN_CMD_QNG_CONFLICT:
		shost_printk(KERN_WARNING, shost, "tag queuing w/o "
				"disconnects\n");
		break;
	default:
		shost_printk(KERN_WARNING, shost, "unknown warning: 0x%x\n",
				warn_code);
		break;
	}

	if (asc_dvc->err_code != 0)
		shost_printk(KERN_ERR, shost, "error 0x%x at init_state "
			"0x%x\n", asc_dvc->err_code, asc_dvc->init_state);

	return asc_dvc->err_code;
}