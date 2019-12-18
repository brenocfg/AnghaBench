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
typedef  int u8 ;
typedef  int u64 ;
typedef  size_t u32 ;
struct registry_priv {int wifi_spec; } ;
struct recv_priv {int bIsAnyNonBEPkts; } ;
struct mlme_ext_info {size_t assoc_AP_vendor; } ;
struct mlme_ext_priv {struct mlme_ext_info mlmext_info; } ;
struct hal_com_data {size_t AcParam_BE; } ;
struct TYPE_4__ {int cur_tx_bytes; int cur_rx_bytes; } ;
struct dvobj_priv {TYPE_1__ traffic_stat; } ;
struct adapter {struct mlme_ext_priv mlmeextpriv; struct registry_priv registrypriv; struct recv_priv recvpriv; } ;
struct TYPE_5__ {size_t prv_traffic_idx; int bCurrentTurboEDCA; } ;
struct TYPE_6__ {int* pwirelessmode; TYPE_2__ DM_EDCA_Table; int /*<<< orphan*/  bLinked; struct adapter* Adapter; } ;
typedef  TYPE_3__* PDM_ODM_T ;

/* Variables and functions */
 size_t DOWN_LINK ; 
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 size_t HT_IOT_PEER_AIRGO ; 
 size_t HT_IOT_PEER_ATHEROS ; 
 size_t HT_IOT_PEER_CISCO ; 
 size_t HT_IOT_PEER_MARVELL ; 
 size_t HT_IOT_PEER_MAX ; 
 int ODM_WM_A ; 
 int ODM_WM_B ; 
 int ODM_WM_G ; 
 int ODM_WM_N24G ; 
 int /*<<< orphan*/  REG_EDCA_BE_PARAM ; 
 size_t UP_LINK ; 
 struct dvobj_priv* adapter_to_dvobj (struct adapter*) ; 
 size_t* edca_setting_DL ; 
 size_t* edca_setting_DL_GMode ; 
 size_t* edca_setting_UL ; 
 int /*<<< orphan*/  rtw_write32 (struct adapter*,int /*<<< orphan*/ ,size_t) ; 

void odm_EdcaTurboCheckCE(void *pDM_VOID)
{
	PDM_ODM_T pDM_Odm = (PDM_ODM_T)pDM_VOID;
	struct adapter *Adapter = pDM_Odm->Adapter;
	struct dvobj_priv *pdvobjpriv = adapter_to_dvobj(Adapter);
	struct recv_priv *precvpriv = &(Adapter->recvpriv);
	struct registry_priv *pregpriv = &Adapter->registrypriv;
	struct mlme_ext_priv *pmlmeext = &(Adapter->mlmeextpriv);
	struct mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	u32 EDCA_BE_UL = 0x5ea42b;
	u32 EDCA_BE_DL = 0x5ea42b;
	u32 iot_peer = 0;
	u8 wirelessmode = 0xFF;		/* invalid value */
	u32 trafficIndex;
	u32 edca_param;
	u64	cur_tx_bytes = 0;
	u64	cur_rx_bytes = 0;
	u8 bbtchange = false;
	u8 biasonrx = false;
	struct hal_com_data	*pHalData = GET_HAL_DATA(Adapter);

	if (!pDM_Odm->bLinked) {
		precvpriv->bIsAnyNonBEPkts = false;
		return;
	}

	if (pregpriv->wifi_spec == 1) {
		precvpriv->bIsAnyNonBEPkts = false;
		return;
	}

	if (pDM_Odm->pwirelessmode)
		wirelessmode = *(pDM_Odm->pwirelessmode);

	iot_peer = pmlmeinfo->assoc_AP_vendor;

	if (iot_peer >=  HT_IOT_PEER_MAX) {
		precvpriv->bIsAnyNonBEPkts = false;
		return;
	}

	/*  Check if the status needs to be changed. */
	if ((bbtchange) || (!precvpriv->bIsAnyNonBEPkts)) {
		cur_tx_bytes = pdvobjpriv->traffic_stat.cur_tx_bytes;
		cur_rx_bytes = pdvobjpriv->traffic_stat.cur_rx_bytes;

		/* traffic, TX or RX */
		if (biasonrx) {
			if (cur_tx_bytes > (cur_rx_bytes << 2)) {
				/*  Uplink TP is present. */
				trafficIndex = UP_LINK;
			} else { /*  Balance TP is present. */
				trafficIndex = DOWN_LINK;
			}
		} else {
			if (cur_rx_bytes > (cur_tx_bytes << 2)) {
				/*  Downlink TP is present. */
				trafficIndex = DOWN_LINK;
			} else { /*  Balance TP is present. */
				trafficIndex = UP_LINK;
			}
		}

		/* 92D txop can't be set to 0x3e for cisco1250 */
		if ((iot_peer == HT_IOT_PEER_CISCO) &&
		    (wirelessmode == ODM_WM_N24G)) {
			EDCA_BE_DL = edca_setting_DL[iot_peer];
			EDCA_BE_UL = edca_setting_UL[iot_peer];
		} else if ((iot_peer == HT_IOT_PEER_CISCO) &&
			   ((wirelessmode == ODM_WM_G) ||
			    (wirelessmode == (ODM_WM_B | ODM_WM_G)) ||
			    (wirelessmode == ODM_WM_A) ||
			    (wirelessmode == ODM_WM_B))) {
			EDCA_BE_DL = edca_setting_DL_GMode[iot_peer];
		} else if ((iot_peer == HT_IOT_PEER_AIRGO) &&
			   ((wirelessmode == ODM_WM_G) ||
			    (wirelessmode == ODM_WM_A))) {
			EDCA_BE_DL = 0xa630;
		} else if (iot_peer == HT_IOT_PEER_MARVELL) {
			EDCA_BE_DL = edca_setting_DL[iot_peer];
			EDCA_BE_UL = edca_setting_UL[iot_peer];
		} else if (iot_peer == HT_IOT_PEER_ATHEROS) {
			/*  Set DL EDCA for Atheros peer to 0x3ea42b. */
			EDCA_BE_DL = edca_setting_DL[iot_peer];
		}

		if (trafficIndex == DOWN_LINK)
			edca_param = EDCA_BE_DL;
		else
			edca_param = EDCA_BE_UL;

		rtw_write32(Adapter, REG_EDCA_BE_PARAM, edca_param);

		pDM_Odm->DM_EDCA_Table.prv_traffic_idx = trafficIndex;

		pDM_Odm->DM_EDCA_Table.bCurrentTurboEDCA = true;
	} else {
		/*  Turn Off EDCA turbo here. */
		/*  Restore original EDCA according to the declaration of AP. */
		 if (pDM_Odm->DM_EDCA_Table.bCurrentTurboEDCA) {
			rtw_write32(Adapter, REG_EDCA_BE_PARAM, pHalData->AcParam_BE);
			pDM_Odm->DM_EDCA_Table.bCurrentTurboEDCA = false;
		}
	}
}