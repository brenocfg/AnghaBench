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
struct pwrctrl_priv {scalar_t__ pwr_mode; int /*<<< orphan*/  lock; } ;
struct adapter {int /*<<< orphan*/  hw_init_completed; scalar_t__ bSurpriseRemoved; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*) ; 
 scalar_t__ PS_MODE_ACTIVE ; 
 struct pwrctrl_priv* adapter_to_pwrctl (struct adapter*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 unsigned long jiffies ; 
 int jiffies_to_msecs (unsigned long) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void LPS_Leave_check(
	struct adapter *padapter)
{
	struct pwrctrl_priv *pwrpriv;
	unsigned long	start_time;
	u8 bReady;

	pwrpriv = adapter_to_pwrctl(padapter);

	bReady = false;
	start_time = jiffies;

	cond_resched();

	while (1) {
		mutex_lock(&pwrpriv->lock);

		if (padapter->bSurpriseRemoved
			|| !(padapter->hw_init_completed)
			|| (pwrpriv->pwr_mode == PS_MODE_ACTIVE))
			bReady = true;

		mutex_unlock(&pwrpriv->lock);

		if (bReady)
			break;

		if (jiffies_to_msecs(jiffies - start_time) > 100) {
			DBG_871X("Wait for cpwm event  than 100 ms!!!\n");
			break;
		}
		msleep(1);
	}
}