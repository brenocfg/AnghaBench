#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct wlan_bssid_ex {int /*<<< orphan*/  MacAddress; } ;
struct sta_info {int dummy; } ;
struct TYPE_12__ {struct wlan_bssid_ex network; } ;
struct TYPE_13__ {TYPE_2__ mlmext_info; } ;
struct adapter {int /*<<< orphan*/  stapriv; TYPE_3__ mlmeextpriv; int /*<<< orphan*/  mlmepriv; } ;
struct TYPE_11__ {int bBtDisabled; int bBtBusy; int bLimitedDig; int bForceToRoam; int bRejectAggPkt; int bBtCtrlAggBufSize; int bIncreaseScanDevNum; int bBtTxRxMask; int rssiAdjustForAgcTableOn; int aggBufSize; int rssiAdjustFor1AntCoexType; int lpsVal; int rpwmVal; int /*<<< orphan*/  raMask; } ;
struct TYPE_14__ {TYPE_1__ btInfo; struct adapter* Adapter; } ;
typedef  TYPE_4__* PBTC_COEXIST ;

/* Variables and functions */
#define  BTC_SET_ACT_AGGREGATE_CTRL 151 
#define  BTC_SET_ACT_CTRL_8723B_ANT 150 
#define  BTC_SET_ACT_CTRL_BT_COEX 149 
#define  BTC_SET_ACT_CTRL_BT_INFO 148 
#define  BTC_SET_ACT_DISABLE_LOW_POWER 147 
#define  BTC_SET_ACT_ENTER_LPS 146 
#define  BTC_SET_ACT_GET_BT_RSSI 145 
#define  BTC_SET_ACT_LEAVE_LPS 144 
#define  BTC_SET_ACT_NORMAL_LPS 143 
#define  BTC_SET_ACT_SEND_MIMO_PS 142 
#define  BTC_SET_ACT_UPDATE_RAMASK 141 
#define  BTC_SET_BL_BT_CTRL_AGG_SIZE 140 
#define  BTC_SET_BL_BT_DISABLE 139 
#define  BTC_SET_BL_BT_LIMITED_DIG 138 
#define  BTC_SET_BL_BT_TRAFFIC_BUSY 137 
#define  BTC_SET_BL_BT_TX_RX_MASK 136 
#define  BTC_SET_BL_FORCE_TO_ROAM 135 
#define  BTC_SET_BL_INC_SCAN_DEV_NUM 134 
#define  BTC_SET_BL_TO_REJ_AP_AGG_PKT 133 
#define  BTC_SET_U1_AGG_BUF_SIZE 132 
#define  BTC_SET_U1_LPS_VAL 131 
#define  BTC_SET_U1_RPWM_VAL 130 
#define  BTC_SET_U1_RSSI_ADJ_VAL_FOR_1ANT_COEX_TYPE 129 
#define  BTC_SET_U1_RSSI_ADJ_VAL_FOR_AGC_TABLE_ON 128 
 int /*<<< orphan*/  WIFI_ASOC_STATE ; 
 int check_fwstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtcoutsrc_AggregationCheck (TYPE_4__*) ; 
 int /*<<< orphan*/  halbtcoutsrc_DisableLowPower (TYPE_4__*,int) ; 
 int /*<<< orphan*/  halbtcoutsrc_EnterLps (TYPE_4__*) ; 
 int /*<<< orphan*/  halbtcoutsrc_IsBtCoexistAvailable (TYPE_4__*) ; 
 int /*<<< orphan*/  halbtcoutsrc_LeaveLps (TYPE_4__*) ; 
 int /*<<< orphan*/  halbtcoutsrc_NormalLps (TYPE_4__*) ; 
 struct sta_info* rtw_get_stainfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_hal_update_ra_mask (struct sta_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 halbtcoutsrc_Set(void *pBtcContext, u8 setType, void *pInBuf)
{
	PBTC_COEXIST pBtCoexist;
	struct adapter *padapter;
	u8 *pu8;
	u32 *pU4Tmp;
	u8 ret;


	pBtCoexist = (PBTC_COEXIST)pBtcContext;
	padapter = pBtCoexist->Adapter;
	pu8 = pInBuf;
	pU4Tmp = pInBuf;
	ret = true;

	if (!halbtcoutsrc_IsBtCoexistAvailable(pBtCoexist))
		return false;

	switch (setType) {
	/*  set some u8 type variables. */
	case BTC_SET_BL_BT_DISABLE:
		pBtCoexist->btInfo.bBtDisabled = *pu8;
		break;

	case BTC_SET_BL_BT_TRAFFIC_BUSY:
		pBtCoexist->btInfo.bBtBusy = *pu8;
		break;

	case BTC_SET_BL_BT_LIMITED_DIG:
		pBtCoexist->btInfo.bLimitedDig = *pu8;
		break;

	case BTC_SET_BL_FORCE_TO_ROAM:
		pBtCoexist->btInfo.bForceToRoam = *pu8;
		break;

	case BTC_SET_BL_TO_REJ_AP_AGG_PKT:
		pBtCoexist->btInfo.bRejectAggPkt = *pu8;
		break;

	case BTC_SET_BL_BT_CTRL_AGG_SIZE:
		pBtCoexist->btInfo.bBtCtrlAggBufSize = *pu8;
		break;

	case BTC_SET_BL_INC_SCAN_DEV_NUM:
		pBtCoexist->btInfo.bIncreaseScanDevNum = *pu8;
		break;

	case BTC_SET_BL_BT_TX_RX_MASK:
		pBtCoexist->btInfo.bBtTxRxMask = *pu8;
		break;

	/*  set some u8 type variables. */
	case BTC_SET_U1_RSSI_ADJ_VAL_FOR_AGC_TABLE_ON:
		pBtCoexist->btInfo.rssiAdjustForAgcTableOn = *pu8;
		break;

	case BTC_SET_U1_AGG_BUF_SIZE:
		pBtCoexist->btInfo.aggBufSize = *pu8;
		break;

	/*  the following are some action which will be triggered */
	case BTC_SET_ACT_GET_BT_RSSI:
		ret = false;
		break;

	case BTC_SET_ACT_AGGREGATE_CTRL:
		halbtcoutsrc_AggregationCheck(pBtCoexist);
		break;

	/* 1Ant =========== */
	/*  set some u8 type variables. */
	case BTC_SET_U1_RSSI_ADJ_VAL_FOR_1ANT_COEX_TYPE:
		pBtCoexist->btInfo.rssiAdjustFor1AntCoexType = *pu8;
		break;

	case BTC_SET_U1_LPS_VAL:
		pBtCoexist->btInfo.lpsVal = *pu8;
		break;

	case BTC_SET_U1_RPWM_VAL:
		pBtCoexist->btInfo.rpwmVal = *pu8;
		break;

	/*  the following are some action which will be triggered */
	case BTC_SET_ACT_LEAVE_LPS:
		halbtcoutsrc_LeaveLps(pBtCoexist);
		break;

	case BTC_SET_ACT_ENTER_LPS:
		halbtcoutsrc_EnterLps(pBtCoexist);
		break;

	case BTC_SET_ACT_NORMAL_LPS:
		halbtcoutsrc_NormalLps(pBtCoexist);
		break;

	case BTC_SET_ACT_DISABLE_LOW_POWER:
		halbtcoutsrc_DisableLowPower(pBtCoexist, *pu8);
		break;

	case BTC_SET_ACT_UPDATE_RAMASK:
		pBtCoexist->btInfo.raMask = *pU4Tmp;

		if (check_fwstate(&padapter->mlmepriv, WIFI_ASOC_STATE) == true) {
			struct sta_info *psta;
			struct wlan_bssid_ex *cur_network;

			cur_network = &padapter->mlmeextpriv.mlmext_info.network;
			psta = rtw_get_stainfo(&padapter->stapriv, cur_network->MacAddress);
			rtw_hal_update_ra_mask(psta, 0);
		}
		break;

	case BTC_SET_ACT_SEND_MIMO_PS:
		ret = false;
		break;

	case BTC_SET_ACT_CTRL_BT_INFO:
		ret = false;
		break;

	case BTC_SET_ACT_CTRL_BT_COEX:
		ret = false;
		break;
	case BTC_SET_ACT_CTRL_8723B_ANT:
		ret = false;
		break;
	/*  */
	default:
		ret = false;
		break;
	}

	return ret;
}