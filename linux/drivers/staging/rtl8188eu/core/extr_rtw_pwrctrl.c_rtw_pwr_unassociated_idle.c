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
struct mlme_priv {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ips_deny_time; } ;
struct adapter {TYPE_1__ pwrctrlpriv; struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int WIFI_ADHOC_MASTER_STATE ; 
 int WIFI_ADHOC_STATE ; 
 int WIFI_AP_STATE ; 
 int WIFI_ASOC_STATE ; 
 int WIFI_SITE_MONITOR ; 
 int WIFI_UNDER_LINKING ; 
 int WIFI_UNDER_WPS ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ time_after_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool rtw_pwr_unassociated_idle(struct adapter *adapter)
{
	struct mlme_priv *pmlmepriv = &(adapter->mlmepriv);
	bool ret = false;

	if (time_after_eq(adapter->pwrctrlpriv.ips_deny_time, jiffies))
		goto exit;

	if (check_fwstate(pmlmepriv, WIFI_ASOC_STATE|WIFI_SITE_MONITOR) ||
	    check_fwstate(pmlmepriv, WIFI_UNDER_LINKING|WIFI_UNDER_WPS) ||
	    check_fwstate(pmlmepriv, WIFI_AP_STATE) ||
	    check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE|WIFI_ADHOC_STATE))
		goto exit;

	ret = true;

exit:
	return ret;
}