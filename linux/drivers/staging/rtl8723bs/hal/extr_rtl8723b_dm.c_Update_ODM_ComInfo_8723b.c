#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct pwrctrl_priv {int /*<<< orphan*/  bpower_saving; } ;
struct mlme_priv {int /*<<< orphan*/  bScanInProcess; } ;
struct mlme_ext_priv {int /*<<< orphan*/  cur_wireless_mode; } ;
struct dm_priv {int InitODMFlag; } ;
struct hal_com_data {int /*<<< orphan*/  ForcedDataRate; int /*<<< orphan*/  u1ForcedIgiLb; int /*<<< orphan*/  CurrentBandType; int /*<<< orphan*/  CurrentChannel; int /*<<< orphan*/  CurrentChannelBW; int /*<<< orphan*/  nCur40MhzPrimeSC; struct dm_priv dmpriv; int /*<<< orphan*/  odmpriv; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_bytes; } ;
struct dvobj_priv {TYPE_1__ traffic_stat; } ;
struct TYPE_4__ {int /*<<< orphan*/  dot11PrivacyAlgrthm; } ;
struct adapter {int /*<<< orphan*/  net_closed; TYPE_2__ securitypriv; struct mlme_priv mlmepriv; struct mlme_ext_priv mlmeextpriv; } ;
typedef  int /*<<< orphan*/ * PDM_ODM_T ;

/* Variables and functions */
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 int NUM_STA ; 
 int ODM_BB_ADAPTIVITY ; 
 int ODM_BB_CCK_PD ; 
 int ODM_BB_CFO_TRACKING ; 
 int ODM_BB_DIG ; 
 int ODM_BB_DYNAMIC_TXPWR ; 
 int ODM_BB_FA_CNT ; 
 int ODM_BB_PWR_SAVE ; 
 int ODM_BB_RA_MASK ; 
 int ODM_BB_RSSI_MONITOR ; 
 int /*<<< orphan*/  ODM_CMNINFO_ABILITY ; 
 int /*<<< orphan*/  ODM_CMNINFO_BAND ; 
 int /*<<< orphan*/  ODM_CMNINFO_BW ; 
 int /*<<< orphan*/  ODM_CMNINFO_CHNL ; 
 int /*<<< orphan*/  ODM_CMNINFO_FORCED_IGI_LB ; 
 int /*<<< orphan*/  ODM_CMNINFO_FORCED_RATE ; 
 int /*<<< orphan*/  ODM_CMNINFO_MP_MODE ; 
 int /*<<< orphan*/  ODM_CMNINFO_NET_CLOSED ; 
 int /*<<< orphan*/  ODM_CMNINFO_POWER_SAVING ; 
 int /*<<< orphan*/  ODM_CMNINFO_RX_UNI ; 
 int /*<<< orphan*/  ODM_CMNINFO_SCAN ; 
 int /*<<< orphan*/  ODM_CMNINFO_SEC_CHNL_OFFSET ; 
 int /*<<< orphan*/  ODM_CMNINFO_SEC_MODE ; 
 int /*<<< orphan*/  ODM_CMNINFO_STA_STATUS ; 
 int /*<<< orphan*/  ODM_CMNINFO_TX_UNI ; 
 int /*<<< orphan*/  ODM_CMNINFO_WM_MODE ; 
 int /*<<< orphan*/  ODM_CmnInfoHook (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ODM_CmnInfoPtrArrayHook (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ODM_CmnInfoUpdate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int ODM_MAC_EDCA_TURBO ; 
 int ODM_RF_CALIBRATION ; 
 int ODM_RF_TX_PWR_TRACK ; 
 struct dvobj_priv* adapter_to_dvobj (struct adapter*) ; 
 struct pwrctrl_priv* adapter_to_pwrctl (struct adapter*) ; 

__attribute__((used)) static void Update_ODM_ComInfo_8723b(struct adapter *Adapter)
{
	struct mlme_ext_priv *pmlmeext = &Adapter->mlmeextpriv;
	struct mlme_priv *pmlmepriv = &Adapter->mlmepriv;
	struct dvobj_priv *dvobj = adapter_to_dvobj(Adapter);
	struct pwrctrl_priv *pwrctrlpriv = adapter_to_pwrctl(Adapter);
	struct hal_com_data *pHalData = GET_HAL_DATA(Adapter);
	PDM_ODM_T pDM_Odm = &(pHalData->odmpriv);
	struct dm_priv *pdmpriv = &pHalData->dmpriv;
	int i;
	u8 zero = 0;

	pdmpriv->InitODMFlag = 0
		| ODM_BB_DIG
		| ODM_BB_RA_MASK
		| ODM_BB_DYNAMIC_TXPWR
		| ODM_BB_FA_CNT
		| ODM_BB_RSSI_MONITOR
		| ODM_BB_CCK_PD
		| ODM_BB_PWR_SAVE
		| ODM_BB_CFO_TRACKING
		| ODM_MAC_EDCA_TURBO
		| ODM_RF_TX_PWR_TRACK
		| ODM_RF_CALIBRATION
#ifdef CONFIG_ODM_ADAPTIVITY
		| ODM_BB_ADAPTIVITY
#endif
		;

	/*  */
	/*  Pointer reference */
	/*  */
	/* ODM_CMNINFO_MAC_PHY_MODE pHalData->MacPhyMode92D */
	/* 	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_MAC_PHY_MODE,&(pDM_Odm->u8_temp)); */

	ODM_CmnInfoUpdate(pDM_Odm, ODM_CMNINFO_ABILITY, pdmpriv->InitODMFlag);

	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_TX_UNI, &(dvobj->traffic_stat.tx_bytes));
	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_RX_UNI, &(dvobj->traffic_stat.rx_bytes));
	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_WM_MODE, &(pmlmeext->cur_wireless_mode));
	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_SEC_CHNL_OFFSET, &(pHalData->nCur40MhzPrimeSC));
	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_SEC_MODE, &(Adapter->securitypriv.dot11PrivacyAlgrthm));
	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_BW, &(pHalData->CurrentChannelBW));
	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_CHNL, &(pHalData->CurrentChannel));
	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_NET_CLOSED, &(Adapter->net_closed));
	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_MP_MODE, &zero);
	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_BAND, &(pHalData->CurrentBandType));
	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_FORCED_IGI_LB, &(pHalData->u1ForcedIgiLb));
	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_FORCED_RATE, &(pHalData->ForcedDataRate));

	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_SCAN, &(pmlmepriv->bScanInProcess));
	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_POWER_SAVING, &(pwrctrlpriv->bpower_saving));


	for (i = 0; i < NUM_STA; i++)
		ODM_CmnInfoPtrArrayHook(pDM_Odm, ODM_CMNINFO_STA_STATUS, i, NULL);
}