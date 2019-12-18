#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int ushort ;
typedef  scalar_t__ uchar ;
struct TYPE_14__ {int cfg_lsw; int cfg_msw; int chksum; int init_sdtr; int disc_enable; int start_motor; int use_cmd_qng; int max_total_qng; int max_tag_qng; int cntl; int* adapter_info; int /*<<< orphan*/ * dos_int13_table; scalar_t__ no_scam; } ;
struct TYPE_13__ {int scsi_reset_wait; int bus_type; int start_motor; int dvc_cntl; int max_total_qng; int min_sdtr_index; TYPE_1__* cfg; int /*<<< orphan*/ * dos_int13_table; scalar_t__ no_scam; int /*<<< orphan*/  err_code; int /*<<< orphan*/  init_state; int /*<<< orphan*/  iop_base; } ;
struct TYPE_12__ {int chip_version; int sdtr_enable; int disc_enable; int cmd_qng_enabled; int* adapter_info; int chip_scsi_id; int* max_tag_qng; scalar_t__* sdtr_period_offset; int /*<<< orphan*/  isa_dma_speed; } ;
typedef  int /*<<< orphan*/  PortAddr ;
typedef  TYPE_2__ ASC_DVC_VAR ;
typedef  TYPE_3__ ASCEEP_CONFIG ;

