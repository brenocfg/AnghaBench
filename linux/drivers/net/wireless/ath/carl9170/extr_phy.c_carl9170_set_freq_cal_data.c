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
struct ieee80211_channel {int band; int /*<<< orphan*/  center_freq; } ;
struct ar9170_calibration_data_per_freq {int /*<<< orphan*/ ** pwr_pdg; int /*<<< orphan*/ ** vpd_pdg; } ;
struct TYPE_2__ {int* cal_freq_pier_2G; int* cal_freq_pier_5G; struct ar9170_calibration_data_per_freq** cal_pier_data_5G; struct ar9170_calibration_data_per_freq** cal_pier_data_2G; } ;
struct ar9170 {TYPE_1__ eeprom; } ;

/* Variables and functions */
 int AR5416_MAX_CHAINS ; 
 int /*<<< orphan*/  AR5416_NUM_2G_CAL_PIERS ; 
 int /*<<< orphan*/  AR5416_NUM_5G_CAL_PIERS ; 
 int AR5416_PD_GAIN_ICEPTS ; 
 int EINVAL ; 
#define  NL80211_BAND_2GHZ 129 
#define  NL80211_BAND_5GHZ 128 
 int carl9170_find_freq_idx (int,int*,int) ; 
 int carl9170_interpolate_u8 (int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int carl9170_interpolate_val (int,int*,int*) ; 
 int /*<<< orphan*/  carl9170_regwrite (int,int) ; 
 int /*<<< orphan*/  carl9170_regwrite_begin (struct ar9170*) ; 
 int /*<<< orphan*/  carl9170_regwrite_finish () ; 
 int carl9170_regwrite_result () ; 

__attribute__((used)) static int carl9170_set_freq_cal_data(struct ar9170 *ar,
	struct ieee80211_channel *channel)
{
	u8 *cal_freq_pier;
	u8 vpds[2][AR5416_PD_GAIN_ICEPTS];
	u8 pwrs[2][AR5416_PD_GAIN_ICEPTS];
	int chain, idx, i;
	u32 phy_data = 0;
	u8 f, tmp;

	switch (channel->band) {
	case NL80211_BAND_2GHZ:
		f = channel->center_freq - 2300;
		cal_freq_pier = ar->eeprom.cal_freq_pier_2G;
		i = AR5416_NUM_2G_CAL_PIERS - 1;
		break;

	case NL80211_BAND_5GHZ:
		f = (channel->center_freq - 4800) / 5;
		cal_freq_pier = ar->eeprom.cal_freq_pier_5G;
		i = AR5416_NUM_5G_CAL_PIERS - 1;
		break;

	default:
		return -EINVAL;
	}

	for (; i >= 0; i--) {
		if (cal_freq_pier[i] != 0xff)
			break;
	}
	if (i < 0)
		return -EINVAL;

	idx = carl9170_find_freq_idx(i, cal_freq_pier, f);

	carl9170_regwrite_begin(ar);

	for (chain = 0; chain < AR5416_MAX_CHAINS; chain++) {
		for (i = 0; i < AR5416_PD_GAIN_ICEPTS; i++) {
			struct ar9170_calibration_data_per_freq *cal_pier_data;
			int j;

			switch (channel->band) {
			case NL80211_BAND_2GHZ:
				cal_pier_data = &ar->eeprom.
					cal_pier_data_2G[chain][idx];
				break;

			case NL80211_BAND_5GHZ:
				cal_pier_data = &ar->eeprom.
					cal_pier_data_5G[chain][idx];
				break;

			default:
				return -EINVAL;
			}

			for (j = 0; j < 2; j++) {
				vpds[j][i] = carl9170_interpolate_u8(f,
					cal_freq_pier[idx],
					cal_pier_data->vpd_pdg[j][i],
					cal_freq_pier[idx + 1],
					cal_pier_data[1].vpd_pdg[j][i]);

				pwrs[j][i] = carl9170_interpolate_u8(f,
					cal_freq_pier[idx],
					cal_pier_data->pwr_pdg[j][i],
					cal_freq_pier[idx + 1],
					cal_pier_data[1].pwr_pdg[j][i]) / 2;
			}
		}

		for (i = 0; i < 76; i++) {
			if (i < 25) {
				tmp = carl9170_interpolate_val(i, &pwrs[0][0],
							       &vpds[0][0]);
			} else {
				tmp = carl9170_interpolate_val(i - 12,
							       &pwrs[1][0],
							       &vpds[1][0]);
			}

			phy_data |= tmp << ((i & 3) << 3);
			if ((i & 3) == 3) {
				carl9170_regwrite(0x1c6280 + chain * 0x1000 +
						  (i & ~3), phy_data);
				phy_data = 0;
			}
		}

		for (i = 19; i < 32; i++)
			carl9170_regwrite(0x1c6280 + chain * 0x1000 + (i << 2),
					  0x0);
	}

	carl9170_regwrite_finish();
	return carl9170_regwrite_result();
}