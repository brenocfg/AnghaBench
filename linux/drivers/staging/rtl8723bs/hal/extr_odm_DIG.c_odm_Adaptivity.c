#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int s8 ;
struct TYPE_5__ {int SupportAbility; int IGI_Base; int TH_L2H_ini; int TH_EDCCA_HL_diff; int AdapEn_RSSI; scalar_t__* pBandWidth; int IGI_target; int TxHangFlg; int* pChannel; int RSSI_Min; int Carrier_Sense_enable; int NHM_disable; int H2L_lb; int L2H_lb; int /*<<< orphan*/  Adapter; scalar_t__ bLinked; int /*<<< orphan*/  ForceEDCCA; } ;
typedef  TYPE_1__* PDM_ODM_T ;

/* Variables and functions */
 int ODM_BB_ADAPTIVITY ; 
 scalar_t__ ODM_BW20M ; 
 scalar_t__ ODM_BW40M ; 
 scalar_t__ ODM_BW80M ; 
 int /*<<< orphan*/  ODM_COMP_DIG ; 
 int /*<<< orphan*/  ODM_DBG_LOUD ; 
 int /*<<< orphan*/  ODM_REG_DBG_RPT_11N ; 
 int /*<<< orphan*/  ODM_RT_TRACE (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PHY_SetBBReg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bMaskByte0 ; 
 int /*<<< orphan*/  bMaskByte2 ; 
 int /*<<< orphan*/  bMaskDWord ; 
 int /*<<< orphan*/  odm_NHMBB (TYPE_1__*) ; 
 int /*<<< orphan*/  odm_SearchPwdBLowerBound (TYPE_1__*,int) ; 
 int /*<<< orphan*/  rOFDM0_ECCAThreshold ; 

void odm_Adaptivity(void *pDM_VOID, u8 IGI)
{
	PDM_ODM_T pDM_Odm = (PDM_ODM_T)pDM_VOID;
	s8 TH_L2H_dmc, TH_H2L_dmc;
	s8 Diff, IGI_target;
	bool EDCCA_State = false;

	if (!(pDM_Odm->SupportAbility & ODM_BB_ADAPTIVITY)) {
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("Go to odm_DynamicEDCCA()\n"));
		return;
	}
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("odm_Adaptivity() =====>\n"));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("ForceEDCCA =%d, IGI_Base = 0x%x, TH_L2H_ini = %d, TH_EDCCA_HL_diff = %d, AdapEn_RSSI = %d\n",
		pDM_Odm->ForceEDCCA, pDM_Odm->IGI_Base, pDM_Odm->TH_L2H_ini, pDM_Odm->TH_EDCCA_HL_diff, pDM_Odm->AdapEn_RSSI));

	if (*pDM_Odm->pBandWidth == ODM_BW20M) /* CHANNEL_WIDTH_20 */
		IGI_target = pDM_Odm->IGI_Base;
	else if (*pDM_Odm->pBandWidth == ODM_BW40M)
		IGI_target = pDM_Odm->IGI_Base + 2;
	else if (*pDM_Odm->pBandWidth == ODM_BW80M)
		IGI_target = pDM_Odm->IGI_Base + 2;
	else
		IGI_target = pDM_Odm->IGI_Base;
	pDM_Odm->IGI_target = (u8) IGI_target;

	/* Search pwdB lower bound */
	if (pDM_Odm->TxHangFlg == true) {
		PHY_SetBBReg(pDM_Odm->Adapter, ODM_REG_DBG_RPT_11N, bMaskDWord, 0x208);
		odm_SearchPwdBLowerBound(pDM_Odm, pDM_Odm->IGI_target);
	}

	if ((!pDM_Odm->bLinked) || (*pDM_Odm->pChannel > 149)) { /*  Band4 doesn't need adaptivity */
		PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_ECCAThreshold, bMaskByte0, 0x7f);
		PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_ECCAThreshold, bMaskByte2, 0x7f);
		return;
	}

	if (!pDM_Odm->ForceEDCCA) {
		if (pDM_Odm->RSSI_Min > pDM_Odm->AdapEn_RSSI)
			EDCCA_State = true;
		else if (pDM_Odm->RSSI_Min < (pDM_Odm->AdapEn_RSSI - 5))
			EDCCA_State = false;
	} else
		EDCCA_State = true;

	if (
		pDM_Odm->bLinked &&
		pDM_Odm->Carrier_Sense_enable == false &&
		pDM_Odm->NHM_disable == false &&
		pDM_Odm->TxHangFlg == false
	)
		odm_NHMBB(pDM_Odm);

	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_DIG,
		ODM_DBG_LOUD,
		(
			"BandWidth =%s, IGI_target = 0x%x, EDCCA_State =%d\n",
			(*pDM_Odm->pBandWidth == ODM_BW80M) ? "80M" :
			((*pDM_Odm->pBandWidth == ODM_BW40M) ? "40M" : "20M"),
			IGI_target,
			EDCCA_State
		)
	);

	if (EDCCA_State) {
		Diff = IGI_target-(s8)IGI;
		TH_L2H_dmc = pDM_Odm->TH_L2H_ini + Diff;
		if (TH_L2H_dmc > 10)
			TH_L2H_dmc = 10;

		TH_H2L_dmc = TH_L2H_dmc - pDM_Odm->TH_EDCCA_HL_diff;

		/* replace lower bound to prevent EDCCA always equal  */
		if (TH_H2L_dmc < pDM_Odm->H2L_lb)
			TH_H2L_dmc = pDM_Odm->H2L_lb;
		if (TH_L2H_dmc < pDM_Odm->L2H_lb)
			TH_L2H_dmc = pDM_Odm->L2H_lb;
	} else {
		TH_L2H_dmc = 0x7f;
		TH_H2L_dmc = 0x7f;
	}
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("IGI = 0x%x, TH_L2H_dmc = %d, TH_H2L_dmc = %d\n",
		IGI, TH_L2H_dmc, TH_H2L_dmc));
	PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_ECCAThreshold, bMaskByte0, (u8)TH_L2H_dmc);
	PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_ECCAThreshold, bMaskByte2, (u8)TH_H2L_dmc);
}