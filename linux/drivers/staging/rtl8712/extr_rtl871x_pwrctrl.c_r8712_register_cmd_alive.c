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
struct pwrctrl_priv {scalar_t__ cpwm; int /*<<< orphan*/  mutex_lock; } ;
struct _adapter {struct pwrctrl_priv pwrctrlpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ALIVE ; 
 int EINVAL ; 
 scalar_t__ PS_STATE_S2 ; 
 int /*<<< orphan*/  PS_STATE_S3 ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r8712_set_rpwm (struct _adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_task_alive (struct pwrctrl_priv*,int /*<<< orphan*/ ) ; 

int r8712_register_cmd_alive(struct _adapter *padapter)
{
	int res = 0;
	struct pwrctrl_priv *pwrctrl = &padapter->pwrctrlpriv;

	mutex_lock(&pwrctrl->mutex_lock);
	register_task_alive(pwrctrl, CMD_ALIVE);
	if (pwrctrl->cpwm < PS_STATE_S2) {
		r8712_set_rpwm(padapter, PS_STATE_S3);
		res = -EINVAL;
	}
	mutex_unlock(&pwrctrl->mutex_lock);
	return res;
}