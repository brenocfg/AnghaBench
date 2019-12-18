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
struct rs_tx_column {int /*<<< orphan*/  ant; } ;
struct rs_rate {int dummy; } ;
struct iwl_mvm {int dummy; } ;
struct ieee80211_sta {int dummy; } ;

/* Variables and functions */
 int iwl_mvm_bt_coex_is_ant_avail (struct iwl_mvm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool rs_ant_allow(struct iwl_mvm *mvm, struct ieee80211_sta *sta,
			 struct rs_rate *rate,
			 const struct rs_tx_column *next_col)
{
	return iwl_mvm_bt_coex_is_ant_avail(mvm, next_col->ant);
}