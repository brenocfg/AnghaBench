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
typedef  int /*<<< orphan*/  u64 ;
struct ieee80211_hw {struct ath10k* priv; } ;
struct ath10k {unsigned int filter_flags; int /*<<< orphan*/  conf_mutex; } ;

/* Variables and functions */
 unsigned int SUPPORTED_FILTERS ; 
 int ath10k_monitor_recalc (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath10k_configure_filter(struct ieee80211_hw *hw,
				    unsigned int changed_flags,
				    unsigned int *total_flags,
				    u64 multicast)
{
	struct ath10k *ar = hw->priv;
	int ret;

	mutex_lock(&ar->conf_mutex);

	changed_flags &= SUPPORTED_FILTERS;
	*total_flags &= SUPPORTED_FILTERS;
	ar->filter_flags = *total_flags;

	ret = ath10k_monitor_recalc(ar);
	if (ret)
		ath10k_warn(ar, "failed to recalc monitor: %d\n", ret);

	mutex_unlock(&ar->conf_mutex);
}