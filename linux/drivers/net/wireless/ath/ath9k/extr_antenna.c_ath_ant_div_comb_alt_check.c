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
struct ath_hw_antcomb_conf {scalar_t__ main_lna_conf; scalar_t__ alt_lna_conf; int div_group; } ;
struct ath_ant_comb {int low_rssi_thresh; int ant_ratio; } ;

/* Variables and functions */
 int ATH_ANT_DIV_COMB_ALT_ANT_RATIO ; 
 scalar_t__ ATH_ANT_DIV_COMB_LNA1 ; 
 scalar_t__ ATH_ANT_DIV_COMB_LNA2 ; 

__attribute__((used)) static inline bool ath_ant_div_comb_alt_check(struct ath_hw_antcomb_conf *conf,
					      struct ath_ant_comb *antcomb,
					      int alt_ratio, int alt_rssi_avg,
					      int main_rssi_avg)
{
	bool result, set1, set2;

	result = set1 = set2 = false;

	if (conf->main_lna_conf == ATH_ANT_DIV_COMB_LNA2 &&
	    conf->alt_lna_conf == ATH_ANT_DIV_COMB_LNA1)
		set1 = true;

	if (conf->main_lna_conf == ATH_ANT_DIV_COMB_LNA1 &&
	    conf->alt_lna_conf == ATH_ANT_DIV_COMB_LNA2)
		set2 = true;

	switch (conf->div_group) {
	case 0:
		if (alt_ratio > ATH_ANT_DIV_COMB_ALT_ANT_RATIO)
			result = true;
		break;
	case 1:
	case 2:
		if (alt_rssi_avg < 4 || alt_rssi_avg < antcomb->low_rssi_thresh)
			break;

		if ((set1 && (alt_rssi_avg >= (main_rssi_avg - 5))) ||
		    (set2 && (alt_rssi_avg >= (main_rssi_avg - 2))) ||
		    (alt_ratio > antcomb->ant_ratio))
			result = true;

		break;
	case 3:
		if (alt_rssi_avg < 4 || alt_rssi_avg < antcomb->low_rssi_thresh)
			break;

		if ((set1 && (alt_rssi_avg >= (main_rssi_avg - 3))) ||
		    (set2 && (alt_rssi_avg >= (main_rssi_avg + 3))) ||
		    (alt_ratio > antcomb->ant_ratio))
			result = true;

		break;
	}

	return result;
}