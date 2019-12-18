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
typedef  int u16 ;
struct ath5k_eeprom_info {scalar_t__* ee_n_piers; } ;
struct TYPE_2__ {struct ath5k_eeprom_info cap_eeprom; } ;
struct ath5k_hw {TYPE_1__ ah_capabilities; } ;
struct ath5k_chan_pcal_info {void* freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR5K_EEPROM_READ (int /*<<< orphan*/ ,int) ; 
 void* ath5k_eeprom_bin2freq (struct ath5k_eeprom_info*,int,unsigned int) ; 

__attribute__((used)) static inline int
ath5k_eeprom_read_freq_list(struct ath5k_hw *ah, int *offset, int max,
			struct ath5k_chan_pcal_info *pc, unsigned int mode)
{
	struct ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	int o = *offset;
	int i = 0;
	u8 freq1, freq2;
	u16 val;

	ee->ee_n_piers[mode] = 0;
	while (i < max) {
		AR5K_EEPROM_READ(o++, val);

		freq1 = val & 0xff;
		if (!freq1)
			break;

		pc[i++].freq = ath5k_eeprom_bin2freq(ee,
				freq1, mode);
		ee->ee_n_piers[mode]++;

		freq2 = (val >> 8) & 0xff;
		if (!freq2)
			break;

		pc[i++].freq = ath5k_eeprom_bin2freq(ee,
				freq2, mode);
		ee->ee_n_piers[mode]++;
	}

	/* return new offset */
	*offset = o;

	return 0;
}