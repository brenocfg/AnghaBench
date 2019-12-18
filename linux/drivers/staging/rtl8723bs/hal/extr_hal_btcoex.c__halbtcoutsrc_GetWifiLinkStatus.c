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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct mlme_priv {int dummy; } ;
struct adapter {struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  WIFI_AP_CONNECTED ; 
 int /*<<< orphan*/  WIFI_AP_STATE ; 
 int /*<<< orphan*/  WIFI_ASOC_STATE ; 
 int /*<<< orphan*/  WIFI_P2P_GC_CONNECTED ; 
 int /*<<< orphan*/  WIFI_P2P_GO_CONNECTED ; 
 int /*<<< orphan*/  WIFI_STA_CONNECTED ; 
 int check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 _halbtcoutsrc_GetWifiLinkStatus(struct adapter *padapter)
{
	struct mlme_priv *pmlmepriv;
	u8 bp2p;
	u32 portConnectedStatus;


	pmlmepriv = &padapter->mlmepriv;
	bp2p = false;
	portConnectedStatus = 0;

	if (check_fwstate(pmlmepriv, WIFI_ASOC_STATE) == true) {
		if (check_fwstate(pmlmepriv, WIFI_AP_STATE) == true) {
			if (bp2p)
				portConnectedStatus |= WIFI_P2P_GO_CONNECTED;
			else
				portConnectedStatus |= WIFI_AP_CONNECTED;
		} else {
			if (bp2p)
				portConnectedStatus |= WIFI_P2P_GC_CONNECTED;
			else
				portConnectedStatus |= WIFI_STA_CONNECTED;
		}
	}

	return portConnectedStatus;
}