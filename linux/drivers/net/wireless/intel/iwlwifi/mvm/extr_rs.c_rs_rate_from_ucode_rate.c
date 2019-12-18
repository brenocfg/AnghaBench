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
struct rs_rate {scalar_t__ index; int ant; int sgi; int ldpc; int stbc; int bfer; int bw; int /*<<< orphan*/  type; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IWL_RATE_INVALID ; 
 int /*<<< orphan*/  LQ_HE_MIMO2 ; 
 int /*<<< orphan*/  LQ_HE_SISO ; 
 int /*<<< orphan*/  LQ_HT_MIMO2 ; 
 int /*<<< orphan*/  LQ_HT_SISO ; 
 int /*<<< orphan*/  LQ_LEGACY_A ; 
 int /*<<< orphan*/  LQ_LEGACY_G ; 
 int /*<<< orphan*/  LQ_VHT_MIMO2 ; 
 int /*<<< orphan*/  LQ_VHT_SISO ; 
 int NL80211_BAND_5GHZ ; 
 int const RATE_HT_MCS_NSS_MSK ; 
 int const RATE_HT_MCS_NSS_POS ; 
 int const RATE_MCS_ANT_ABC_MSK ; 
 int RATE_MCS_ANT_POS ; 
 int const RATE_MCS_BF_MSK ; 
 int RATE_MCS_CHAN_WIDTH_80 ; 
 int const RATE_MCS_CHAN_WIDTH_MSK ; 
 int const RATE_MCS_HE_MSK ; 
 int const RATE_MCS_HT_MSK ; 
 int const RATE_MCS_LDPC_MSK ; 
 int const RATE_MCS_SGI_MSK ; 
 int const RATE_MCS_STBC_MSK ; 
 int const RATE_MCS_VHT_MSK ; 
 int const RATE_VHT_MCS_NSS_MSK ; 
 int const RATE_VHT_MCS_NSS_POS ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int,int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int get_num_of_ant_from_rate (int const) ; 
 int /*<<< orphan*/  is_he (struct rs_rate*) ; 
 int /*<<< orphan*/  is_vht (struct rs_rate*) ; 
 scalar_t__ iwl_hwrate_to_plcp_idx (int const) ; 
 int /*<<< orphan*/  memset (struct rs_rate*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rs_rate_from_ucode_rate(const u32 ucode_rate,
				   enum nl80211_band band,
				   struct rs_rate *rate)
{
	u32 ant_msk = ucode_rate & RATE_MCS_ANT_ABC_MSK;
	u8 num_of_ant = get_num_of_ant_from_rate(ucode_rate);
	u8 nss;

	memset(rate, 0, sizeof(*rate));
	rate->index = iwl_hwrate_to_plcp_idx(ucode_rate);

	if (rate->index == IWL_RATE_INVALID)
		return -EINVAL;

	rate->ant = (ant_msk >> RATE_MCS_ANT_POS);

	/* Legacy */
	if (!(ucode_rate & RATE_MCS_HT_MSK) &&
	    !(ucode_rate & RATE_MCS_VHT_MSK) &&
	    !(ucode_rate & RATE_MCS_HE_MSK)) {
		if (num_of_ant == 1) {
			if (band == NL80211_BAND_5GHZ)
				rate->type = LQ_LEGACY_A;
			else
				rate->type = LQ_LEGACY_G;
		}

		return 0;
	}

	/* HT, VHT or HE */
	if (ucode_rate & RATE_MCS_SGI_MSK)
		rate->sgi = true;
	if (ucode_rate & RATE_MCS_LDPC_MSK)
		rate->ldpc = true;
	if (ucode_rate & RATE_MCS_STBC_MSK)
		rate->stbc = true;
	if (ucode_rate & RATE_MCS_BF_MSK)
		rate->bfer = true;

	rate->bw = ucode_rate & RATE_MCS_CHAN_WIDTH_MSK;

	if (ucode_rate & RATE_MCS_HT_MSK) {
		nss = ((ucode_rate & RATE_HT_MCS_NSS_MSK) >>
		       RATE_HT_MCS_NSS_POS) + 1;

		if (nss == 1) {
			rate->type = LQ_HT_SISO;
			WARN_ONCE(!rate->stbc && !rate->bfer && num_of_ant != 1,
				  "stbc %d bfer %d",
				  rate->stbc, rate->bfer);
		} else if (nss == 2) {
			rate->type = LQ_HT_MIMO2;
			WARN_ON_ONCE(num_of_ant != 2);
		} else {
			WARN_ON_ONCE(1);
		}
	} else if (ucode_rate & RATE_MCS_VHT_MSK) {
		nss = ((ucode_rate & RATE_VHT_MCS_NSS_MSK) >>
		       RATE_VHT_MCS_NSS_POS) + 1;

		if (nss == 1) {
			rate->type = LQ_VHT_SISO;
			WARN_ONCE(!rate->stbc && !rate->bfer && num_of_ant != 1,
				  "stbc %d bfer %d",
				  rate->stbc, rate->bfer);
		} else if (nss == 2) {
			rate->type = LQ_VHT_MIMO2;
			WARN_ON_ONCE(num_of_ant != 2);
		} else {
			WARN_ON_ONCE(1);
		}
	} else if (ucode_rate & RATE_MCS_HE_MSK) {
		nss = ((ucode_rate & RATE_VHT_MCS_NSS_MSK) >>
		      RATE_VHT_MCS_NSS_POS) + 1;

		if (nss == 1) {
			rate->type = LQ_HE_SISO;
			WARN_ONCE(!rate->stbc && !rate->bfer && num_of_ant != 1,
				  "stbc %d bfer %d", rate->stbc, rate->bfer);
		} else if (nss == 2) {
			rate->type = LQ_HE_MIMO2;
			WARN_ON_ONCE(num_of_ant != 2);
		} else {
			WARN_ON_ONCE(1);
		}
	}

	WARN_ON_ONCE(rate->bw == RATE_MCS_CHAN_WIDTH_80 &&
		     !is_he(rate) && !is_vht(rate));

	return 0;
}