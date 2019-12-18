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
typedef  int u32 ;
struct TYPE_4__ {size_t* txp_pd_table; } ;
struct ath5k_eeprom_info {size_t** ee_pdc_to_idx; size_t* ee_pd_gains; } ;
struct TYPE_3__ {struct ath5k_eeprom_info cap_eeprom; } ;
struct ath5k_hw {TYPE_2__ ah_txpower; TYPE_1__ ah_capabilities; } ;

/* Variables and functions */
 int AR5K_EEPROM_POWER_TABLE_SIZE ; 
 int /*<<< orphan*/  AR5K_PHY_PDADC_TXPOWER (size_t) ; 
 int /*<<< orphan*/  AR5K_PHY_TPC_RG1 ; 
 int AR5K_PHY_TPC_RG1_NUM_PD_GAIN ; 
 int AR5K_PHY_TPC_RG1_PDGAIN_1 ; 
 int AR5K_PHY_TPC_RG1_PDGAIN_2 ; 
 int AR5K_PHY_TPC_RG1_PDGAIN_3 ; 
 int AR5K_REG_SM (size_t,int) ; 
 int ath5k_hw_reg_read (struct ath5k_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath5k_hw_reg_write (struct ath5k_hw*,int,int /*<<< orphan*/ ) ; 
 int get_unaligned_le32 (size_t*) ; 

__attribute__((used)) static void
ath5k_write_pwr_to_pdadc_table(struct ath5k_hw *ah, u8 ee_mode)
{
	struct ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	u8 *pdadc_out = ah->ah_txpower.txp_pd_table;
	u8 *pdg_to_idx = ee->ee_pdc_to_idx[ee_mode];
	u8 pdcurves = ee->ee_pd_gains[ee_mode];
	u32 reg;
	u8 i;

	/* Select the right pdgain curves */

	/* Clear current settings */
	reg = ath5k_hw_reg_read(ah, AR5K_PHY_TPC_RG1);
	reg &= ~(AR5K_PHY_TPC_RG1_PDGAIN_1 |
		AR5K_PHY_TPC_RG1_PDGAIN_2 |
		AR5K_PHY_TPC_RG1_PDGAIN_3 |
		AR5K_PHY_TPC_RG1_NUM_PD_GAIN);

	/*
	 * Use pd_gains curve from eeprom
	 *
	 * This overrides the default setting from initvals
	 * in case some vendors (e.g. Zcomax) don't use the default
	 * curves. If we don't honor their settings we 'll get a
	 * 5dB (1 * gain overlap ?) drop.
	 */
	reg |= AR5K_REG_SM(pdcurves, AR5K_PHY_TPC_RG1_NUM_PD_GAIN);

	switch (pdcurves) {
	case 3:
		reg |= AR5K_REG_SM(pdg_to_idx[2], AR5K_PHY_TPC_RG1_PDGAIN_3);
		/* Fall through */
	case 2:
		reg |= AR5K_REG_SM(pdg_to_idx[1], AR5K_PHY_TPC_RG1_PDGAIN_2);
		/* Fall through */
	case 1:
		reg |= AR5K_REG_SM(pdg_to_idx[0], AR5K_PHY_TPC_RG1_PDGAIN_1);
		break;
	}
	ath5k_hw_reg_write(ah, reg, AR5K_PHY_TPC_RG1);

	/*
	 * Write TX power values
	 */
	for (i = 0; i < (AR5K_EEPROM_POWER_TABLE_SIZE / 2); i++) {
		u32 val = get_unaligned_le32(&pdadc_out[4 * i]);
		ath5k_hw_reg_write(ah, val, AR5K_PHY_PDADC_TXPOWER(i));
	}
}