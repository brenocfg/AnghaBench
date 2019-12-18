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
typedef  size_t u32 ;
struct TYPE_4__ {TYPE_1__* clip_groups; } ;
struct il_priv {TYPE_2__ _3945; scalar_t__ eeprom; } ;
struct il3945_eeprom_txpower_group {int saturation_power; } ;
struct il3945_eeprom {struct il3945_eeprom_txpower_group* groups; } ;
typedef  scalar_t__ s8 ;
typedef  int s32 ;
struct TYPE_3__ {scalar_t__ clip_powers; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_POWER (char*) ; 
 size_t IL_NUM_TX_CALIB_GROUPS ; 
 int /*<<< orphan*/  IL_WARN (char*,int) ; 
#define  RATE_36M_IDX_TBL 130 
#define  RATE_48M_IDX_TBL 129 
#define  RATE_54M_IDX_TBL 128 
 int RATE_COUNT_3945 ; 

__attribute__((used)) static void
il3945_hw_reg_init_channel_groups(struct il_priv *il)
{
	u32 i;
	s32 rate_idx;
	struct il3945_eeprom *eeprom = (struct il3945_eeprom *)il->eeprom;
	const struct il3945_eeprom_txpower_group *group;

	D_POWER("Initializing factory calib info from EEPROM\n");

	for (i = 0; i < IL_NUM_TX_CALIB_GROUPS; i++) {
		s8 *clip_pwrs;	/* table of power levels for each rate */
		s8 satur_pwr;	/* saturation power for each chnl group */
		group = &eeprom->groups[i];

		/* sanity check on factory saturation power value */
		if (group->saturation_power < 40) {
			IL_WARN("Error: saturation power is %d, "
				"less than minimum expected 40\n",
				group->saturation_power);
			return;
		}

		/*
		 * Derive requested power levels for each rate, based on
		 *   hardware capabilities (saturation power for band).
		 * Basic value is 3dB down from saturation, with further
		 *   power reductions for highest 3 data rates.  These
		 *   backoffs provide headroom for high rate modulation
		 *   power peaks, without too much distortion (clipping).
		 */
		/* we'll fill in this array with h/w max power levels */
		clip_pwrs = (s8 *) il->_3945.clip_groups[i].clip_powers;

		/* divide factory saturation power by 2 to find -3dB level */
		satur_pwr = (s8) (group->saturation_power >> 1);

		/* fill in channel group's nominal powers for each rate */
		for (rate_idx = 0; rate_idx < RATE_COUNT_3945;
		     rate_idx++, clip_pwrs++) {
			switch (rate_idx) {
			case RATE_36M_IDX_TBL:
				if (i == 0)	/* B/G */
					*clip_pwrs = satur_pwr;
				else	/* A */
					*clip_pwrs = satur_pwr - 5;
				break;
			case RATE_48M_IDX_TBL:
				if (i == 0)
					*clip_pwrs = satur_pwr - 7;
				else
					*clip_pwrs = satur_pwr - 10;
				break;
			case RATE_54M_IDX_TBL:
				if (i == 0)
					*clip_pwrs = satur_pwr - 9;
				else
					*clip_pwrs = satur_pwr - 12;
				break;
			default:
				*clip_pwrs = satur_pwr;
				break;
			}
		}
	}
}