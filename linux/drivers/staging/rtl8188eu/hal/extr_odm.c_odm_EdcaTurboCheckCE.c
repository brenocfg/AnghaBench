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
typedef  int u8 ;
typedef  int u64 ;
typedef  size_t u32 ;
struct xmit_priv {int tx_bytes; int last_tx_bytes; } ;
struct registry_priv {int wifi_spec; } ;
struct recv_priv {int bIsAnyNonBEPkts; int rx_bytes; int last_rx_bytes; } ;
struct TYPE_4__ {size_t prv_traffic_idx; int bCurrentTurboEDCA; } ;
struct odm_dm_struct {TYPE_2__ DM_EDCA_Table; struct adapter* Adapter; } ;
struct mlme_ext_info {size_t assoc_AP_vendor; } ;
struct mlme_ext_priv {int cur_wireless_mode; struct mlme_ext_info mlmext_info; } ;
struct adapter {TYPE_1__* HalData; struct mlme_ext_priv mlmeextpriv; struct registry_priv registrypriv; struct recv_priv recvpriv; struct xmit_priv xmitpriv; } ;
struct TYPE_3__ {size_t AcParam_BE; } ;

/* Variables and functions */
 size_t DOWN_LINK ; 
 size_t** EDCAParam ; 
 size_t HT_IOT_PEER_ATHEROS ; 
 size_t HT_IOT_PEER_CISCO ; 
 size_t HT_IOT_PEER_MAX ; 
 size_t HT_IOT_PEER_RALINK ; 
 size_t HT_IOT_PEER_UNKNOWN ; 
 int /*<<< orphan*/  REG_EDCA_BE_PARAM ; 
 size_t UP_LINK ; 
 int WIRELESS_11_24N ; 
 int /*<<< orphan*/  usb_write32 (struct adapter*,int /*<<< orphan*/ ,size_t) ; 

void odm_EdcaTurboCheckCE(struct odm_dm_struct *pDM_Odm)
{
	struct adapter *Adapter = pDM_Odm->Adapter;
	u32	trafficIndex;
	u32	edca_param;
	u64	cur_tx_bytes = 0;
	u64	cur_rx_bytes = 0;
	u8	bbtchange = false;
	struct xmit_priv		*pxmitpriv = &(Adapter->xmitpriv);
	struct recv_priv		*precvpriv = &(Adapter->recvpriv);
	struct registry_priv	*pregpriv = &Adapter->registrypriv;
	struct mlme_ext_priv	*pmlmeext = &(Adapter->mlmeextpriv);
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);

	if (pregpriv->wifi_spec == 1) /*  (pmlmeinfo->HT_enable == 0)) */
		goto dm_CheckEdcaTurbo_EXIT;

	if (pmlmeinfo->assoc_AP_vendor >=  HT_IOT_PEER_MAX)
		goto dm_CheckEdcaTurbo_EXIT;

	/*  Check if the status needs to be changed. */
	if ((bbtchange) || (!precvpriv->bIsAnyNonBEPkts)) {
		cur_tx_bytes = pxmitpriv->tx_bytes - pxmitpriv->last_tx_bytes;
		cur_rx_bytes = precvpriv->rx_bytes - precvpriv->last_rx_bytes;

		/* traffic, TX or RX */
		if ((pmlmeinfo->assoc_AP_vendor == HT_IOT_PEER_RALINK) ||
		    (pmlmeinfo->assoc_AP_vendor == HT_IOT_PEER_ATHEROS)) {
			if (cur_tx_bytes > (cur_rx_bytes << 2)) {
				/*  Uplink TP is present. */
				trafficIndex = UP_LINK;
			} else {
				/*  Balance TP is present. */
				trafficIndex = DOWN_LINK;
			}
		} else {
			if (cur_rx_bytes > (cur_tx_bytes << 2)) {
				/*  Downlink TP is present. */
				trafficIndex = DOWN_LINK;
			} else {
				/*  Balance TP is present. */
				trafficIndex = UP_LINK;
			}
		}

		if ((pDM_Odm->DM_EDCA_Table.prv_traffic_idx != trafficIndex) || (!pDM_Odm->DM_EDCA_Table.bCurrentTurboEDCA)) {
			if ((pmlmeinfo->assoc_AP_vendor == HT_IOT_PEER_CISCO) && (pmlmeext->cur_wireless_mode & WIRELESS_11_24N))
				edca_param = EDCAParam[pmlmeinfo->assoc_AP_vendor][trafficIndex];
			else
				edca_param = EDCAParam[HT_IOT_PEER_UNKNOWN][trafficIndex];

			usb_write32(Adapter, REG_EDCA_BE_PARAM, edca_param);

			pDM_Odm->DM_EDCA_Table.prv_traffic_idx = trafficIndex;
		}

		pDM_Odm->DM_EDCA_Table.bCurrentTurboEDCA = true;
	} else {
		/*  Turn Off EDCA turbo here. */
		/*  Restore original EDCA according to the declaration of AP. */
		if (pDM_Odm->DM_EDCA_Table.bCurrentTurboEDCA) {
			usb_write32(Adapter, REG_EDCA_BE_PARAM,
				    Adapter->HalData->AcParam_BE);
			pDM_Odm->DM_EDCA_Table.bCurrentTurboEDCA = false;
		}
	}

dm_CheckEdcaTurbo_EXIT:
	/*  Set variables for next time. */
	precvpriv->bIsAnyNonBEPkts = false;
	pxmitpriv->last_tx_bytes = pxmitpriv->tx_bytes;
	precvpriv->last_rx_bytes = precvpriv->rx_bytes;
}