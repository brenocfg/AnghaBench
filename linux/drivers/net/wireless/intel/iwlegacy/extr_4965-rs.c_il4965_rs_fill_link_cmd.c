#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct il_scale_tbl_info {int /*<<< orphan*/  lq_type; int /*<<< orphan*/  ant_type; } ;
struct TYPE_5__ {int valid_tx_ant; } ;
struct il_priv {TYPE_1__ hw_params; } ;
struct TYPE_8__ {int /*<<< orphan*/  agg_time_limit; int /*<<< orphan*/  agg_dis_start_th; int /*<<< orphan*/  agg_frame_cnt_limit; } ;
struct TYPE_6__ {int mimo_delimiter; int /*<<< orphan*/  dual_stream_ant_msk; int /*<<< orphan*/  single_stream_ant_msk; } ;
struct il_link_quality_cmd {TYPE_4__ agg_params; TYPE_3__* rs_table; TYPE_2__ general_params; } ;
struct il_lq_sta {int /*<<< orphan*/  band; struct il_link_quality_cmd lq; } ;
struct TYPE_7__ {void* rate_n_flags; } ;

/* Variables and functions */
 int IL_HT_NUMBER_TRY ; 
 int IL_NUMBER_TRY ; 
 int /*<<< orphan*/  LINK_QUAL_AGG_DISABLE_START_DEF ; 
 int /*<<< orphan*/  LINK_QUAL_AGG_FRAME_LIMIT_DEF ; 
 int /*<<< orphan*/  LINK_QUAL_AGG_TIME_LIMIT_DEF ; 
 int LINK_QUAL_MAX_RETRY_NUM ; 
 int NUM_TRY_BEFORE_ANT_TOGGLE ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int il4965_num_of_ant (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il4965_rs_dbgfs_set_mcs (struct il_lq_sta*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  il4965_rs_get_lower_rate (struct il_lq_sta*,struct il_scale_tbl_info*,int,int) ; 
 int /*<<< orphan*/  il4965_rs_get_tbl_info_from_mcs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct il_scale_tbl_info*,int*) ; 
 scalar_t__ il4965_rs_toggle_antenna (int,int /*<<< orphan*/ *,struct il_scale_tbl_info*) ; 
 scalar_t__ is_legacy (int /*<<< orphan*/ ) ; 
 scalar_t__ is_mimo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
il4965_rs_fill_link_cmd(struct il_priv *il, struct il_lq_sta *lq_sta,
			u32 new_rate)
{
	struct il_scale_tbl_info tbl_type;
	int idx = 0;
	int rate_idx;
	int repeat_rate = 0;
	u8 ant_toggle_cnt = 0;
	u8 use_ht_possible = 1;
	u8 valid_tx_ant = 0;
	struct il_link_quality_cmd *lq_cmd = &lq_sta->lq;

	/* Override starting rate (idx 0) if needed for debug purposes */
	il4965_rs_dbgfs_set_mcs(lq_sta, &new_rate, idx);

	/* Interpret new_rate (rate_n_flags) */
	il4965_rs_get_tbl_info_from_mcs(new_rate, lq_sta->band, &tbl_type,
					&rate_idx);

	/* How many times should we repeat the initial rate? */
	if (is_legacy(tbl_type.lq_type)) {
		ant_toggle_cnt = 1;
		repeat_rate = IL_NUMBER_TRY;
	} else {
		repeat_rate = IL_HT_NUMBER_TRY;
	}

	lq_cmd->general_params.mimo_delimiter =
	    is_mimo(tbl_type.lq_type) ? 1 : 0;

	/* Fill 1st table entry (idx 0) */
	lq_cmd->rs_table[idx].rate_n_flags = cpu_to_le32(new_rate);

	if (il4965_num_of_ant(tbl_type.ant_type) == 1) {
		lq_cmd->general_params.single_stream_ant_msk =
		    tbl_type.ant_type;
	} else if (il4965_num_of_ant(tbl_type.ant_type) == 2) {
		lq_cmd->general_params.dual_stream_ant_msk = tbl_type.ant_type;
	}
	/* otherwise we don't modify the existing value */
	idx++;
	repeat_rate--;
	if (il)
		valid_tx_ant = il->hw_params.valid_tx_ant;

	/* Fill rest of rate table */
	while (idx < LINK_QUAL_MAX_RETRY_NUM) {
		/* Repeat initial/next rate.
		 * For legacy IL_NUMBER_TRY == 1, this loop will not execute.
		 * For HT IL_HT_NUMBER_TRY == 3, this executes twice. */
		while (repeat_rate > 0 && idx < LINK_QUAL_MAX_RETRY_NUM) {
			if (is_legacy(tbl_type.lq_type)) {
				if (ant_toggle_cnt < NUM_TRY_BEFORE_ANT_TOGGLE)
					ant_toggle_cnt++;
				else if (il &&
					 il4965_rs_toggle_antenna(valid_tx_ant,
								  &new_rate,
								  &tbl_type))
					ant_toggle_cnt = 1;
			}

			/* Override next rate if needed for debug purposes */
			il4965_rs_dbgfs_set_mcs(lq_sta, &new_rate, idx);

			/* Fill next table entry */
			lq_cmd->rs_table[idx].rate_n_flags =
			    cpu_to_le32(new_rate);
			repeat_rate--;
			idx++;
		}

		il4965_rs_get_tbl_info_from_mcs(new_rate, lq_sta->band,
						&tbl_type, &rate_idx);

		/* Indicate to uCode which entries might be MIMO.
		 * If initial rate was MIMO, this will finally end up
		 * as (IL_HT_NUMBER_TRY * 2), after 2nd pass, otherwise 0. */
		if (is_mimo(tbl_type.lq_type))
			lq_cmd->general_params.mimo_delimiter = idx;

		/* Get next rate */
		new_rate =
		    il4965_rs_get_lower_rate(lq_sta, &tbl_type, rate_idx,
					     use_ht_possible);

		/* How many times should we repeat the next rate? */
		if (is_legacy(tbl_type.lq_type)) {
			if (ant_toggle_cnt < NUM_TRY_BEFORE_ANT_TOGGLE)
				ant_toggle_cnt++;
			else if (il &&
				 il4965_rs_toggle_antenna(valid_tx_ant,
							  &new_rate, &tbl_type))
				ant_toggle_cnt = 1;

			repeat_rate = IL_NUMBER_TRY;
		} else {
			repeat_rate = IL_HT_NUMBER_TRY;
		}

		/* Don't allow HT rates after next pass.
		 * il4965_rs_get_lower_rate() will change type to LQ_A or LQ_G. */
		use_ht_possible = 0;

		/* Override next rate if needed for debug purposes */
		il4965_rs_dbgfs_set_mcs(lq_sta, &new_rate, idx);

		/* Fill next table entry */
		lq_cmd->rs_table[idx].rate_n_flags = cpu_to_le32(new_rate);

		idx++;
		repeat_rate--;
	}

	lq_cmd->agg_params.agg_frame_cnt_limit = LINK_QUAL_AGG_FRAME_LIMIT_DEF;
	lq_cmd->agg_params.agg_dis_start_th = LINK_QUAL_AGG_DISABLE_START_DEF;

	lq_cmd->agg_params.agg_time_limit =
	    cpu_to_le16(LINK_QUAL_AGG_TIME_LIMIT_DEF);
}