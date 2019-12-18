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
typedef  scalar_t__ uchar ;
struct TYPE_5__ {int bus_type; int is_in_int; int scsi_reset_wait; int max_sdtr_index; TYPE_1__* cfg; int /*<<< orphan*/ ** scsiq_busy_tail; int /*<<< orphan*/ ** scsiq_busy_head; int /*<<< orphan*/ * max_dvc_qng; scalar_t__* cur_dvc_qng; int /*<<< orphan*/  sdtr_period_tbl; int /*<<< orphan*/  max_dma_count; void* start_motor; int /*<<< orphan*/  max_total_qng; scalar_t__ init_sdtr; int /*<<< orphan*/  dvc_cntl; scalar_t__ min_sdtr_index; scalar_t__ res2; scalar_t__ redo_scam; scalar_t__ queue_full_or_busy; scalar_t__ unit_not_ready; scalar_t__ no_scam; scalar_t__ use_tagged_qng; scalar_t__ last_q_shortage; scalar_t__ in_critical_cnt; scalar_t__ cur_total_qng; scalar_t__ sdtr_done; scalar_t__ pci_fix_asyn_xfer_always; scalar_t__ pci_fix_asyn_xfer; scalar_t__ bug_fix_cntl; int /*<<< orphan*/  err_code; int /*<<< orphan*/  iop_base; } ;
struct TYPE_4__ {int /*<<< orphan*/ * max_tag_qng; scalar_t__ isa_dma_channel; int /*<<< orphan*/  isa_dma_speed; scalar_t__ chip_version; int /*<<< orphan*/  chip_scsi_id; void* disc_enable; void* sdtr_enable; scalar_t__ cmd_qng_enabled; scalar_t__ can_tagged_qng; } ;
typedef  int /*<<< orphan*/  PortAddr ;
typedef  int /*<<< orphan*/  ASC_SCSI_Q ;
typedef  TYPE_2__ ASC_DVC_VAR ;

/* Variables and functions */
 scalar_t__ ASC_CHIP_MIN_VER_ISA_PNP ; 
 scalar_t__ ASC_CHIP_VER_PCI_ULTRA_3050 ; 
 scalar_t__ ASC_CHIP_VER_PCI_ULTRA_3150 ; 
 int /*<<< orphan*/  ASC_DEF_CHIP_SCSI_ID ; 
 int /*<<< orphan*/  ASC_DEF_DVC_CNTL ; 
 int /*<<< orphan*/  ASC_DEF_ISA_DMA_SPEED ; 
 int /*<<< orphan*/  ASC_DEF_MAX_TOTAL_QNG ; 
 int /*<<< orphan*/  ASC_IERR_NO_BUS_TYPE ; 
 int ASC_IS_EISA ; 
 int ASC_IS_ISA ; 
 int ASC_IS_ISAPNP ; 
 int ASC_IS_PCI ; 
 int ASC_IS_PCI_ULTRA ; 
 int ASC_IS_VL ; 
 int /*<<< orphan*/  ASC_MAX_INRAM_TAG_QNG ; 
 int /*<<< orphan*/  ASC_MAX_SCSI1_QNG ; 
 int ASC_MAX_TID ; 
 void* ASC_SCSI_WIDTH_BIT_SET ; 
 scalar_t__ AscGetChipVersion (int /*<<< orphan*/ ,int) ; 
 scalar_t__ AscGetIsaDmaChannel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AscGetMaxDmaCount (int) ; 
 int /*<<< orphan*/  AscSetChipControl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AscSetChipIFC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AscSetChipStatus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AscSetExtraControl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CC_HALT ; 
 int /*<<< orphan*/  IFC_INIT_DEFAULT ; 
 int SEC_ACTIVE_NEGATE ; 
 int SEC_ENABLE_FILTER ; 
 int SEC_SLEW_RATE ; 
 int /*<<< orphan*/  asc_syn_ultra_xfer_period ; 
 int /*<<< orphan*/  asc_syn_xfer_period ; 

