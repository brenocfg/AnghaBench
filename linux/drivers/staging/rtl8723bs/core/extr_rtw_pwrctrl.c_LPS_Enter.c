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
struct pwrctrl_priv {int LpsIdleCount; scalar_t__ pwr_mode; int bpower_saving; int /*<<< orphan*/  power_mgnt; scalar_t__ bLeisurePs; } ;
struct dvobj_priv {TYPE_2__* padapters; } ;
struct TYPE_3__ {int /*<<< orphan*/  smart_ps; } ;
struct adapter {TYPE_1__ registrypriv; } ;
struct TYPE_4__ {int /*<<< orphan*/  mlmepriv; } ;

/* Variables and functions */
 scalar_t__ IFACE_PORT0 ; 
 scalar_t__ PS_MODE_ACTIVE ; 
 int /*<<< orphan*/  PS_RDY_CHECK (TYPE_2__*) ; 
 int /*<<< orphan*/  WIFI_ASOC_STATE ; 
 struct dvobj_priv* adapter_to_dvobj (struct adapter*) ; 
 scalar_t__ check_fwstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct pwrctrl_priv* dvobj_to_pwrctl (struct dvobj_priv*) ; 
 scalar_t__ get_iface_type (struct adapter*) ; 
 scalar_t__ hal_btcoex_IsBtControlLps (struct adapter*) ; 
 int /*<<< orphan*/  rtw_set_ps_mode (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 

void LPS_Enter(struct adapter *padapter, const char *msg)
{
	struct dvobj_priv *dvobj = adapter_to_dvobj(padapter);
	struct pwrctrl_priv *pwrpriv = dvobj_to_pwrctl(dvobj);
	int n_assoc_iface = 0;
	char buf[32] = {0};

	if (hal_btcoex_IsBtControlLps(padapter))
		return;

	/* Skip lps enter request if number of assocated adapters is not 1 */
	if (check_fwstate(&(dvobj->padapters->mlmepriv), WIFI_ASOC_STATE))
		n_assoc_iface++;
	if (n_assoc_iface != 1)
		return;

	/* Skip lps enter request for adapter not port0 */
	if (get_iface_type(padapter) != IFACE_PORT0)
		return;

	if (!PS_RDY_CHECK(dvobj->padapters))
		return;

	if (pwrpriv->bLeisurePs) {
		/*  Idle for a while if we connect to AP a while ago. */
		if (pwrpriv->LpsIdleCount >= 2) { /*   4 Sec */
			if (pwrpriv->pwr_mode == PS_MODE_ACTIVE) {
				sprintf(buf, "WIFI-%s", msg);
				pwrpriv->bpower_saving = true;
				rtw_set_ps_mode(padapter, pwrpriv->power_mgnt, padapter->registrypriv.smart_ps, 0, buf);
			}
		} else
			pwrpriv->LpsIdleCount++;
	}

/* 	DBG_871X("-LeisurePSEnter\n"); */
}