/* Variables and functions */
 int /*<<< orphan*/  ASCV_HALTCODE_W ; 
 int ASC_CFG0_HOST_INT_ON ; 
 int ASC_CFG_MSW_CLR_MASK ; 
 scalar_t__ ASC_CHIP_VER_PCI_ULTRA_3050 ; 
 int ASC_CNTL_SDTR_ENABLE_ULTRA ; 
 int /*<<< orphan*/  ASC_DBG (int,char*,...) ; 
 int ASC_DEF_SDTR_OFFSET ; 
 int ASC_EEP_GET_CHIP_ID (TYPE_3__*) ; 
 int /*<<< orphan*/  ASC_EEP_GET_DMA_SPD (TYPE_3__*) ; 
 int /*<<< orphan*/  ASC_EEP_SET_CHIP_ID (TYPE_3__*,int) ; 
 int /*<<< orphan*/  ASC_IERR_SET_PC_ADDR ; 
 int /*<<< orphan*/  ASC_IERR_START_STOP_CHIP ; 
 int /*<<< orphan*/  ASC_INIT_RESET_SCSI_DONE ; 
 int ASC_IS_PCI_ULTRA ; 
 int ASC_MAX_INRAM_TAG_QNG ; 
 int ASC_MAX_PCI_INRAM_TOTAL_QNG ; 
 int ASC_MAX_PCI_ULTRA_INRAM_TAG_QNG ; 
 int ASC_MAX_PCI_ULTRA_INRAM_TOTAL_QNG ; 
 int ASC_MAX_TID ; 
 int ASC_MAX_TOTAL_QNG ; 
 scalar_t__ ASC_MCODE_START_ADDR ; 
 int ASC_MIN_TAG_Q_PER_DVC ; 
 int ASC_MIN_TOTAL_QNG ; 
 int /*<<< orphan*/  ASC_PRINT (char*) ; 
 int /*<<< orphan*/  ASC_PRINT1 (char*,int) ; 
 int ASC_SDTR_ULTRA_PCI_10MB_INDEX ; 
 int ASC_WARN_AUTO_CONFIG ; 
 int ASC_WARN_CFG_MSW_RECOVER ; 
 int ASC_WARN_CMD_QNG_CONFLICT ; 
 int ASC_WARN_EEPROM_CHKSUM ; 
 int ASC_WARN_EEPROM_RECOVER ; 
 void* AscGetChipCfgLsw (int /*<<< orphan*/ ) ; 
 void* AscGetChipCfgMsw (int /*<<< orphan*/ ) ; 
 scalar_t__ AscGetChipScsiCtrl (int /*<<< orphan*/ ) ; 
 int AscGetChipStatus (int /*<<< orphan*/ ) ; 
 scalar_t__ AscGetChipVersion (int /*<<< orphan*/ ,int) ; 
 int AscGetEEPConfig (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 scalar_t__ AscGetPCAddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AscIsChipHalted (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AscResetChipAndScsiBus (TYPE_2__*) ; 
 int /*<<< orphan*/  AscSetChipCfgMsw (int /*<<< orphan*/ ,int) ; 
 int AscSetEEPConfig (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  AscSetPCAddr (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ AscStopChip (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AscStopQueueExe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AscTestExternalLram (TYPE_2__*) ; 
 int /*<<< orphan*/  AscWriteLramWord (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int CSW_AUTO_CONFIG ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int AscInitFromEEP(ASC_DVC_VAR *asc_dvc)
{
	ASCEEP_CONFIG eep_config_buf;
	ASCEEP_CONFIG *eep_config;
	PortAddr iop_base;
	ushort chksum;
	ushort warn_code;
	ushort cfg_msw, cfg_lsw;
	int i;
	int write_eep = 0;

	iop_base = asc_dvc->iop_base;
	warn_code = 0;
	AscWriteLramWord(iop_base, ASCV_HALTCODE_W, 0x00FE);
	AscStopQueueExe(iop_base);
	if ((AscStopChip(iop_base)) ||
	    (AscGetChipScsiCtrl(iop_base) != 0)) {
		asc_dvc->init_state |= ASC_INIT_RESET_SCSI_DONE;
		AscResetChipAndScsiBus(asc_dvc);
		mdelay(asc_dvc->scsi_reset_wait * 1000); /* XXX: msleep? */
	}
	if (!AscIsChipHalted(iop_base)) {
		asc_dvc->err_code |= ASC_IERR_START_STOP_CHIP;
		return (warn_code);
	}
	AscSetPCAddr(iop_base, ASC_MCODE_START_ADDR);
	if (AscGetPCAddr(iop_base) != ASC_MCODE_START_ADDR) {
		asc_dvc->err_code |= ASC_IERR_SET_PC_ADDR;
		return (warn_code);
	}
	eep_config = (ASCEEP_CONFIG *)&eep_config_buf;
	cfg_msw = AscGetChipCfgMsw(iop_base);
	cfg_lsw = AscGetChipCfgLsw(iop_base);
	if ((cfg_msw & ASC_CFG_MSW_CLR_MASK) != 0) {
		cfg_msw &= ~ASC_CFG_MSW_CLR_MASK;
		warn_code |= ASC_WARN_CFG_MSW_RECOVER;
		AscSetChipCfgMsw(iop_base, cfg_msw);
	}
	chksum = AscGetEEPConfig(iop_base, eep_config, asc_dvc->bus_type);
	ASC_DBG(1, "chksum 0x%x\n", chksum);
	if (chksum == 0) {
		chksum = 0xaa55;
	}
	if (AscGetChipStatus(iop_base) & CSW_AUTO_CONFIG) {
		warn_code |= ASC_WARN_AUTO_CONFIG;
		if (asc_dvc->cfg->chip_version == 3) {
			if (eep_config->cfg_lsw != cfg_lsw) {
				warn_code |= ASC_WARN_EEPROM_RECOVER;
				eep_config->cfg_lsw =
				    AscGetChipCfgLsw(iop_base);
			}
			if (eep_config->cfg_msw != cfg_msw) {
				warn_code |= ASC_WARN_EEPROM_RECOVER;
				eep_config->cfg_msw =
				    AscGetChipCfgMsw(iop_base);
			}
		}
	}
	eep_config->cfg_msw &= ~ASC_CFG_MSW_CLR_MASK;
	eep_config->cfg_lsw |= ASC_CFG0_HOST_INT_ON;
	ASC_DBG(1, "eep_config->chksum 0x%x\n", eep_config->chksum);
	if (chksum != eep_config->chksum) {
		if (AscGetChipVersion(iop_base, asc_dvc->bus_type) ==
		    ASC_CHIP_VER_PCI_ULTRA_3050) {
			ASC_DBG(1, "chksum error ignored; EEPROM-less board\n");
			eep_config->init_sdtr = 0xFF;
			eep_config->disc_enable = 0xFF;
			eep_config->start_motor = 0xFF;
			eep_config->use_cmd_qng = 0;
			eep_config->max_total_qng = 0xF0;
			eep_config->max_tag_qng = 0x20;
			eep_config->cntl = 0xBFFF;
			ASC_EEP_SET_CHIP_ID(eep_config, 7);
			eep_config->no_scam = 0;
			eep_config->adapter_info[0] = 0;
			eep_config->adapter_info[1] = 0;
			eep_config->adapter_info[2] = 0;
			eep_config->adapter_info[3] = 0;
			eep_config->adapter_info[4] = 0;
			/* Indicate EEPROM-less board. */
			eep_config->adapter_info[5] = 0xBB;
		} else {
			ASC_PRINT
			    ("AscInitFromEEP: EEPROM checksum error; Will try to re-write EEPROM.\n");
			write_eep = 1;
			warn_code |= ASC_WARN_EEPROM_CHKSUM;
		}
	}
	asc_dvc->cfg->sdtr_enable = eep_config->init_sdtr;
	asc_dvc->cfg->disc_enable = eep_config->disc_enable;
	asc_dvc->cfg->cmd_qng_enabled = eep_config->use_cmd_qng;
	asc_dvc->cfg->isa_dma_speed = ASC_EEP_GET_DMA_SPD(eep_config);
	asc_dvc->start_motor = eep_config->start_motor;
	asc_dvc->dvc_cntl = eep_config->cntl;
	asc_dvc->no_scam = eep_config->no_scam;
	asc_dvc->cfg->adapter_info[0] = eep_config->adapter_info[0];
	asc_dvc->cfg->adapter_info[1] = eep_config->adapter_info[1];
	asc_dvc->cfg->adapter_info[2] = eep_config->adapter_info[2];
	asc_dvc->cfg->adapter_info[3] = eep_config->adapter_info[3];
	asc_dvc->cfg->adapter_info[4] = eep_config->adapter_info[4];
	asc_dvc->cfg->adapter_info[5] = eep_config->adapter_info[5];
	if (!AscTestExternalLram(asc_dvc)) {
		if (((asc_dvc->bus_type & ASC_IS_PCI_ULTRA) ==
		     ASC_IS_PCI_ULTRA)) {
			eep_config->max_total_qng =
			    ASC_MAX_PCI_ULTRA_INRAM_TOTAL_QNG;
			eep_config->max_tag_qng =
			    ASC_MAX_PCI_ULTRA_INRAM_TAG_QNG;
		} else {
			eep_config->cfg_msw |= 0x0800;
			cfg_msw |= 0x0800;
			AscSetChipCfgMsw(iop_base, cfg_msw);
			eep_config->max_total_qng = ASC_MAX_PCI_INRAM_TOTAL_QNG;
			eep_config->max_tag_qng = ASC_MAX_INRAM_TAG_QNG;
		}
	} else {
	}
	if (eep_config->max_total_qng < ASC_MIN_TOTAL_QNG) {
		eep_config->max_total_qng = ASC_MIN_TOTAL_QNG;
	}
	if (eep_config->max_total_qng > ASC_MAX_TOTAL_QNG) {
		eep_config->max_total_qng = ASC_MAX_TOTAL_QNG;
	}
	if (eep_config->max_tag_qng > eep_config->max_total_qng) {
		eep_config->max_tag_qng = eep_config->max_total_qng;
	}
	if (eep_config->max_tag_qng < ASC_MIN_TAG_Q_PER_DVC) {
		eep_config->max_tag_qng = ASC_MIN_TAG_Q_PER_DVC;
	}
	asc_dvc->max_total_qng = eep_config->max_total_qng;
	if ((eep_config->use_cmd_qng & eep_config->disc_enable) !=
	    eep_config->use_cmd_qng) {
		eep_config->disc_enable = eep_config->use_cmd_qng;
		warn_code |= ASC_WARN_CMD_QNG_CONFLICT;
	}
	ASC_EEP_SET_CHIP_ID(eep_config,
			    ASC_EEP_GET_CHIP_ID(eep_config) & ASC_MAX_TID);
	asc_dvc->cfg->chip_scsi_id = ASC_EEP_GET_CHIP_ID(eep_config);
	if (((asc_dvc->bus_type & ASC_IS_PCI_ULTRA) == ASC_IS_PCI_ULTRA) &&
	    !(asc_dvc->dvc_cntl & ASC_CNTL_SDTR_ENABLE_ULTRA)) {
		asc_dvc->min_sdtr_index = ASC_SDTR_ULTRA_PCI_10MB_INDEX;
	}

	for (i = 0; i <= ASC_MAX_TID; i++) {
		asc_dvc->dos_int13_table[i] = eep_config->dos_int13_table[i];
		asc_dvc->cfg->max_tag_qng[i] = eep_config->max_tag_qng;
		asc_dvc->cfg->sdtr_period_offset[i] =
		    (uchar)(ASC_DEF_SDTR_OFFSET |
			    (asc_dvc->min_sdtr_index << 4));
	}
	eep_config->cfg_msw = AscGetChipCfgMsw(iop_base);
	if (write_eep) {
		if ((i = AscSetEEPConfig(iop_base, eep_config,
				     asc_dvc->bus_type)) != 0) {
			ASC_PRINT1
			    ("AscInitFromEEP: Failed to re-write EEPROM with %d errors.\n",
			     i);
		} else {
			ASC_PRINT
			    ("AscInitFromEEP: Successfully re-wrote EEPROM.\n");
		}
	}
	return (warn_code);
}