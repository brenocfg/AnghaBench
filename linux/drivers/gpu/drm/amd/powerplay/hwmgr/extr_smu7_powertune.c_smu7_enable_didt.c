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
struct pp_hwmgr {scalar_t__ chip_id; int /*<<< orphan*/  device; } ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CGS_IND_REG__DIDT ; 
 int /*<<< orphan*/  CGS_WREG32_FIELD_IND (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ CHIP_POLARIS11 ; 
 int DB_Enable_MASK ; 
 int DB_Enable_SHIFT ; 
 int DIDTBlock_Info ; 
 int /*<<< orphan*/  DIDT_CTRL_EN ; 
 int /*<<< orphan*/  DIDT_DB_CTRL0 ; 
 int /*<<< orphan*/  DIDT_SQ_CTRL0 ; 
 int /*<<< orphan*/  DIDT_TCP_CTRL0 ; 
 int /*<<< orphan*/  DIDT_TD_CTRL0 ; 
 int /*<<< orphan*/  PHM_PlatformCaps_DBRamping ; 
 int /*<<< orphan*/  PHM_PlatformCaps_SQRamping ; 
 int /*<<< orphan*/  PHM_PlatformCaps_TCPRamping ; 
 int /*<<< orphan*/  PHM_PlatformCaps_TDRamping ; 
 int /*<<< orphan*/  PPSMC_MSG_Didt_Block_Function ; 
 scalar_t__ PP_CAP (int /*<<< orphan*/ ) ; 
 int Polaris11_DIDTBlock_Info ; 
 int SQ_Enable_MASK ; 
 int SQ_Enable_SHIFT ; 
 int TCP_Enable_MASK ; 
 int TCP_Enable_SHIFT ; 
 int TD_Enable_MASK ; 
 int TD_Enable_SHIFT ; 
 int smum_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int smu7_enable_didt(struct pp_hwmgr *hwmgr, const bool enable)
{
	uint32_t en = enable ? 1 : 0;
	uint32_t block_en = 0;
	int32_t result = 0;
	uint32_t didt_block;

	if (hwmgr->chip_id == CHIP_POLARIS11)
		didt_block = Polaris11_DIDTBlock_Info;
	else
		didt_block = DIDTBlock_Info;

	block_en = PP_CAP(PHM_PlatformCaps_SQRamping) ? en : 0;
	CGS_WREG32_FIELD_IND(hwmgr->device, CGS_IND_REG__DIDT,
			     DIDT_SQ_CTRL0, DIDT_CTRL_EN, block_en);
	didt_block &= ~SQ_Enable_MASK;
	didt_block |= block_en << SQ_Enable_SHIFT;

	block_en = PP_CAP(PHM_PlatformCaps_DBRamping) ? en : 0;
	CGS_WREG32_FIELD_IND(hwmgr->device, CGS_IND_REG__DIDT,
			     DIDT_DB_CTRL0, DIDT_CTRL_EN, block_en);
	didt_block &= ~DB_Enable_MASK;
	didt_block |= block_en << DB_Enable_SHIFT;

	block_en = PP_CAP(PHM_PlatformCaps_TDRamping) ? en : 0;
	CGS_WREG32_FIELD_IND(hwmgr->device, CGS_IND_REG__DIDT,
			     DIDT_TD_CTRL0, DIDT_CTRL_EN, block_en);
	didt_block &= ~TD_Enable_MASK;
	didt_block |= block_en << TD_Enable_SHIFT;

	block_en = PP_CAP(PHM_PlatformCaps_TCPRamping) ? en : 0;
	CGS_WREG32_FIELD_IND(hwmgr->device, CGS_IND_REG__DIDT,
			     DIDT_TCP_CTRL0, DIDT_CTRL_EN, block_en);
	didt_block &= ~TCP_Enable_MASK;
	didt_block |= block_en << TCP_Enable_SHIFT;

	if (enable)
		result = smum_send_msg_to_smc_with_parameter(hwmgr, PPSMC_MSG_Didt_Block_Function, didt_block);

	return result;
}