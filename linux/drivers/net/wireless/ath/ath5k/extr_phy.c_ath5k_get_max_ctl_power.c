#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  scalar_t__ u32 ;
struct ieee80211_channel {scalar_t__ center_freq; int hw_value; int /*<<< orphan*/  band; } ;
struct ath_regulatory {int dummy; } ;
struct TYPE_4__ {int txp_max_pwr; } ;
struct ath5k_eeprom_info {size_t* ee_ctl; size_t ee_ctls; struct ath5k_edge_power* ee_ctl_pwr; } ;
struct TYPE_3__ {struct ath5k_eeprom_info cap_eeprom; } ;
struct ath5k_hw {TYPE_2__ ah_txpower; int /*<<< orphan*/  ah_bwmode; TYPE_1__ ah_capabilities; } ;
struct ath5k_edge_power {scalar_t__ freq; scalar_t__ edge; } ;
typedef  int s16 ;

/* Variables and functions */
 int /*<<< orphan*/  AR5K_BWMODE_40MHZ ; 
 size_t AR5K_CTL_11A ; 
 size_t AR5K_CTL_11B ; 
 size_t AR5K_CTL_11G ; 
 size_t AR5K_CTL_TURBO ; 
 size_t AR5K_CTL_TURBOG ; 
 size_t AR5K_EEPROM_N_EDGES ; 
#define  AR5K_MODE_11A 130 
#define  AR5K_MODE_11B 129 
#define  AR5K_MODE_11G 128 
 struct ath_regulatory* ath5k_hw_regulatory (struct ath5k_hw*) ; 
 size_t ath_regd_get_band_ctl (struct ath_regulatory*,int /*<<< orphan*/ ) ; 
 int min (int,int) ; 

__attribute__((used)) static void
ath5k_get_max_ctl_power(struct ath5k_hw *ah,
			struct ieee80211_channel *channel)
{
	struct ath_regulatory *regulatory = ath5k_hw_regulatory(ah);
	struct ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	struct ath5k_edge_power *rep = ee->ee_ctl_pwr;
	u8 *ctl_val = ee->ee_ctl;
	s16 max_chan_pwr = ah->ah_txpower.txp_max_pwr / 4;
	s16 edge_pwr = 0;
	u8 rep_idx;
	u8 i, ctl_mode;
	u8 ctl_idx = 0xFF;
	u32 target = channel->center_freq;

	ctl_mode = ath_regd_get_band_ctl(regulatory, channel->band);

	switch (channel->hw_value) {
	case AR5K_MODE_11A:
		if (ah->ah_bwmode == AR5K_BWMODE_40MHZ)
			ctl_mode |= AR5K_CTL_TURBO;
		else
			ctl_mode |= AR5K_CTL_11A;
		break;
	case AR5K_MODE_11G:
		if (ah->ah_bwmode == AR5K_BWMODE_40MHZ)
			ctl_mode |= AR5K_CTL_TURBOG;
		else
			ctl_mode |= AR5K_CTL_11G;
		break;
	case AR5K_MODE_11B:
		ctl_mode |= AR5K_CTL_11B;
		break;
	default:
		return;
	}

	for (i = 0; i < ee->ee_ctls; i++) {
		if (ctl_val[i] == ctl_mode) {
			ctl_idx = i;
			break;
		}
	}

	/* If we have a CTL dataset available grab it and find the
	 * edge power for our frequency */
	if (ctl_idx == 0xFF)
		return;

	/* Edge powers are sorted by frequency from lower
	 * to higher. Each CTL corresponds to 8 edge power
	 * measurements. */
	rep_idx = ctl_idx * AR5K_EEPROM_N_EDGES;

	/* Don't do boundaries check because we
	 * might have more that one bands defined
	 * for this mode */

	/* Get the edge power that's closer to our
	 * frequency */
	for (i = 0; i < AR5K_EEPROM_N_EDGES; i++) {
		rep_idx += i;
		if (target <= rep[rep_idx].freq)
			edge_pwr = (s16) rep[rep_idx].edge;
	}

	if (edge_pwr)
		ah->ah_txpower.txp_max_pwr = 4 * min(edge_pwr, max_chan_pwr);
}