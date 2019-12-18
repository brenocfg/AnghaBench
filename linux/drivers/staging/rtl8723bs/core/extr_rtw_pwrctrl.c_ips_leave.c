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
struct pwrctrl_priv {int /*<<< orphan*/  lock; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPS_NONE ; 
 int _SUCCESS ; 
 int _ips_leave (struct adapter*) ; 
 struct pwrctrl_priv* adapter_to_pwrctl (struct adapter*) ; 
 int /*<<< orphan*/  hal_btcoex_IpsNotify (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_primary_adapter (struct adapter*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int ips_leave(struct adapter *padapter)
{
	struct pwrctrl_priv *pwrpriv = adapter_to_pwrctl(padapter);
	int ret;

	if (!is_primary_adapter(padapter))
		return _SUCCESS;

	mutex_lock(&pwrpriv->lock);
	ret = _ips_leave(padapter);
	mutex_unlock(&pwrpriv->lock);

	if (_SUCCESS == ret)
		hal_btcoex_IpsNotify(padapter, IPS_NONE);

	return ret;
}