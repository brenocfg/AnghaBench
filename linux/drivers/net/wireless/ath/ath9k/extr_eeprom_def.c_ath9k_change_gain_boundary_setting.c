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
typedef  size_t u16 ;
struct ath_hw {int dummy; } ;
typedef  scalar_t__ int8_t ;
typedef  int int16_t ;

/* Variables and functions */
 scalar_t__ AR5416_PWR_TABLE_OFFSET_DB ; 
 scalar_t__ AR_SREV_9280_20_OR_LATER (struct ath_hw*) ; 
 size_t MAX_RATE_POWER ; 
 scalar_t__ min (size_t,size_t) ; 

__attribute__((used)) static int16_t ath9k_change_gain_boundary_setting(struct ath_hw *ah,
				u16 *gb,
				u16 numXpdGain,
				u16 pdGainOverlap_t2,
				int8_t pwr_table_offset,
				int16_t *diff)

{
	u16 k;

	/* Prior to writing the boundaries or the pdadc vs. power table
	 * into the chip registers the default starting point on the pdadc
	 * vs. power table needs to be checked and the curve boundaries
	 * adjusted accordingly
	 */
	if (AR_SREV_9280_20_OR_LATER(ah)) {
		u16 gb_limit;

		if (AR5416_PWR_TABLE_OFFSET_DB != pwr_table_offset) {
			/* get the difference in dB */
			*diff = (u16)(pwr_table_offset - AR5416_PWR_TABLE_OFFSET_DB);
			/* get the number of half dB steps */
			*diff *= 2;
			/* change the original gain boundary settings
			 * by the number of half dB steps
			 */
			for (k = 0; k < numXpdGain; k++)
				gb[k] = (u16)(gb[k] - *diff);
		}
		/* Because of a hardware limitation, ensure the gain boundary
		 * is not larger than (63 - overlap)
		 */
		gb_limit = (u16)(MAX_RATE_POWER - pdGainOverlap_t2);

		for (k = 0; k < numXpdGain; k++)
			gb[k] = (u16)min(gb_limit, gb[k]);
	}

	return *diff;
}