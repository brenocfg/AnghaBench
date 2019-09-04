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
typedef  int uint32_t ;
struct pp_hwmgr {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGS_IND_REG__DIDT ; 
 int /*<<< orphan*/  CGS_WREG32_FIELD_IND (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int DB_Enable_MASK ; 
 int DB_Enable_SHIFT ; 
 int /*<<< orphan*/  DIDT_CTRL_EN ; 
 int /*<<< orphan*/  DIDT_DBR_CTRL0 ; 
 int /*<<< orphan*/  DIDT_DBR_EDC_CTRL ; 
 int /*<<< orphan*/  DIDT_DB_CTRL0 ; 
 int /*<<< orphan*/  DIDT_DB_EDC_CTRL ; 
 int /*<<< orphan*/  DIDT_SQ_CTRL0 ; 
 int /*<<< orphan*/  DIDT_SQ_EDC_CTRL ; 
 int /*<<< orphan*/  DIDT_TCP_CTRL0 ; 
 int /*<<< orphan*/  DIDT_TCP_EDC_CTRL ; 
 int /*<<< orphan*/  DIDT_TD_CTRL0 ; 
 int /*<<< orphan*/  DIDT_TD_EDC_CTRL ; 
 int /*<<< orphan*/  EDC_EN ; 
 int /*<<< orphan*/  EDC_SW_RST ; 
 int /*<<< orphan*/  PHM_PlatformCaps_DBRRamping ; 
 int /*<<< orphan*/  PHM_PlatformCaps_DBRamping ; 
 int /*<<< orphan*/  PHM_PlatformCaps_DiDtEDCEnable ; 
 int /*<<< orphan*/  PHM_PlatformCaps_SQRamping ; 
 int /*<<< orphan*/  PHM_PlatformCaps_TCPRamping ; 
 int /*<<< orphan*/  PHM_PlatformCaps_TDRamping ; 
 int /*<<< orphan*/  PPSMC_MSG_ConfigureGfxDidt ; 
 scalar_t__ PP_CAP (int /*<<< orphan*/ ) ; 
 int REG_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int SQ_Enable_MASK ; 
 int SQ_Enable_SHIFT ; 
 int SQ_IR_MASK ; 
 int TCP_Enable_MASK ; 
 int TCP_Enable_SHIFT ; 
 int TCP_IR_MASK ; 
 int TD_Enable_MASK ; 
 int TD_Enable_SHIFT ; 
 int TD_PCC_MASK ; 
 int cgs_read_ind_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgs_write_ind_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ixDIDT_DBR_EDC_CTRL ; 
 int /*<<< orphan*/  ixDIDT_DB_EDC_CTRL ; 
 int /*<<< orphan*/  ixDIDT_SQ_EDC_CTRL ; 
 int /*<<< orphan*/  ixDIDT_TCP_EDC_CTRL ; 
 int /*<<< orphan*/  ixDIDT_TD_EDC_CTRL ; 
 int /*<<< orphan*/  smum_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vega10_didt_set_mask(struct pp_hwmgr *hwmgr, const bool enable)
{
	uint32_t data;
	uint32_t en = (enable ? 1 : 0);
	uint32_t didt_block_info = SQ_IR_MASK | TCP_IR_MASK | TD_PCC_MASK;

	if (PP_CAP(PHM_PlatformCaps_SQRamping)) {
		CGS_WREG32_FIELD_IND(hwmgr->device, CGS_IND_REG__DIDT,
				     DIDT_SQ_CTRL0, DIDT_CTRL_EN, en);
		didt_block_info &= ~SQ_Enable_MASK;
		didt_block_info |= en << SQ_Enable_SHIFT;
	}

	if (PP_CAP(PHM_PlatformCaps_DBRamping)) {
		CGS_WREG32_FIELD_IND(hwmgr->device, CGS_IND_REG__DIDT,
				     DIDT_DB_CTRL0, DIDT_CTRL_EN, en);
		didt_block_info &= ~DB_Enable_MASK;
		didt_block_info |= en << DB_Enable_SHIFT;
	}

	if (PP_CAP(PHM_PlatformCaps_TDRamping)) {
		CGS_WREG32_FIELD_IND(hwmgr->device, CGS_IND_REG__DIDT,
				     DIDT_TD_CTRL0, DIDT_CTRL_EN, en);
		didt_block_info &= ~TD_Enable_MASK;
		didt_block_info |= en << TD_Enable_SHIFT;
	}

	if (PP_CAP(PHM_PlatformCaps_TCPRamping)) {
		CGS_WREG32_FIELD_IND(hwmgr->device, CGS_IND_REG__DIDT,
				     DIDT_TCP_CTRL0, DIDT_CTRL_EN, en);
		didt_block_info &= ~TCP_Enable_MASK;
		didt_block_info |= en << TCP_Enable_SHIFT;
	}

	if (PP_CAP(PHM_PlatformCaps_DBRRamping)) {
		CGS_WREG32_FIELD_IND(hwmgr->device, CGS_IND_REG__DIDT,
				     DIDT_DBR_CTRL0, DIDT_CTRL_EN, en);
	}

	if (PP_CAP(PHM_PlatformCaps_DiDtEDCEnable)) {
		if (PP_CAP(PHM_PlatformCaps_SQRamping)) {
			data = cgs_read_ind_register(hwmgr->device, CGS_IND_REG__DIDT, ixDIDT_SQ_EDC_CTRL);
			data = REG_SET_FIELD(data, DIDT_SQ_EDC_CTRL, EDC_EN, en);
			data = REG_SET_FIELD(data, DIDT_SQ_EDC_CTRL, EDC_SW_RST, ~en);
			cgs_write_ind_register(hwmgr->device, CGS_IND_REG__DIDT, ixDIDT_SQ_EDC_CTRL, data);
		}

		if (PP_CAP(PHM_PlatformCaps_DBRamping)) {
			data = cgs_read_ind_register(hwmgr->device, CGS_IND_REG__DIDT, ixDIDT_DB_EDC_CTRL);
			data = REG_SET_FIELD(data, DIDT_DB_EDC_CTRL, EDC_EN, en);
			data = REG_SET_FIELD(data, DIDT_DB_EDC_CTRL, EDC_SW_RST, ~en);
			cgs_write_ind_register(hwmgr->device, CGS_IND_REG__DIDT, ixDIDT_DB_EDC_CTRL, data);
		}

		if (PP_CAP(PHM_PlatformCaps_TDRamping)) {
			data = cgs_read_ind_register(hwmgr->device, CGS_IND_REG__DIDT, ixDIDT_TD_EDC_CTRL);
			data = REG_SET_FIELD(data, DIDT_TD_EDC_CTRL, EDC_EN, en);
			data = REG_SET_FIELD(data, DIDT_TD_EDC_CTRL, EDC_SW_RST, ~en);
			cgs_write_ind_register(hwmgr->device, CGS_IND_REG__DIDT, ixDIDT_TD_EDC_CTRL, data);
		}

		if (PP_CAP(PHM_PlatformCaps_TCPRamping)) {
			data = cgs_read_ind_register(hwmgr->device, CGS_IND_REG__DIDT, ixDIDT_TCP_EDC_CTRL);
			data = REG_SET_FIELD(data, DIDT_TCP_EDC_CTRL, EDC_EN, en);
			data = REG_SET_FIELD(data, DIDT_TCP_EDC_CTRL, EDC_SW_RST, ~en);
			cgs_write_ind_register(hwmgr->device, CGS_IND_REG__DIDT, ixDIDT_TCP_EDC_CTRL, data);
		}

		if (PP_CAP(PHM_PlatformCaps_DBRRamping)) {
			data = cgs_read_ind_register(hwmgr->device, CGS_IND_REG__DIDT, ixDIDT_DBR_EDC_CTRL);
			data = REG_SET_FIELD(data, DIDT_DBR_EDC_CTRL, EDC_EN, en);
			data = REG_SET_FIELD(data, DIDT_DBR_EDC_CTRL, EDC_SW_RST, ~en);
			cgs_write_ind_register(hwmgr->device, CGS_IND_REG__DIDT, ixDIDT_DBR_EDC_CTRL, data);
		}
	}

	/* For Vega10, SMC does not support any mask yet. */
	if (enable)
		smum_send_msg_to_smc_with_parameter(hwmgr, PPSMC_MSG_ConfigureGfxDidt, didt_block_info);

}