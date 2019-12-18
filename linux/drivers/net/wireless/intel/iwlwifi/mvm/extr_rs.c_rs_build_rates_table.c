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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct rs_rate {int stbc; } ;
struct iwl_mvm {TYPE_1__* fw; } ;
struct iwl_lq_cmd {int mimo_delim; int /*<<< orphan*/  flags; int /*<<< orphan*/  rs_table; } ;
struct iwl_lq_sta {struct iwl_lq_cmd lq; } ;
struct ieee80211_sta {int dummy; } ;
typedef  int /*<<< orphan*/  rate ;
struct TYPE_2__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 int IWL_MVM_RS_HT_VHT_RETRIES_PER_RATE ; 
 int IWL_MVM_RS_INITIAL_LEGACY_NUM_RATES ; 
 int IWL_MVM_RS_INITIAL_LEGACY_RETRIES ; 
 int IWL_MVM_RS_INITIAL_MIMO_NUM_RATES ; 
 int IWL_MVM_RS_INITIAL_SISO_NUM_RATES ; 
 int IWL_MVM_RS_SECONDARY_LEGACY_NUM_RATES ; 
 int IWL_MVM_RS_SECONDARY_LEGACY_RETRIES ; 
 int IWL_MVM_RS_SECONDARY_SISO_NUM_RATES ; 
 int IWL_MVM_RS_SECONDARY_SISO_RETRIES ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_API_LQ_SS_PARAMS ; 
 int /*<<< orphan*/  LQ_FLAGS_COLOR_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LQ_FLAG_COLOR_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LQ_FLAG_COLOR_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  fw_has_api (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ is_legacy (struct rs_rate*) ; 
 scalar_t__ is_mimo (struct rs_rate*) ; 
 scalar_t__ is_siso (struct rs_rate*) ; 
 int /*<<< orphan*/  iwl_mvm_get_valid_tx_ant (struct iwl_mvm*) ; 
 int /*<<< orphan*/  memcpy (struct rs_rate*,struct rs_rate const*,int) ; 
 int /*<<< orphan*/  rs_fill_rates_for_column (struct iwl_mvm*,struct iwl_lq_sta*,struct rs_rate*,int /*<<< orphan*/ ,int*,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rs_get_lower_rate_down_column (struct iwl_lq_sta*,struct rs_rate*) ; 
 scalar_t__ rs_stbc_allow (struct iwl_mvm*,struct ieee80211_sta*,struct iwl_lq_sta*) ; 

__attribute__((used)) static void rs_build_rates_table(struct iwl_mvm *mvm,
				 struct ieee80211_sta *sta,
				 struct iwl_lq_sta *lq_sta,
				 const struct rs_rate *initial_rate)
{
	struct rs_rate rate;
	int num_rates, num_retries, index = 0;
	u8 valid_tx_ant = 0;
	struct iwl_lq_cmd *lq_cmd = &lq_sta->lq;
	bool toggle_ant = false;
	u32 color;

	memcpy(&rate, initial_rate, sizeof(rate));

	valid_tx_ant = iwl_mvm_get_valid_tx_ant(mvm);

	/* TODO: remove old API when min FW API hits 14 */
	if (!fw_has_api(&mvm->fw->ucode_capa, IWL_UCODE_TLV_API_LQ_SS_PARAMS) &&
	    rs_stbc_allow(mvm, sta, lq_sta))
		rate.stbc = true;

	if (is_siso(&rate)) {
		num_rates = IWL_MVM_RS_INITIAL_SISO_NUM_RATES;
		num_retries = IWL_MVM_RS_HT_VHT_RETRIES_PER_RATE;
	} else if (is_mimo(&rate)) {
		num_rates = IWL_MVM_RS_INITIAL_MIMO_NUM_RATES;
		num_retries = IWL_MVM_RS_HT_VHT_RETRIES_PER_RATE;
	} else {
		num_rates = IWL_MVM_RS_INITIAL_LEGACY_NUM_RATES;
		num_retries = IWL_MVM_RS_INITIAL_LEGACY_RETRIES;
		toggle_ant = true;
	}

	rs_fill_rates_for_column(mvm, lq_sta, &rate, lq_cmd->rs_table, &index,
				 num_rates, num_retries, valid_tx_ant,
				 toggle_ant);

	rs_get_lower_rate_down_column(lq_sta, &rate);

	if (is_siso(&rate)) {
		num_rates = IWL_MVM_RS_SECONDARY_SISO_NUM_RATES;
		num_retries = IWL_MVM_RS_SECONDARY_SISO_RETRIES;
		lq_cmd->mimo_delim = index;
	} else if (is_legacy(&rate)) {
		num_rates = IWL_MVM_RS_SECONDARY_LEGACY_NUM_RATES;
		num_retries = IWL_MVM_RS_SECONDARY_LEGACY_RETRIES;
	} else {
		WARN_ON_ONCE(1);
	}

	toggle_ant = true;

	rs_fill_rates_for_column(mvm, lq_sta, &rate, lq_cmd->rs_table, &index,
				 num_rates, num_retries, valid_tx_ant,
				 toggle_ant);

	rs_get_lower_rate_down_column(lq_sta, &rate);

	num_rates = IWL_MVM_RS_SECONDARY_LEGACY_NUM_RATES;
	num_retries = IWL_MVM_RS_SECONDARY_LEGACY_RETRIES;

	rs_fill_rates_for_column(mvm, lq_sta, &rate, lq_cmd->rs_table, &index,
				 num_rates, num_retries, valid_tx_ant,
				 toggle_ant);

	/* update the color of the LQ command (as a counter at bits 1-3) */
	color = LQ_FLAGS_COLOR_INC(LQ_FLAG_COLOR_GET(lq_cmd->flags));
	lq_cmd->flags = LQ_FLAG_COLOR_SET(lq_cmd->flags, color);
}