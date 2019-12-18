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
struct ath5k_eeprom_info {struct ath5k_chan_pcal_info* ee_pwr_cal_g; struct ath5k_chan_pcal_info* ee_pwr_cal_b; } ;
struct TYPE_2__ {struct ath5k_eeprom_info cap_eeprom; } ;
struct ath5k_hw {TYPE_1__ ah_capabilities; } ;
struct ath5k_chan_pcal_info {int dummy; } ;

/* Variables and functions */
#define  AR5K_EEPROM_MODE_11B 129 
#define  AR5K_EEPROM_MODE_11G 128 
 int /*<<< orphan*/  AR5K_EEPROM_N_2GHZ_CHAN_2413 ; 
 int EINVAL ; 
 int /*<<< orphan*/  ath5k_eeprom_read_freq_list (struct ath5k_hw*,int*,int /*<<< orphan*/ ,struct ath5k_chan_pcal_info*,unsigned int) ; 

__attribute__((used)) static inline int
ath5k_eeprom_init_11bg_2413(struct ath5k_hw *ah, unsigned int mode, int offset)
{
	struct ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	struct ath5k_chan_pcal_info *pcal;

	switch (mode) {
	case AR5K_EEPROM_MODE_11B:
		pcal = ee->ee_pwr_cal_b;
		break;
	case AR5K_EEPROM_MODE_11G:
		pcal = ee->ee_pwr_cal_g;
		break;
	default:
		return -EINVAL;
	}

	ath5k_eeprom_read_freq_list(ah, &offset,
		AR5K_EEPROM_N_2GHZ_CHAN_2413, pcal,
		mode);

	return 0;
}