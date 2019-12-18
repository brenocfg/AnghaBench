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
typedef  size_t u8 ;
struct ath5k_pdgain_info {size_t pd_points; int* pd_pwr; int /*<<< orphan*/ * pd_step; } ;
struct ath5k_eeprom_info {size_t** ee_pdc_to_idx; size_t* ee_n_piers; size_t* ee_x_gain; int* ee_pd_gains; } ;
struct TYPE_2__ {struct ath5k_eeprom_info cap_eeprom; } ;
struct ath5k_hw {TYPE_1__ ah_capabilities; } ;
struct ath5k_chan_pcal_info_rf5111 {int* pwr; int /*<<< orphan*/ * pcdac; } ;
struct ath5k_chan_pcal_info {int min_pwr; int max_pwr; struct ath5k_pdgain_info* pd_curves; struct ath5k_chan_pcal_info_rf5111 rf5111_info; } ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 size_t AR5K_EEPROM_N_PD_CURVES ; 
 size_t AR5K_EEPROM_N_PWR_POINTS_5111 ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ath5k_eeprom_free_pcal_info (struct ath5k_hw*,int) ; 
 void* kcalloc (size_t,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ath5k_eeprom_convert_pcal_info_5111(struct ath5k_hw *ah, int mode,
				struct ath5k_chan_pcal_info *chinfo)
{
	struct ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	struct ath5k_chan_pcal_info_rf5111 *pcinfo;
	struct ath5k_pdgain_info *pd;
	u8 pier, point, idx;
	u8 *pdgain_idx = ee->ee_pdc_to_idx[mode];

	/* Fill raw data for each calibration pier */
	for (pier = 0; pier < ee->ee_n_piers[mode]; pier++) {

		pcinfo = &chinfo[pier].rf5111_info;

		/* Allocate pd_curves for this cal pier */
		chinfo[pier].pd_curves =
			kcalloc(AR5K_EEPROM_N_PD_CURVES,
				sizeof(struct ath5k_pdgain_info),
				GFP_KERNEL);

		if (!chinfo[pier].pd_curves)
			goto err_out;

		/* Only one curve for RF5111
		 * find out which one and place
		 * in pd_curves.
		 * Note: ee_x_gain is reversed here */
		for (idx = 0; idx < AR5K_EEPROM_N_PD_CURVES; idx++) {

			if (!((ee->ee_x_gain[mode] >> idx) & 0x1)) {
				pdgain_idx[0] = idx;
				break;
			}
		}

		ee->ee_pd_gains[mode] = 1;

		pd = &chinfo[pier].pd_curves[idx];

		pd->pd_points = AR5K_EEPROM_N_PWR_POINTS_5111;

		/* Allocate pd points for this curve */
		pd->pd_step = kcalloc(AR5K_EEPROM_N_PWR_POINTS_5111,
					sizeof(u8), GFP_KERNEL);
		if (!pd->pd_step)
			goto err_out;

		pd->pd_pwr = kcalloc(AR5K_EEPROM_N_PWR_POINTS_5111,
					sizeof(s16), GFP_KERNEL);
		if (!pd->pd_pwr)
			goto err_out;

		/* Fill raw dataset
		 * (convert power to 0.25dB units
		 * for RF5112 compatibility) */
		for (point = 0; point < pd->pd_points; point++) {

			/* Absolute values */
			pd->pd_pwr[point] = 2 * pcinfo->pwr[point];

			/* Already sorted */
			pd->pd_step[point] = pcinfo->pcdac[point];
		}

		/* Set min/max pwr */
		chinfo[pier].min_pwr = pd->pd_pwr[0];
		chinfo[pier].max_pwr = pd->pd_pwr[10];

	}

	return 0;

err_out:
	ath5k_eeprom_free_pcal_info(ah, mode);
	return -ENOMEM;
}