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
typedef  int u32 ;
struct TYPE_4__ {int Cnt_Fast_Fsync; int Cnt_SB_Search_fail; int Cnt_OFDM_CCA; int Cnt_Parity_Fail; int Cnt_Rate_Illegal; int Cnt_Crc8_fail; int Cnt_Mcs_fail; int Cnt_Ofdm_fail; int Cnt_Cck_fail; int Cnt_CCK_CCA; int Cnt_all; int Cnt_CCA_all; } ;
struct TYPE_5__ {int SupportAbility; int /*<<< orphan*/  Adapter; TYPE_1__ FalseAlmCnt; } ;
typedef  TYPE_1__* Pfalse_ALARM_STATISTICS ;
typedef  TYPE_2__* PDM_ODM_T ;

/* Variables and functions */
 int /*<<< orphan*/  BIT12 ; 
 int /*<<< orphan*/  BIT14 ; 
 int /*<<< orphan*/  BIT31 ; 
 int ODM_BB_FA_CNT ; 
 int /*<<< orphan*/  ODM_COMP_FA_CNT ; 
 int /*<<< orphan*/  ODM_DBG_LOUD ; 
 int /*<<< orphan*/  ODM_REG_CCK_CCA_CNT_11N ; 
 int /*<<< orphan*/  ODM_REG_CCK_FA_LSB_11N ; 
 int /*<<< orphan*/  ODM_REG_CCK_FA_MSB_11N ; 
 int /*<<< orphan*/  ODM_REG_CCK_FA_RST_11N ; 
 int /*<<< orphan*/  ODM_REG_OFDM_FA_HOLDC_11N ; 
 int /*<<< orphan*/  ODM_REG_OFDM_FA_RSTD_11N ; 
 int /*<<< orphan*/  ODM_REG_OFDM_FA_TYPE1_11N ; 
 int /*<<< orphan*/  ODM_REG_OFDM_FA_TYPE2_11N ; 
 int /*<<< orphan*/  ODM_REG_OFDM_FA_TYPE3_11N ; 
 int /*<<< orphan*/  ODM_REG_OFDM_FA_TYPE4_11N ; 
 int /*<<< orphan*/  ODM_RT_TRACE (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int PHY_QueryBBReg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_SetBBReg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bMaskByte0 ; 
 int /*<<< orphan*/  bMaskByte3 ; 
 int /*<<< orphan*/  bMaskDWord ; 

void odm_FalseAlarmCounterStatistics(void *pDM_VOID)
{
	PDM_ODM_T pDM_Odm = (PDM_ODM_T)pDM_VOID;
	Pfalse_ALARM_STATISTICS FalseAlmCnt = &(pDM_Odm->FalseAlmCnt);
	u32 ret_value;

	if (!(pDM_Odm->SupportAbility & ODM_BB_FA_CNT))
		return;

	/* hold ofdm counter */
	/* hold page C counter */
	PHY_SetBBReg(pDM_Odm->Adapter, ODM_REG_OFDM_FA_HOLDC_11N, BIT31, 1);
	/* hold page D counter */
	PHY_SetBBReg(pDM_Odm->Adapter, ODM_REG_OFDM_FA_RSTD_11N, BIT31, 1);

	ret_value = PHY_QueryBBReg(
		pDM_Odm->Adapter, ODM_REG_OFDM_FA_TYPE1_11N, bMaskDWord
	);
	FalseAlmCnt->Cnt_Fast_Fsync = (ret_value&0xffff);
	FalseAlmCnt->Cnt_SB_Search_fail = ((ret_value&0xffff0000)>>16);

	ret_value = PHY_QueryBBReg(
		pDM_Odm->Adapter, ODM_REG_OFDM_FA_TYPE2_11N, bMaskDWord
	);
	FalseAlmCnt->Cnt_OFDM_CCA = (ret_value&0xffff);
	FalseAlmCnt->Cnt_Parity_Fail = ((ret_value&0xffff0000)>>16);

	ret_value = PHY_QueryBBReg(
		pDM_Odm->Adapter, ODM_REG_OFDM_FA_TYPE3_11N, bMaskDWord
	);
	FalseAlmCnt->Cnt_Rate_Illegal = (ret_value&0xffff);
	FalseAlmCnt->Cnt_Crc8_fail = ((ret_value&0xffff0000)>>16);

	ret_value = PHY_QueryBBReg(
		pDM_Odm->Adapter, ODM_REG_OFDM_FA_TYPE4_11N, bMaskDWord
	);
	FalseAlmCnt->Cnt_Mcs_fail = (ret_value&0xffff);

	FalseAlmCnt->Cnt_Ofdm_fail =
		FalseAlmCnt->Cnt_Parity_Fail +
		FalseAlmCnt->Cnt_Rate_Illegal +
		FalseAlmCnt->Cnt_Crc8_fail +
		FalseAlmCnt->Cnt_Mcs_fail +
		FalseAlmCnt->Cnt_Fast_Fsync +
		FalseAlmCnt->Cnt_SB_Search_fail;

	{
		/* hold cck counter */
		PHY_SetBBReg(pDM_Odm->Adapter, ODM_REG_CCK_FA_RST_11N, BIT12, 1);
		PHY_SetBBReg(pDM_Odm->Adapter, ODM_REG_CCK_FA_RST_11N, BIT14, 1);

		ret_value = PHY_QueryBBReg(
			pDM_Odm->Adapter, ODM_REG_CCK_FA_LSB_11N, bMaskByte0
		);
		FalseAlmCnt->Cnt_Cck_fail = ret_value;

		ret_value = PHY_QueryBBReg(
			pDM_Odm->Adapter, ODM_REG_CCK_FA_MSB_11N, bMaskByte3
		);
		FalseAlmCnt->Cnt_Cck_fail += (ret_value&0xff)<<8;

		ret_value = PHY_QueryBBReg(
			pDM_Odm->Adapter, ODM_REG_CCK_CCA_CNT_11N, bMaskDWord
		);
		FalseAlmCnt->Cnt_CCK_CCA =
			((ret_value&0xFF)<<8) | ((ret_value&0xFF00)>>8);
	}

	FalseAlmCnt->Cnt_all = (
		FalseAlmCnt->Cnt_Fast_Fsync +
		FalseAlmCnt->Cnt_SB_Search_fail +
		FalseAlmCnt->Cnt_Parity_Fail +
		FalseAlmCnt->Cnt_Rate_Illegal +
		FalseAlmCnt->Cnt_Crc8_fail +
		FalseAlmCnt->Cnt_Mcs_fail +
		FalseAlmCnt->Cnt_Cck_fail
	);

	FalseAlmCnt->Cnt_CCA_all =
		FalseAlmCnt->Cnt_OFDM_CCA + FalseAlmCnt->Cnt_CCK_CCA;

	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_FA_CNT,
		ODM_DBG_LOUD,
		("Enter odm_FalseAlarmCounterStatistics\n")
	);
	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_FA_CNT,
		ODM_DBG_LOUD,
		(
			"Cnt_Fast_Fsync =%d, Cnt_SB_Search_fail =%d\n",
			FalseAlmCnt->Cnt_Fast_Fsync,
			FalseAlmCnt->Cnt_SB_Search_fail
		)
	);
	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_FA_CNT,
		ODM_DBG_LOUD,
		(
			"Cnt_Parity_Fail =%d, Cnt_Rate_Illegal =%d\n",
			FalseAlmCnt->Cnt_Parity_Fail,
			FalseAlmCnt->Cnt_Rate_Illegal
		)
	);
	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_FA_CNT,
		ODM_DBG_LOUD,
		(
			"Cnt_Crc8_fail =%d, Cnt_Mcs_fail =%d\n",
			FalseAlmCnt->Cnt_Crc8_fail,
			FalseAlmCnt->Cnt_Mcs_fail
		)
	);

	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_FA_CNT,
		ODM_DBG_LOUD,
		("Cnt_OFDM_CCA =%d\n", FalseAlmCnt->Cnt_OFDM_CCA)
	);
	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_FA_CNT,
		ODM_DBG_LOUD,
		("Cnt_CCK_CCA =%d\n", FalseAlmCnt->Cnt_CCK_CCA)
	);
	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_FA_CNT,
		ODM_DBG_LOUD,
		("Cnt_CCA_all =%d\n", FalseAlmCnt->Cnt_CCA_all)
	);
	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_FA_CNT,
		ODM_DBG_LOUD,
		("Cnt_Ofdm_fail =%d\n",	FalseAlmCnt->Cnt_Ofdm_fail)
	);
	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_FA_CNT,
		ODM_DBG_LOUD,
		("Cnt_Cck_fail =%d\n",	FalseAlmCnt->Cnt_Cck_fail)
	);
	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_FA_CNT,
		ODM_DBG_LOUD,
		("Cnt_Ofdm_fail =%d\n",	FalseAlmCnt->Cnt_Ofdm_fail)
	);
	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_FA_CNT,
		ODM_DBG_LOUD,
		("Total False Alarm =%d\n",	FalseAlmCnt->Cnt_all)
	);
}