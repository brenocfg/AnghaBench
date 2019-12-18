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
struct ath9k_htc_priv {scalar_t__ ps_usecount; int /*<<< orphan*/  htc_pm_lock; int /*<<< orphan*/  ah; scalar_t__ ps_enabled; scalar_t__ ps_idle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH9K_PM_FULL_SLEEP ; 
 int /*<<< orphan*/  ATH9K_PM_NETWORK_SLEEP ; 
 int /*<<< orphan*/  ath9k_hw_setpower (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_hw_setrxabort (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath9k_hw_stopdmarecv (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void ath9k_htc_ps_restore(struct ath9k_htc_priv *priv)
{
	bool reset;

	mutex_lock(&priv->htc_pm_lock);
	if (--priv->ps_usecount != 0)
		goto unlock;

	if (priv->ps_idle) {
		ath9k_hw_setrxabort(priv->ah, true);
		ath9k_hw_stopdmarecv(priv->ah, &reset);
		ath9k_hw_setpower(priv->ah, ATH9K_PM_FULL_SLEEP);
	} else if (priv->ps_enabled) {
		ath9k_hw_setpower(priv->ah, ATH9K_PM_NETWORK_SLEEP);
	}

unlock:
	mutex_unlock(&priv->htc_pm_lock);
}