__attribute__((used)) static void AscInitAscDvcVar(ASC_DVC_VAR *asc_dvc)
{
	int i;
	PortAddr iop_base;
	uchar chip_version;

	iop_base = asc_dvc->iop_base;
	asc_dvc->err_code = 0;
	if ((asc_dvc->bus_type &
	     (ASC_IS_ISA | ASC_IS_PCI | ASC_IS_EISA | ASC_IS_VL)) == 0) {
		asc_dvc->err_code |= ASC_IERR_NO_BUS_TYPE;
	}
	AscSetChipControl(iop_base, CC_HALT);
	AscSetChipStatus(iop_base, 0);
	asc_dvc->bug_fix_cntl = 0;
	asc_dvc->pci_fix_asyn_xfer = 0;
	asc_dvc->pci_fix_asyn_xfer_always = 0;
	/* asc_dvc->init_state initialized in AscInitGetConfig(). */
	asc_dvc->sdtr_done = 0;
	asc_dvc->cur_total_qng = 0;
	asc_dvc->is_in_int = false;
	asc_dvc->in_critical_cnt = 0;
	asc_dvc->last_q_shortage = 0;
	asc_dvc->use_tagged_qng = 0;
	asc_dvc->no_scam = 0;
	asc_dvc->unit_not_ready = 0;
	asc_dvc->queue_full_or_busy = 0;
	asc_dvc->redo_scam = 0;
	asc_dvc->res2 = 0;
	asc_dvc->min_sdtr_index = 0;
	asc_dvc->cfg->can_tagged_qng = 0;
	asc_dvc->cfg->cmd_qng_enabled = 0;
	asc_dvc->dvc_cntl = ASC_DEF_DVC_CNTL;
	asc_dvc->init_sdtr = 0;
	asc_dvc->max_total_qng = ASC_DEF_MAX_TOTAL_QNG;
	asc_dvc->scsi_reset_wait = 3;
	asc_dvc->start_motor = ASC_SCSI_WIDTH_BIT_SET;
	asc_dvc->max_dma_count = AscGetMaxDmaCount(asc_dvc->bus_type);
	asc_dvc->cfg->sdtr_enable = ASC_SCSI_WIDTH_BIT_SET;
	asc_dvc->cfg->disc_enable = ASC_SCSI_WIDTH_BIT_SET;
	asc_dvc->cfg->chip_scsi_id = ASC_DEF_CHIP_SCSI_ID;
	chip_version = AscGetChipVersion(iop_base, asc_dvc->bus_type);
	asc_dvc->cfg->chip_version = chip_version;
	asc_dvc->sdtr_period_tbl = asc_syn_xfer_period;
	asc_dvc->max_sdtr_index = 7;
	if ((asc_dvc->bus_type & ASC_IS_PCI) &&
	    (chip_version >= ASC_CHIP_VER_PCI_ULTRA_3150)) {
		asc_dvc->bus_type = ASC_IS_PCI_ULTRA;
		asc_dvc->sdtr_period_tbl = asc_syn_ultra_xfer_period;
		asc_dvc->max_sdtr_index = 15;
		if (chip_version == ASC_CHIP_VER_PCI_ULTRA_3150) {
			AscSetExtraControl(iop_base,
					   (SEC_ACTIVE_NEGATE | SEC_SLEW_RATE));
		} else if (chip_version >= ASC_CHIP_VER_PCI_ULTRA_3050) {
			AscSetExtraControl(iop_base,
					   (SEC_ACTIVE_NEGATE |
					    SEC_ENABLE_FILTER));
		}
	}
	if (asc_dvc->bus_type == ASC_IS_PCI) {
		AscSetExtraControl(iop_base,
				   (SEC_ACTIVE_NEGATE | SEC_SLEW_RATE));
	}

	asc_dvc->cfg->isa_dma_speed = ASC_DEF_ISA_DMA_SPEED;
#ifdef CONFIG_ISA
	if ((asc_dvc->bus_type & ASC_IS_ISA) != 0) {
		if (chip_version >= ASC_CHIP_MIN_VER_ISA_PNP) {
			AscSetChipIFC(iop_base, IFC_INIT_DEFAULT);
			asc_dvc->bus_type = ASC_IS_ISAPNP;
		}
		asc_dvc->cfg->isa_dma_channel =
		    (uchar)AscGetIsaDmaChannel(iop_base);
	}
#endif /* CONFIG_ISA */
	for (i = 0; i <= ASC_MAX_TID; i++) {
		asc_dvc->cur_dvc_qng[i] = 0;
		asc_dvc->max_dvc_qng[i] = ASC_MAX_SCSI1_QNG;
		asc_dvc->scsiq_busy_head[i] = (ASC_SCSI_Q *)0L;
		asc_dvc->scsiq_busy_tail[i] = (ASC_SCSI_Q *)0L;
		asc_dvc->cfg->max_tag_qng[i] = ASC_MAX_INRAM_TAG_QNG;
	}
}