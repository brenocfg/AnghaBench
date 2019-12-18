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
struct il_priv {scalar_t__ eeprom; } ;
struct il3945_eeprom_txpower_sample {size_t power; size_t gain_idx; } ;
struct il3945_eeprom_txpower_group {struct il3945_eeprom_txpower_sample* samples; } ;
struct il3945_eeprom {struct il3945_eeprom_txpower_group* groups; } ;
typedef  int s8 ;
typedef  size_t s32 ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int
il3945_hw_reg_get_matched_power_idx(struct il_priv *il, s8 requested_power,
				    s32 setting_idx, s32 *new_idx)
{
	const struct il3945_eeprom_txpower_group *chnl_grp = NULL;
	struct il3945_eeprom *eeprom = (struct il3945_eeprom *)il->eeprom;
	s32 idx0, idx1;
	s32 power = 2 * requested_power;
	s32 i;
	const struct il3945_eeprom_txpower_sample *samples;
	s32 gains0, gains1;
	s32 res;
	s32 denominator;

	chnl_grp = &eeprom->groups[setting_idx];
	samples = chnl_grp->samples;
	for (i = 0; i < 5; i++) {
		if (power == samples[i].power) {
			*new_idx = samples[i].gain_idx;
			return 0;
		}
	}

	if (power > samples[1].power) {
		idx0 = 0;
		idx1 = 1;
	} else if (power > samples[2].power) {
		idx0 = 1;
		idx1 = 2;
	} else if (power > samples[3].power) {
		idx0 = 2;
		idx1 = 3;
	} else {
		idx0 = 3;
		idx1 = 4;
	}

	denominator = (s32) samples[idx1].power - (s32) samples[idx0].power;
	if (denominator == 0)
		return -EINVAL;
	gains0 = (s32) samples[idx0].gain_idx * (1 << 19);
	gains1 = (s32) samples[idx1].gain_idx * (1 << 19);
	res =
	    gains0 + (gains1 - gains0) * ((s32) power -
					  (s32) samples[idx0].power) /
	    denominator + (1 << 18);
	*new_idx = res >> 19;
	return 0;
}