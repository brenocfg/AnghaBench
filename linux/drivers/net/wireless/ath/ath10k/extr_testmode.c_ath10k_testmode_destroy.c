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
struct ath10k {scalar_t__ state; int /*<<< orphan*/  conf_mutex; } ;

/* Variables and functions */
 scalar_t__ ATH10K_STATE_UTF ; 
 int /*<<< orphan*/  __ath10k_tm_cmd_utf_stop (struct ath10k*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void ath10k_testmode_destroy(struct ath10k *ar)
{
	mutex_lock(&ar->conf_mutex);

	if (ar->state != ATH10K_STATE_UTF) {
		/* utf firmware is not running, nothing to do */
		goto out;
	}

	__ath10k_tm_cmd_utf_stop(ar);

out:
	mutex_unlock(&ar->conf_mutex);
}