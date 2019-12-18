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
struct ath5k_pdgain_info {unsigned int pd_points; int /*<<< orphan*/ * pd_pwr; scalar_t__* pd_step; } ;
struct ath5k_eeprom_info {size_t** ee_pdc_to_idx; unsigned int* ee_n_piers; unsigned int* ee_pd_gains; } ;
struct TYPE_2__ {struct ath5k_eeprom_info cap_eeprom; } ;
struct ath5k_hw {TYPE_1__ ah_capabilities; } ;
struct ath5k_chan_pcal_info_rf5112 {scalar_t__* pcdac_x3; int /*<<< orphan*/ * pwr_x3; scalar_t__* pcdac_x0; int /*<<< orphan*/ * pwr_x0; } ;
struct ath5k_chan_pcal_info {int /*<<< orphan*/  min_pwr; struct ath5k_pdgain_info* pd_curves; struct ath5k_chan_pcal_info_rf5112 rf5112_info; } ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 unsigned int AR5K_EEPROM_N_PD_CURVES ; 
 unsigned int AR5K_EEPROM_N_XPD0_POINTS ; 
 unsigned int AR5K_EEPROM_N_XPD3_POINTS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ath5k_eeprom_free_pcal_info (struct ath5k_hw*,int) ; 
 void* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ath5k_eeprom_convert_pcal_info_5112(struct ath5k_hw *ah, int mode,
				struct ath5k_chan_pcal_info *chinfo)
{
	struct ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	struct ath5k_chan_pcal_info_rf5112 *pcinfo;
	u8 *pdgain_idx = ee->ee_pdc_to_idx[mode];
	unsigned int pier, pdg, point;

	/* Fill raw data for each calibration pier */
	for (pier = 0; pier < ee->ee_n_piers[mode]; pier++) {

		pcinfo = &chinfo[pier].rf5112_info;

		/* Allocate pd_curves for this cal pier */
		chinfo[pier].pd_curves =
				kcalloc(AR5K_EEPROM_N_PD_CURVES,
					sizeof(struct ath5k_pdgain_info),
					GFP_KERNEL);

		if (!chinfo[pier].pd_curves)
			goto err_out;

		/* Fill pd_curves */
		for (pdg = 0; pdg < ee->ee_pd_gains[mode]; pdg++) {

			u8 idx = pdgain_idx[pdg];
			struct ath5k_pdgain_info *pd =
					&chinfo[pier].pd_curves[idx];

			/* Lowest gain curve (max power) */
			if (pdg == 0) {
				/* One more point for better accuracy */
				pd->pd_points = AR5K_EEPROM_N_XPD0_POINTS;

				/* Allocate pd points for this curve */
				pd->pd_step = kcalloc(pd->pd_points,
						sizeof(u8), GFP_KERNEL);

				if (!pd->pd_step)
					goto err_out;

				pd->pd_pwr = kcalloc(pd->pd_points,
						sizeof(s16), GFP_KERNEL);

				if (!pd->pd_pwr)
					goto err_out;

				/* Fill raw dataset
				 * (all power levels are in 0.25dB units) */
				pd->pd_step[0] = pcinfo->pcdac_x0[0];
				pd->pd_pwr[0] = pcinfo->pwr_x0[0];

				for (point = 1; point < pd->pd_points;
				point++) {
					/* Absolute values */
					pd->pd_pwr[point] =
						pcinfo->pwr_x0[point];

					/* Deltas */
					pd->pd_step[point] =
						pd->pd_step[point - 1] +
						pcinfo->pcdac_x0[point];
				}

				/* Set min power for this frequency */
				chinfo[pier].min_pwr = pd->pd_pwr[0];

			/* Highest gain curve (min power) */
			} else if (pdg == 1) {

				pd->pd_points = AR5K_EEPROM_N_XPD3_POINTS;

				/* Allocate pd points for this curve */
				pd->pd_step = kcalloc(pd->pd_points,
						sizeof(u8), GFP_KERNEL);

				if (!pd->pd_step)
					goto err_out;

				pd->pd_pwr = kcalloc(pd->pd_points,
						sizeof(s16), GFP_KERNEL);

				if (!pd->pd_pwr)
					goto err_out;

				/* Fill raw dataset
				 * (all power levels are in 0.25dB units) */
				for (point = 0; point < pd->pd_points;
				point++) {
					/* Absolute values */
					pd->pd_pwr[point] =
						pcinfo->pwr_x3[point];

					/* Fixed points */
					pd->pd_step[point] =
						pcinfo->pcdac_x3[point];
				}

				/* Since we have a higher gain curve
				 * override min power */
				chinfo[pier].min_pwr = pd->pd_pwr[0];
			}
		}
	}

	return 0;

err_out:
	ath5k_eeprom_free_pcal_info(ah, mode);
	return -ENOMEM;
}