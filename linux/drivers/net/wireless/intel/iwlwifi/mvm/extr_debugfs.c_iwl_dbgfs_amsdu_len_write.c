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
typedef  void* u16 ;
struct iwl_mvm_sta {void* orig_amsdu_len; } ;
struct ieee80211_sta {void* max_amsdu_len; void** max_tid_amsdu_len; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int ARRAY_SIZE (void**) ; 
 size_t EINVAL ; 
 struct iwl_mvm_sta* iwl_mvm_sta_from_mac80211 (struct ieee80211_sta*) ; 
 scalar_t__ kstrtou16 (char*,int /*<<< orphan*/ ,void**) ; 

__attribute__((used)) static ssize_t iwl_dbgfs_amsdu_len_write(struct ieee80211_sta *sta,
					 char *buf, size_t count,
					 loff_t *ppos)
{
	struct iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	int i;
	u16 amsdu_len;

	if (kstrtou16(buf, 0, &amsdu_len))
		return -EINVAL;

	if (amsdu_len) {
		mvmsta->orig_amsdu_len = sta->max_amsdu_len;
		sta->max_amsdu_len = amsdu_len;
		for (i = 0; i < ARRAY_SIZE(sta->max_tid_amsdu_len); i++)
			sta->max_tid_amsdu_len[i] = amsdu_len;
	} else {
		sta->max_amsdu_len = mvmsta->orig_amsdu_len;
		mvmsta->orig_amsdu_len = 0;
	}
	return count;
}