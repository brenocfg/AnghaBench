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
typedef  int u32 ;
struct iwl_scale_tbl_info {int is_SGI; int is_ht40; int is_dup; int ant_type; int /*<<< orphan*/  lq_type; int /*<<< orphan*/  max_search; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IWL_MAX_11N_MIMO3_SEARCH ; 
 int /*<<< orphan*/  IWL_MAX_SEARCH ; 
 int IWL_RATE_INVALID ; 
 int IWL_RATE_MIMO2_60M_PLCP ; 
 int IWL_RATE_SISO_60M_PLCP ; 
 int /*<<< orphan*/  LQ_A ; 
 int /*<<< orphan*/  LQ_G ; 
 int /*<<< orphan*/  LQ_MIMO2 ; 
 int /*<<< orphan*/  LQ_MIMO3 ; 
 int /*<<< orphan*/  LQ_NONE ; 
 int /*<<< orphan*/  LQ_SISO ; 
 int NL80211_BAND_5GHZ ; 
 int const RATE_MCS_ANT_ABC_MSK ; 
 int RATE_MCS_ANT_POS ; 
 int const RATE_MCS_DUP_MSK ; 
 int const RATE_MCS_HT40_MSK ; 
 int const RATE_MCS_HT_MSK ; 
 int const RATE_MCS_SGI_MSK ; 
 int get_num_of_ant_from_rate (int const) ; 
 int iwl_hwrate_to_plcp_idx (int const) ; 
 int /*<<< orphan*/  memset (struct iwl_scale_tbl_info*,int /*<<< orphan*/ ,int) ; 
 int rs_extract_rate (int const) ; 

__attribute__((used)) static int rs_get_tbl_info_from_mcs(const u32 rate_n_flags,
				    enum nl80211_band band,
				    struct iwl_scale_tbl_info *tbl,
				    int *rate_idx)
{
	u32 ant_msk = (rate_n_flags & RATE_MCS_ANT_ABC_MSK);
	u8 num_of_ant = get_num_of_ant_from_rate(rate_n_flags);
	u8 mcs;

	memset(tbl, 0, sizeof(struct iwl_scale_tbl_info));
	*rate_idx = iwl_hwrate_to_plcp_idx(rate_n_flags);

	if (*rate_idx  == IWL_RATE_INVALID) {
		*rate_idx = -1;
		return -EINVAL;
	}
	tbl->is_SGI = 0;	/* default legacy setup */
	tbl->is_ht40 = 0;
	tbl->is_dup = 0;
	tbl->ant_type = (ant_msk >> RATE_MCS_ANT_POS);
	tbl->lq_type = LQ_NONE;
	tbl->max_search = IWL_MAX_SEARCH;

	/* legacy rate format */
	if (!(rate_n_flags & RATE_MCS_HT_MSK)) {
		if (num_of_ant == 1) {
			if (band == NL80211_BAND_5GHZ)
				tbl->lq_type = LQ_A;
			else
				tbl->lq_type = LQ_G;
		}
	/* HT rate format */
	} else {
		if (rate_n_flags & RATE_MCS_SGI_MSK)
			tbl->is_SGI = 1;

		if ((rate_n_flags & RATE_MCS_HT40_MSK) ||
		    (rate_n_flags & RATE_MCS_DUP_MSK))
			tbl->is_ht40 = 1;

		if (rate_n_flags & RATE_MCS_DUP_MSK)
			tbl->is_dup = 1;

		mcs = rs_extract_rate(rate_n_flags);

		/* SISO */
		if (mcs <= IWL_RATE_SISO_60M_PLCP) {
			if (num_of_ant == 1)
				tbl->lq_type = LQ_SISO; /*else NONE*/
		/* MIMO2 */
		} else if (mcs <= IWL_RATE_MIMO2_60M_PLCP) {
			if (num_of_ant == 2)
				tbl->lq_type = LQ_MIMO2;
		/* MIMO3 */
		} else {
			if (num_of_ant == 3) {
				tbl->max_search = IWL_MAX_11N_MIMO3_SEARCH;
				tbl->lq_type = LQ_MIMO3;
			}
		}
	}
	return 0;
}