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
struct TYPE_2__ {size_t* txp_pd_table; size_t** tmpL; int txp_min_idx; } ;
struct ath5k_hw {TYPE_1__ ah_txpower; } ;
typedef  int s16 ;

/* Variables and functions */
 int AR5K_EEPROM_N_PD_GAINS ; 
 int AR5K_EEPROM_POWER_TABLE_SIZE ; 
 int /*<<< orphan*/  AR5K_PHY_TPC_RG5 ; 
 size_t AR5K_PHY_TPC_RG5_PD_GAIN_BOUNDARY_1 ; 
 size_t AR5K_PHY_TPC_RG5_PD_GAIN_BOUNDARY_2 ; 
 size_t AR5K_PHY_TPC_RG5_PD_GAIN_BOUNDARY_3 ; 
 size_t AR5K_PHY_TPC_RG5_PD_GAIN_BOUNDARY_4 ; 
 size_t AR5K_PHY_TPC_RG5_PD_GAIN_OVERLAP ; 
 int AR5K_REG_SM (size_t,size_t) ; 
 size_t AR5K_TUNE_MAX_TXPOWER ; 
 scalar_t__ ath5k_hw_reg_read (struct ath5k_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath5k_hw_reg_write (struct ath5k_hw*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ath5k_combine_pwr_to_pdadc_curves(struct ath5k_hw *ah,
			s16 *pwr_min, s16 *pwr_max, u8 pdcurves)
{
	u8 gain_boundaries[AR5K_EEPROM_N_PD_GAINS];
	u8 *pdadc_out = ah->ah_txpower.txp_pd_table;
	u8 *pdadc_tmp;
	s16 pdadc_0;
	u8 pdadc_i, pdadc_n, pwr_step, pdg, max_idx, table_size;
	u8 pd_gain_overlap;

	/* Note: Register value is initialized on initvals
	 * there is no feedback from hw.
	 * XXX: What about pd_gain_overlap from EEPROM ? */
	pd_gain_overlap = (u8) ath5k_hw_reg_read(ah, AR5K_PHY_TPC_RG5) &
		AR5K_PHY_TPC_RG5_PD_GAIN_OVERLAP;

	/* Create final PDADC table */
	for (pdg = 0, pdadc_i = 0; pdg < pdcurves; pdg++) {
		pdadc_tmp = ah->ah_txpower.tmpL[pdg];

		if (pdg == pdcurves - 1)
			/* 2 dB boundary stretch for last
			 * (higher power) curve */
			gain_boundaries[pdg] = pwr_max[pdg] + 4;
		else
			/* Set gain boundary in the middle
			 * between this curve and the next one */
			gain_boundaries[pdg] =
				(pwr_max[pdg] + pwr_min[pdg + 1]) / 2;

		/* Sanity check in case our 2 db stretch got out of
		 * range. */
		if (gain_boundaries[pdg] > AR5K_TUNE_MAX_TXPOWER)
			gain_boundaries[pdg] = AR5K_TUNE_MAX_TXPOWER;

		/* For the first curve (lower power)
		 * start from 0 dB */
		if (pdg == 0)
			pdadc_0 = 0;
		else
			/* For the other curves use the gain overlap */
			pdadc_0 = (gain_boundaries[pdg - 1] - pwr_min[pdg]) -
							pd_gain_overlap;

		/* Force each power step to be at least 0.5 dB */
		if ((pdadc_tmp[1] - pdadc_tmp[0]) > 1)
			pwr_step = pdadc_tmp[1] - pdadc_tmp[0];
		else
			pwr_step = 1;

		/* If pdadc_0 is negative, we need to extrapolate
		 * below this pdgain by a number of pwr_steps */
		while ((pdadc_0 < 0) && (pdadc_i < 128)) {
			s16 tmp = pdadc_tmp[0] + pdadc_0 * pwr_step;
			pdadc_out[pdadc_i++] = (tmp < 0) ? 0 : (u8) tmp;
			pdadc_0++;
		}

		/* Set last pwr level, using gain boundaries */
		pdadc_n = gain_boundaries[pdg] + pd_gain_overlap - pwr_min[pdg];
		/* Limit it to be inside pwr range */
		table_size = pwr_max[pdg] - pwr_min[pdg];
		max_idx = (pdadc_n < table_size) ? pdadc_n : table_size;

		/* Fill pdadc_out table */
		while (pdadc_0 < max_idx && pdadc_i < 128)
			pdadc_out[pdadc_i++] = pdadc_tmp[pdadc_0++];

		/* Need to extrapolate above this pdgain? */
		if (pdadc_n <= max_idx)
			continue;

		/* Force each power step to be at least 0.5 dB */
		if ((pdadc_tmp[table_size - 1] - pdadc_tmp[table_size - 2]) > 1)
			pwr_step = pdadc_tmp[table_size - 1] -
						pdadc_tmp[table_size - 2];
		else
			pwr_step = 1;

		/* Extrapolate above */
		while ((pdadc_0 < (s16) pdadc_n) &&
		(pdadc_i < AR5K_EEPROM_POWER_TABLE_SIZE * 2)) {
			s16 tmp = pdadc_tmp[table_size - 1] +
					(pdadc_0 - max_idx) * pwr_step;
			pdadc_out[pdadc_i++] = (tmp > 127) ? 127 : (u8) tmp;
			pdadc_0++;
		}
	}

	while (pdg < AR5K_EEPROM_N_PD_GAINS) {
		gain_boundaries[pdg] = gain_boundaries[pdg - 1];
		pdg++;
	}

	while (pdadc_i < AR5K_EEPROM_POWER_TABLE_SIZE * 2) {
		pdadc_out[pdadc_i] = pdadc_out[pdadc_i - 1];
		pdadc_i++;
	}

	/* Set gain boundaries */
	ath5k_hw_reg_write(ah,
		AR5K_REG_SM(pd_gain_overlap,
			AR5K_PHY_TPC_RG5_PD_GAIN_OVERLAP) |
		AR5K_REG_SM(gain_boundaries[0],
			AR5K_PHY_TPC_RG5_PD_GAIN_BOUNDARY_1) |
		AR5K_REG_SM(gain_boundaries[1],
			AR5K_PHY_TPC_RG5_PD_GAIN_BOUNDARY_2) |
		AR5K_REG_SM(gain_boundaries[2],
			AR5K_PHY_TPC_RG5_PD_GAIN_BOUNDARY_3) |
		AR5K_REG_SM(gain_boundaries[3],
			AR5K_PHY_TPC_RG5_PD_GAIN_BOUNDARY_4),
		AR5K_PHY_TPC_RG5);

	/* Used for setting rate power table */
	ah->ah_txpower.txp_min_idx = pwr_min[0];

}