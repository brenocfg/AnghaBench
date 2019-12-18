#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_2__ {scalar_t__ bBusyTraffic; } ;
struct mlme_priv {TYPE_1__ LinkDetectInfo; } ;
struct adapter {struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  WIFI_AP_STATE ; 
 int /*<<< orphan*/  WIFI_ASOC_STATE ; 
 int check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 halbtcoutsrc_IsWifiBusy(struct adapter *padapter)
{
	struct mlme_priv *pmlmepriv;


	pmlmepriv = &padapter->mlmepriv;

	if (check_fwstate(pmlmepriv, WIFI_ASOC_STATE) == true) {
		if (check_fwstate(pmlmepriv, WIFI_AP_STATE) == true)
			return true;
		if (pmlmepriv->LinkDetectInfo.bBusyTraffic)
			return true;
	}

	return false;
}