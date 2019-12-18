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
typedef  scalar_t__ u8 ;
struct iwl_priv {int dummy; } ;
struct iwl_lq_sta {int dummy; } ;
struct ieee80211_sta {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_ERR (struct iwl_priv*,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ IWL_MAX_TID_COUNT ; 
 int /*<<< orphan*/  rs_tl_turn_on_agg_for_tid (struct iwl_priv*,struct iwl_lq_sta*,scalar_t__,struct ieee80211_sta*) ; 

__attribute__((used)) static void rs_tl_turn_on_agg(struct iwl_priv *priv, u8 tid,
			      struct iwl_lq_sta *lq_data,
			      struct ieee80211_sta *sta)
{
	if (tid < IWL_MAX_TID_COUNT)
		rs_tl_turn_on_agg_for_tid(priv, lq_data, tid, sta);
	else
		IWL_ERR(priv, "tid exceeds max TID count: %d/%d\n",
			tid, IWL_MAX_TID_COUNT);
}