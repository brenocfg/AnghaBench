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
struct ieee80211_channel {int center_freq; } ;
struct ath5k_hw {int ah_radio; struct ieee80211_channel* ah_current_channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR5K_PHY_CCKTXCTL ; 
 int /*<<< orphan*/  AR5K_PHY_CCKTXCTL_JAPAN ; 
 int /*<<< orphan*/  AR5K_PHY_CCKTXCTL_WORLD ; 
 int /*<<< orphan*/  AR5K_REG_ENABLE_BITS (struct ath5k_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  AR5K_RF2317 131 
#define  AR5K_RF2425 130 
#define  AR5K_RF5110 129 
#define  AR5K_RF5111 128 
 int /*<<< orphan*/  ATH5K_ERR (struct ath5k_hw*,char*,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  ath5k_channel_ok (struct ath5k_hw*,struct ieee80211_channel*) ; 
 int ath5k_hw_rf2425_channel (struct ath5k_hw*,struct ieee80211_channel*) ; 
 int ath5k_hw_rf5110_channel (struct ath5k_hw*,struct ieee80211_channel*) ; 
 int ath5k_hw_rf5111_channel (struct ath5k_hw*,struct ieee80211_channel*) ; 
 int ath5k_hw_rf5112_channel (struct ath5k_hw*,struct ieee80211_channel*) ; 

__attribute__((used)) static int
ath5k_hw_channel(struct ath5k_hw *ah,
		struct ieee80211_channel *channel)
{
	int ret;
	/*
	 * Check bounds supported by the PHY (we don't care about regulatory
	 * restrictions at this point).
	 */
	if (!ath5k_channel_ok(ah, channel)) {
		ATH5K_ERR(ah,
			"channel frequency (%u MHz) out of supported "
			"band range\n",
			channel->center_freq);
		return -EINVAL;
	}

	/*
	 * Set the channel and wait
	 */
	switch (ah->ah_radio) {
	case AR5K_RF5110:
		ret = ath5k_hw_rf5110_channel(ah, channel);
		break;
	case AR5K_RF5111:
		ret = ath5k_hw_rf5111_channel(ah, channel);
		break;
	case AR5K_RF2317:
	case AR5K_RF2425:
		ret = ath5k_hw_rf2425_channel(ah, channel);
		break;
	default:
		ret = ath5k_hw_rf5112_channel(ah, channel);
		break;
	}

	if (ret)
		return ret;

	/* Set JAPAN setting for channel 14 */
	if (channel->center_freq == 2484) {
		AR5K_REG_ENABLE_BITS(ah, AR5K_PHY_CCKTXCTL,
				AR5K_PHY_CCKTXCTL_JAPAN);
	} else {
		AR5K_REG_ENABLE_BITS(ah, AR5K_PHY_CCKTXCTL,
				AR5K_PHY_CCKTXCTL_WORLD);
	}

	ah->ah_current_channel = channel;

	return 0;
}