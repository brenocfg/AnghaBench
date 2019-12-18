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
typedef  int u16 ;
struct TYPE_4__ {int bBusyTraffic; int NumRxOkInPeriod; int NumTxOkInPeriod; int NumRxUnicastOkInPeriod; int TrafficTransitionCount; int bTxBusyTraffic; int bRxBusyTraffic; int bHigherBusyTraffic; int bHigherBusyRxTraffic; int bHigherBusyTxTraffic; } ;
struct mlme_priv {TYPE_2__ LinkDetectInfo; } ;
struct dvobj_priv {TYPE_1__* padapters; } ;
struct adapter {struct mlme_priv mlmepriv; } ;
struct TYPE_3__ {struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPS_CTRL_TRAFFIC_BUSY ; 
 int /*<<< orphan*/  LPS_Enter (struct adapter*,char*) ; 
 int /*<<< orphan*/  LPS_Leave (struct adapter*,char*) ; 
 int /*<<< orphan*/  WIFI_ASOC_STATE ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 struct dvobj_priv* adapter_to_dvobj (struct adapter*) ; 
 int check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  collect_traffic_statistics (struct adapter*) ; 
 int /*<<< orphan*/  rtw_lps_ctrl_wk_cmd (struct adapter*,int /*<<< orphan*/ ,int) ; 

u8 traffic_status_watchdog(struct adapter *padapter, u8 from_timer)
{
	u8 bEnterPS = false;
	u16 BusyThresholdHigh = 25;
	u16 BusyThresholdLow = 10;
	u16 BusyThreshold = BusyThresholdHigh;
	u8 bBusyTraffic = false, bTxBusyTraffic = false, bRxBusyTraffic = false;
	u8 bHigherBusyTraffic = false, bHigherBusyRxTraffic = false, bHigherBusyTxTraffic = false;

	struct mlme_priv 	*pmlmepriv = &(padapter->mlmepriv);

	collect_traffic_statistics(padapter);

	/*  */
	/*  Determine if our traffic is busy now */
	/*  */
	if ((check_fwstate(pmlmepriv, _FW_LINKED) == true)
		/*&& !MgntInitAdapterInProgress(pMgntInfo)*/) {
		/*  if we raise bBusyTraffic in last watchdog, using lower threshold. */
		if (pmlmepriv->LinkDetectInfo.bBusyTraffic)
				BusyThreshold = BusyThresholdLow;

		if (pmlmepriv->LinkDetectInfo.NumRxOkInPeriod > BusyThreshold ||
			pmlmepriv->LinkDetectInfo.NumTxOkInPeriod > BusyThreshold) {
			bBusyTraffic = true;

			if (pmlmepriv->LinkDetectInfo.NumRxOkInPeriod > pmlmepriv->LinkDetectInfo.NumTxOkInPeriod)
				bRxBusyTraffic = true;
			else
				bTxBusyTraffic = true;
		}

		/*  Higher Tx/Rx data. */
		if (pmlmepriv->LinkDetectInfo.NumRxOkInPeriod > 4000 ||
			pmlmepriv->LinkDetectInfo.NumTxOkInPeriod > 4000) {
			bHigherBusyTraffic = true;

			if (pmlmepriv->LinkDetectInfo.NumRxOkInPeriod > pmlmepriv->LinkDetectInfo.NumTxOkInPeriod)
				bHigherBusyRxTraffic = true;
			else
				bHigherBusyTxTraffic = true;
		}

		/*  check traffic for  powersaving. */
		if (((pmlmepriv->LinkDetectInfo.NumRxUnicastOkInPeriod + pmlmepriv->LinkDetectInfo.NumTxOkInPeriod) > 8) ||
			(pmlmepriv->LinkDetectInfo.NumRxUnicastOkInPeriod > 2)) {
			/* DBG_871X("(-)Tx = %d, Rx = %d\n", pmlmepriv->LinkDetectInfo.NumTxOkInPeriod, pmlmepriv->LinkDetectInfo.NumRxUnicastOkInPeriod); */
			bEnterPS = false;

			if (bBusyTraffic == true) {
				if (pmlmepriv->LinkDetectInfo.TrafficTransitionCount <= 4)
					pmlmepriv->LinkDetectInfo.TrafficTransitionCount = 4;

				pmlmepriv->LinkDetectInfo.TrafficTransitionCount++;

				/* DBG_871X("Set TrafficTransitionCount to %d\n", pmlmepriv->LinkDetectInfo.TrafficTransitionCount); */

				if (pmlmepriv->LinkDetectInfo.TrafficTransitionCount > 30/*TrafficTransitionLevel*/) {
					pmlmepriv->LinkDetectInfo.TrafficTransitionCount = 30;
				}
			}
		} else {
			/* DBG_871X("(+)Tx = %d, Rx = %d\n", pmlmepriv->LinkDetectInfo.NumTxOkInPeriod, pmlmepriv->LinkDetectInfo.NumRxUnicastOkInPeriod); */

			if (pmlmepriv->LinkDetectInfo.TrafficTransitionCount >= 2)
				pmlmepriv->LinkDetectInfo.TrafficTransitionCount -= 2;
			else
				pmlmepriv->LinkDetectInfo.TrafficTransitionCount = 0;

			if (pmlmepriv->LinkDetectInfo.TrafficTransitionCount == 0)
				bEnterPS = true;
		}

		/*  LeisurePS only work in infra mode. */
		if (bEnterPS) {
			if (!from_timer)
				LPS_Enter(padapter, "TRAFFIC_IDLE");
		} else {
			if (!from_timer)
				LPS_Leave(padapter, "TRAFFIC_BUSY");
			else
				rtw_lps_ctrl_wk_cmd(padapter, LPS_CTRL_TRAFFIC_BUSY, 1);
		}
	} else {
		struct dvobj_priv *dvobj = adapter_to_dvobj(padapter);
		int n_assoc_iface = 0;

		if (check_fwstate(&(dvobj->padapters->mlmepriv), WIFI_ASOC_STATE))
			n_assoc_iface++;

		if (!from_timer && n_assoc_iface == 0)
			LPS_Leave(padapter, "NON_LINKED");
	}

	pmlmepriv->LinkDetectInfo.NumRxOkInPeriod = 0;
	pmlmepriv->LinkDetectInfo.NumTxOkInPeriod = 0;
	pmlmepriv->LinkDetectInfo.NumRxUnicastOkInPeriod = 0;
	pmlmepriv->LinkDetectInfo.bBusyTraffic = bBusyTraffic;
	pmlmepriv->LinkDetectInfo.bTxBusyTraffic = bTxBusyTraffic;
	pmlmepriv->LinkDetectInfo.bRxBusyTraffic = bRxBusyTraffic;
	pmlmepriv->LinkDetectInfo.bHigherBusyTraffic = bHigherBusyTraffic;
	pmlmepriv->LinkDetectInfo.bHigherBusyRxTraffic = bHigherBusyRxTraffic;
	pmlmepriv->LinkDetectInfo.bHigherBusyTxTraffic = bHigherBusyTxTraffic;

	return bEnterPS;

}