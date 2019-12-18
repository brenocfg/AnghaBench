#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct mlme_ext_priv {int cur_channel; int /*<<< orphan*/  cur_wireless_mode; } ;
struct hal_com_data {int CurrentBandType; int FirmwareVersion; int FirmwareSubVersion; int CurrentChannel; int /*<<< orphan*/  CurrentChannelBW; } ;
struct TYPE_13__ {int /*<<< orphan*/  NumRxOkInPeriod; int /*<<< orphan*/  NumTxOkInPeriod; } ;
struct TYPE_15__ {TYPE_4__ LinkDetectInfo; } ;
struct TYPE_10__ {int /*<<< orphan*/  dot11PrivacyAlgrthm; } ;
struct adapter {TYPE_3__* dvobj; struct mlme_ext_priv mlmeextpriv; TYPE_9__ mlmepriv; TYPE_1__ securitypriv; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_14__ {struct adapter* Adapter; } ;
struct TYPE_11__ {int pwr_mode; } ;
struct TYPE_12__ {TYPE_2__ pwrctl_priv; } ;
typedef  TYPE_4__* PRT_LINK_DETECT_T ;
typedef  TYPE_5__* PBTC_COEXIST ;

/* Variables and functions */
#define  BTC_GET_BL_EXT_SWITCH 154 
#define  BTC_GET_BL_HS_CONNECTING 153 
#define  BTC_GET_BL_HS_OPERATION 152 
#define  BTC_GET_BL_WIFI_4_WAY_PROGRESS 151 
#define  BTC_GET_BL_WIFI_AP_MODE_ENABLE 150 
#define  BTC_GET_BL_WIFI_BUSY 149 
#define  BTC_GET_BL_WIFI_CONNECTED 148 
#define  BTC_GET_BL_WIFI_ENABLE_ENCRYPTION 147 
#define  BTC_GET_BL_WIFI_IS_IN_MP_MODE 146 
#define  BTC_GET_BL_WIFI_LINK 145 
#define  BTC_GET_BL_WIFI_ROAM 144 
#define  BTC_GET_BL_WIFI_SCAN 143 
#define  BTC_GET_BL_WIFI_UNDER_5G 142 
#define  BTC_GET_BL_WIFI_UNDER_B_MODE 141 
#define  BTC_GET_S4_HS_RSSI 140 
#define  BTC_GET_S4_WIFI_RSSI 139 
#define  BTC_GET_U1_AP_NUM 138 
#define  BTC_GET_U1_LPS_MODE 137 
#define  BTC_GET_U1_MAC_PHY_MODE 136 
#define  BTC_GET_U1_WIFI_CENTRAL_CHNL 135 
#define  BTC_GET_U1_WIFI_DOT11_CHNL 134 
#define  BTC_GET_U1_WIFI_HS_CHNL 133 
#define  BTC_GET_U4_BT_PATCH_VER 132 
#define  BTC_GET_U4_WIFI_BW 131 
#define  BTC_GET_U4_WIFI_FW_VER 130 
#define  BTC_GET_U4_WIFI_LINK_STATUS 129 
#define  BTC_GET_U4_WIFI_TRAFFIC_DIRECTION 128 
 int BTC_SMSP ; 
 int BTC_WIFI_BW_HT20 ; 
 int BTC_WIFI_BW_HT40 ; 
 int BTC_WIFI_BW_LEGACY ; 
 int BTC_WIFI_TRAFFIC_RX ; 
 int BTC_WIFI_TRAFFIC_TX ; 
 int /*<<< orphan*/  CHANNEL_WIDTH_20 ; 
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 int GLBtcWiFiInScanState ; 
 int /*<<< orphan*/  IsLegacyOnly (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIFI_AP_STATE ; 
 int /*<<< orphan*/  WIFI_ASOC_STATE ; 
 int /*<<< orphan*/  WIFI_UNDER_LINKING ; 
 int /*<<< orphan*/  WIRELESS_11B ; 
 int check_fwstate (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int halbtcoutsrc_GetBtPatchVer (TYPE_5__*) ; 
 int halbtcoutsrc_GetWifiLinkStatus (TYPE_5__*) ; 
 int /*<<< orphan*/  halbtcoutsrc_GetWifiRssi (struct adapter*) ; 
 int halbtcoutsrc_GetWifiScanAPNum (struct adapter*) ; 
 int /*<<< orphan*/  halbtcoutsrc_IsBtCoexistAvailable (TYPE_5__*) ; 
 int halbtcoutsrc_IsWifiBusy (struct adapter*) ; 

__attribute__((used)) static u8 halbtcoutsrc_Get(void *pBtcContext, u8 getType, void *pOutBuf)
{
	PBTC_COEXIST pBtCoexist;
	struct adapter *padapter;
	struct hal_com_data *pHalData;
	struct mlme_ext_priv *mlmeext;
	u8 *pu8;
	s32 *pS4Tmp;
	u32 *pU4Tmp;
	u8 ret;


	pBtCoexist = (PBTC_COEXIST)pBtcContext;
	if (!halbtcoutsrc_IsBtCoexistAvailable(pBtCoexist))
		return false;

	padapter = pBtCoexist->Adapter;
	pHalData = GET_HAL_DATA(padapter);
	mlmeext = &padapter->mlmeextpriv;
	pu8 = pOutBuf;
	pS4Tmp = pOutBuf;
	pU4Tmp = pOutBuf;
	ret = true;

	switch (getType) {
	case BTC_GET_BL_HS_OPERATION:
		*pu8 = false;
		ret = false;
		break;

	case BTC_GET_BL_HS_CONNECTING:
		*pu8 = false;
		ret = false;
		break;

	case BTC_GET_BL_WIFI_CONNECTED:
		*pu8 = check_fwstate(&padapter->mlmepriv, WIFI_ASOC_STATE);
		break;

	case BTC_GET_BL_WIFI_BUSY:
		*pu8 = halbtcoutsrc_IsWifiBusy(padapter);
		break;

	case BTC_GET_BL_WIFI_SCAN:
		/* Use the value of the new variable GLBtcWiFiInScanState to judge whether WiFi is in scan state or not, since the originally used flag
			WIFI_SITE_MONITOR in fwstate may not be cleared in time */
		*pu8 = GLBtcWiFiInScanState;
		break;

	case BTC_GET_BL_WIFI_LINK:
		*pu8 = check_fwstate(&padapter->mlmepriv, WIFI_UNDER_LINKING);
		break;

	case BTC_GET_BL_WIFI_ROAM:
		*pu8 = check_fwstate(&padapter->mlmepriv, WIFI_UNDER_LINKING);
		break;

	case BTC_GET_BL_WIFI_4_WAY_PROGRESS:
		*pu8 = false;
		break;

	case BTC_GET_BL_WIFI_UNDER_5G:
		*pu8 = pHalData->CurrentBandType == 1;
		break;

	case BTC_GET_BL_WIFI_AP_MODE_ENABLE:
		*pu8 = check_fwstate(&padapter->mlmepriv, WIFI_AP_STATE);
		break;

	case BTC_GET_BL_WIFI_ENABLE_ENCRYPTION:
		*pu8 = padapter->securitypriv.dot11PrivacyAlgrthm == 0 ? false : true;
		break;

	case BTC_GET_BL_WIFI_UNDER_B_MODE:
		if (mlmeext->cur_wireless_mode == WIRELESS_11B)
			*pu8 = true;
		else
			*pu8 = false;
		break;

	case BTC_GET_BL_WIFI_IS_IN_MP_MODE:
		*pu8 = false;
		break;

	case BTC_GET_BL_EXT_SWITCH:
		*pu8 = false;
		break;

	case BTC_GET_S4_WIFI_RSSI:
		*pS4Tmp = halbtcoutsrc_GetWifiRssi(padapter);
		break;

	case BTC_GET_S4_HS_RSSI:
		*pS4Tmp = 0;
		ret = false;
		break;

	case BTC_GET_U4_WIFI_BW:
		if (IsLegacyOnly(mlmeext->cur_wireless_mode))
			*pU4Tmp = BTC_WIFI_BW_LEGACY;
		else if (pHalData->CurrentChannelBW == CHANNEL_WIDTH_20)
			*pU4Tmp = BTC_WIFI_BW_HT20;
		else
			*pU4Tmp = BTC_WIFI_BW_HT40;
		break;

	case BTC_GET_U4_WIFI_TRAFFIC_DIRECTION:
		{
			PRT_LINK_DETECT_T plinkinfo;
			plinkinfo = &padapter->mlmepriv.LinkDetectInfo;

			if (plinkinfo->NumTxOkInPeriod > plinkinfo->NumRxOkInPeriod)
				*pU4Tmp = BTC_WIFI_TRAFFIC_TX;
			else
				*pU4Tmp = BTC_WIFI_TRAFFIC_RX;
		}
		break;

	case BTC_GET_U4_WIFI_FW_VER:
		*pU4Tmp = pHalData->FirmwareVersion << 16;
		*pU4Tmp |= pHalData->FirmwareSubVersion;
		break;

	case BTC_GET_U4_WIFI_LINK_STATUS:
		*pU4Tmp = halbtcoutsrc_GetWifiLinkStatus(pBtCoexist);
		break;

	case BTC_GET_U4_BT_PATCH_VER:
		*pU4Tmp = halbtcoutsrc_GetBtPatchVer(pBtCoexist);
		break;

	case BTC_GET_U1_WIFI_DOT11_CHNL:
		*pu8 = padapter->mlmeextpriv.cur_channel;
		break;

	case BTC_GET_U1_WIFI_CENTRAL_CHNL:
		*pu8 = pHalData->CurrentChannel;
		break;

	case BTC_GET_U1_WIFI_HS_CHNL:
		*pu8 = 0;
		ret = false;
		break;

	case BTC_GET_U1_MAC_PHY_MODE:
		*pu8 = BTC_SMSP;
/* 			*pU1Tmp = BTC_DMSP; */
/* 			*pU1Tmp = BTC_DMDP; */
/* 			*pU1Tmp = BTC_MP_UNKNOWN; */
		break;

	case BTC_GET_U1_AP_NUM:
		*pu8 = halbtcoutsrc_GetWifiScanAPNum(padapter);
		break;

	/* 1Ant =========== */
	case BTC_GET_U1_LPS_MODE:
		*pu8 = padapter->dvobj->pwrctl_priv.pwr_mode;
		break;

	default:
		ret = false;
		break;
	}

	return ret;
}