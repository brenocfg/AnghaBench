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
struct pwrctrl_priv {unsigned long DelayLPSLastTimeStamp; scalar_t__ bInSuspend; } ;
struct mlme_priv {int dummy; } ;
struct TYPE_2__ {scalar_t__ dot11AuthAlgrthm; int /*<<< orphan*/  binstallGrpkey; } ;
struct adapter {TYPE_1__ securitypriv; struct mlme_priv mlmepriv; struct pwrctrl_priv pwrctrlpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_88E (char*) ; 
 unsigned long LPS_DELAY_TIME ; 
 int /*<<< orphan*/  WIFI_ADHOC_MASTER_STATE ; 
 int /*<<< orphan*/  WIFI_ADHOC_STATE ; 
 int /*<<< orphan*/  WIFI_AP_STATE ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 int /*<<< orphan*/  _FW_UNDER_SURVEY ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ dot11AuthAlgrthm_8021X ; 
 unsigned long jiffies ; 

__attribute__((used)) static u8 PS_RDY_CHECK(struct adapter *padapter)
{
	unsigned long curr_time, delta_time;
	struct pwrctrl_priv	*pwrpriv = &padapter->pwrctrlpriv;
	struct mlme_priv	*pmlmepriv = &(padapter->mlmepriv);

	curr_time = jiffies;
	delta_time = curr_time - pwrpriv->DelayLPSLastTimeStamp;

	if (delta_time < LPS_DELAY_TIME)
		return false;

	if ((!check_fwstate(pmlmepriv, _FW_LINKED)) ||
	    (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY)) ||
	    (check_fwstate(pmlmepriv, WIFI_AP_STATE)) ||
	    (check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE)) ||
	    (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE)))
		return false;
	if (pwrpriv->bInSuspend)
		return false;
	if (padapter->securitypriv.dot11AuthAlgrthm == dot11AuthAlgrthm_8021X &&
	    !padapter->securitypriv.binstallGrpkey) {
		DBG_88E("Group handshake still in progress !!!\n");
		return false;
	}
	return true;
}