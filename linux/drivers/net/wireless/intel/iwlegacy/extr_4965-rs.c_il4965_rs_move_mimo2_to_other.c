#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct il_scale_tbl_info {int action; int is_SGI; int* expected_tpt; int /*<<< orphan*/  lq_type; int /*<<< orphan*/  current_rate; int /*<<< orphan*/  is_ht40; int /*<<< orphan*/  ant_type; struct il_rate_scale_data* win; } ;
struct il_rate_scale_data {int /*<<< orphan*/  success_ratio; } ;
struct TYPE_2__ {int valid_tx_ant; int tx_chains_num; } ;
struct il_priv {TYPE_1__ hw_params; } ;
struct il_lq_sta {size_t active_tbl; int last_tpt; int search_better_tbl; int /*<<< orphan*/  action_counter; struct il_scale_tbl_info* lq_info; int /*<<< orphan*/  is_green; } ;
struct ieee80211_sta_ht_cap {int cap; } ;
struct ieee80211_sta {struct ieee80211_sta_ht_cap ht_cap; } ;
struct ieee80211_conf {int dummy; } ;
typedef  int /*<<< orphan*/  s8 ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ANT_A ; 
 int /*<<< orphan*/  ANT_B ; 
 int /*<<< orphan*/  ANT_C ; 
 int /*<<< orphan*/  D_RATE (char*) ; 
 int IEEE80211_HT_CAP_SGI_20 ; 
 int IEEE80211_HT_CAP_SGI_40 ; 
#define  IL_MIMO2_SWITCH_ANTENNA1 133 
#define  IL_MIMO2_SWITCH_ANTENNA2 132 
#define  IL_MIMO2_SWITCH_GI 131 
#define  IL_MIMO2_SWITCH_SISO_A 130 
#define  IL_MIMO2_SWITCH_SISO_B 129 
#define  IL_MIMO2_SWITCH_SISO_C 128 
 int /*<<< orphan*/  IL_RS_GOOD_RATIO ; 
 int /*<<< orphan*/  LQ_NONE ; 
 int RATE_COUNT ; 
 int /*<<< orphan*/  il4965_rate_n_flags_from_tbl (struct il_priv*,struct il_scale_tbl_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il4965_rs_is_valid_ant (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il4965_rs_set_expected_tpt_table (struct il_lq_sta*,struct il_scale_tbl_info*) ; 
 int il4965_rs_switch_to_siso (struct il_priv*,struct il_lq_sta*,struct ieee80211_conf*,struct ieee80211_sta*,struct il_scale_tbl_info*,int) ; 
 int /*<<< orphan*/  il4965_rs_toggle_antenna (int,int /*<<< orphan*/ *,struct il_scale_tbl_info*) ; 
 int /*<<< orphan*/  memcpy (struct il_scale_tbl_info*,struct il_scale_tbl_info*,int) ; 

__attribute__((used)) static int
il4965_rs_move_mimo2_to_other(struct il_priv *il, struct il_lq_sta *lq_sta,
			      struct ieee80211_conf *conf,
			      struct ieee80211_sta *sta, int idx)
{
	s8 is_green = lq_sta->is_green;
	struct il_scale_tbl_info *tbl = &(lq_sta->lq_info[lq_sta->active_tbl]);
	struct il_scale_tbl_info *search_tbl =
	    &(lq_sta->lq_info[(1 - lq_sta->active_tbl)]);
	struct il_rate_scale_data *win = &(tbl->win[idx]);
	struct ieee80211_sta_ht_cap *ht_cap = &sta->ht_cap;
	u32 sz =
	    (sizeof(struct il_scale_tbl_info) -
	     (sizeof(struct il_rate_scale_data) * RATE_COUNT));
	u8 start_action;
	u8 valid_tx_ant = il->hw_params.valid_tx_ant;
	u8 tx_chains_num = il->hw_params.tx_chains_num;
	u8 update_search_tbl_counter = 0;
	int ret;

	start_action = tbl->action;
	for (;;) {
		lq_sta->action_counter++;
		switch (tbl->action) {
		case IL_MIMO2_SWITCH_ANTENNA1:
		case IL_MIMO2_SWITCH_ANTENNA2:
			D_RATE("LQ: MIMO2 toggle Antennas\n");

			if (tx_chains_num <= 2)
				break;

			if (win->success_ratio >= IL_RS_GOOD_RATIO)
				break;

			memcpy(search_tbl, tbl, sz);
			if (il4965_rs_toggle_antenna
			    (valid_tx_ant, &search_tbl->current_rate,
			     search_tbl)) {
				update_search_tbl_counter = 1;
				goto out;
			}
			break;
		case IL_MIMO2_SWITCH_SISO_A:
		case IL_MIMO2_SWITCH_SISO_B:
		case IL_MIMO2_SWITCH_SISO_C:
			D_RATE("LQ: MIMO2 switch to SISO\n");

			/* Set up new search table for SISO */
			memcpy(search_tbl, tbl, sz);

			if (tbl->action == IL_MIMO2_SWITCH_SISO_A)
				search_tbl->ant_type = ANT_A;
			else if (tbl->action == IL_MIMO2_SWITCH_SISO_B)
				search_tbl->ant_type = ANT_B;
			else
				search_tbl->ant_type = ANT_C;

			if (!il4965_rs_is_valid_ant
			    (valid_tx_ant, search_tbl->ant_type))
				break;

			ret =
			    il4965_rs_switch_to_siso(il, lq_sta, conf, sta,
						     search_tbl, idx);
			if (!ret)
				goto out;

			break;

		case IL_MIMO2_SWITCH_GI:
			if (!tbl->is_ht40 &&
			    !(ht_cap->cap & IEEE80211_HT_CAP_SGI_20))
				break;
			if (tbl->is_ht40 &&
			    !(ht_cap->cap & IEEE80211_HT_CAP_SGI_40))
				break;

			D_RATE("LQ: MIMO2 toggle SGI/NGI\n");

			/* Set up new search table for MIMO2 */
			memcpy(search_tbl, tbl, sz);
			search_tbl->is_SGI = !tbl->is_SGI;
			il4965_rs_set_expected_tpt_table(lq_sta, search_tbl);
			/*
			 * If active table already uses the fastest possible
			 * modulation (dual stream with short guard interval),
			 * and it's working well, there's no need to look
			 * for a better type of modulation!
			 */
			if (tbl->is_SGI) {
				s32 tpt = lq_sta->last_tpt / 100;
				if (tpt >= search_tbl->expected_tpt[idx])
					break;
			}
			search_tbl->current_rate =
			    il4965_rate_n_flags_from_tbl(il, search_tbl, idx,
							 is_green);
			update_search_tbl_counter = 1;
			goto out;

		}
		tbl->action++;
		if (tbl->action > IL_MIMO2_SWITCH_GI)
			tbl->action = IL_MIMO2_SWITCH_ANTENNA1;

		if (tbl->action == start_action)
			break;
	}
	search_tbl->lq_type = LQ_NONE;
	return 0;
out:
	lq_sta->search_better_tbl = 1;
	tbl->action++;
	if (tbl->action > IL_MIMO2_SWITCH_GI)
		tbl->action = IL_MIMO2_SWITCH_ANTENNA1;
	if (update_search_tbl_counter)
		search_tbl->action = tbl->action;

	return 0;

}