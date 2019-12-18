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
struct pwrctrl_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  ips_mode_req; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ips_enter (struct adapter*) ; 
 struct pwrctrl_priv* adapter_to_pwrctl (struct adapter*) ; 
 int /*<<< orphan*/  hal_btcoex_IpsNotify (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void ips_enter(struct adapter *padapter)
{
	struct pwrctrl_priv *pwrpriv = adapter_to_pwrctl(padapter);


	hal_btcoex_IpsNotify(padapter, pwrpriv->ips_mode_req);

	mutex_lock(&pwrpriv->lock);
	_ips_enter(padapter);
	mutex_unlock(&pwrpriv->lock);
}