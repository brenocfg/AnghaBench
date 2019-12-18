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
struct ieee80211_tx_rate {int flags; int idx; } ;
struct ieee80211_tx_info {scalar_t__ band; } ;
struct ar9170 {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int AR9170_TX_PHY_BW_40MHZ ; 
 int AR9170_TX_PHY_BW_40MHZ_DUP ; 
 int AR9170_TX_PHY_BW_S ; 
 int /*<<< orphan*/  AR9170_TX_PHY_MCS ; 
 int AR9170_TX_PHY_MOD_CCK ; 
 int AR9170_TX_PHY_MOD_HT ; 
 int AR9170_TX_PHY_MOD_OFDM ; 
 int AR9170_TX_PHY_RATE_CCK_11M ; 
 int AR9170_TX_PHY_SHORT_GI ; 
 int /*<<< orphan*/  AR9170_TX_PHY_TXCHAIN ; 
 int AR9170_TX_PHY_TX_HEAVY_CLIP_S ; 
 int /*<<< orphan*/  AR9170_TX_PHY_TX_PWR ; 
 int IEEE80211_TX_RC_40_MHZ_WIDTH ; 
 int IEEE80211_TX_RC_DUP_DATA ; 
 int IEEE80211_TX_RC_MCS ; 
 int IEEE80211_TX_RC_SHORT_GI ; 
 scalar_t__ NL80211_BAND_2GHZ ; 
 int SET_CONSTVAL (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  SET_VAL (int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  carl9170_tx_rate_tpc_chains (struct ar9170*,struct ieee80211_tx_info*,struct ieee80211_tx_rate*,unsigned int*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 

__attribute__((used)) static __le32 carl9170_tx_physet(struct ar9170 *ar,
	struct ieee80211_tx_info *info, struct ieee80211_tx_rate *txrate)
{
	unsigned int power = 0, chains = 0, phyrate = 0;
	__le32 tmp;

	tmp = cpu_to_le32(0);

	if (txrate->flags & IEEE80211_TX_RC_40_MHZ_WIDTH)
		tmp |= cpu_to_le32(AR9170_TX_PHY_BW_40MHZ <<
			AR9170_TX_PHY_BW_S);
	/* this works because 40 MHz is 2 and dup is 3 */
	if (txrate->flags & IEEE80211_TX_RC_DUP_DATA)
		tmp |= cpu_to_le32(AR9170_TX_PHY_BW_40MHZ_DUP <<
			AR9170_TX_PHY_BW_S);

	if (txrate->flags & IEEE80211_TX_RC_SHORT_GI)
		tmp |= cpu_to_le32(AR9170_TX_PHY_SHORT_GI);

	if (txrate->flags & IEEE80211_TX_RC_MCS) {
		SET_VAL(AR9170_TX_PHY_MCS, phyrate, txrate->idx);

		/* heavy clip control */
		tmp |= cpu_to_le32((txrate->idx & 0x7) <<
			AR9170_TX_PHY_TX_HEAVY_CLIP_S);

		tmp |= cpu_to_le32(AR9170_TX_PHY_MOD_HT);

		/*
		 * green field preamble does not work.
		 *
		 * if (txrate->flags & IEEE80211_TX_RC_GREEN_FIELD)
		 * tmp |= cpu_to_le32(AR9170_TX_PHY_GREENFIELD);
		 */
	} else {
		if (info->band == NL80211_BAND_2GHZ) {
			if (txrate->idx <= AR9170_TX_PHY_RATE_CCK_11M)
				tmp |= cpu_to_le32(AR9170_TX_PHY_MOD_CCK);
			else
				tmp |= cpu_to_le32(AR9170_TX_PHY_MOD_OFDM);
		} else {
			tmp |= cpu_to_le32(AR9170_TX_PHY_MOD_OFDM);
		}

		/*
		 * short preamble seems to be broken too.
		 *
		 * if (txrate->flags & IEEE80211_TX_RC_USE_SHORT_PREAMBLE)
		 *	tmp |= cpu_to_le32(AR9170_TX_PHY_SHORT_PREAMBLE);
		 */
	}
	carl9170_tx_rate_tpc_chains(ar, info, txrate,
				    &phyrate, &power, &chains);

	tmp |= cpu_to_le32(SET_CONSTVAL(AR9170_TX_PHY_MCS, phyrate));
	tmp |= cpu_to_le32(SET_CONSTVAL(AR9170_TX_PHY_TX_PWR, power));
	tmp |= cpu_to_le32(SET_CONSTVAL(AR9170_TX_PHY_TXCHAIN, chains));
	return tmp;
}