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
struct ath_hw {unsigned int paprd_training_power; unsigned int* paprd_gain_table_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_PAPRD_TRAINER_STAT1 ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_TRAINER_STAT1_PAPRD_TRAIN_DONE ; 
 unsigned int PAPRD_GAIN_TABLE_ENTRIES ; 
 int /*<<< orphan*/  REG_CLR_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int ar9003_get_desired_gain (struct ath_hw*,int,unsigned int) ; 
 int /*<<< orphan*/  ar9003_tx_force_gain (struct ath_hw*,unsigned int) ; 

void ar9003_paprd_setup_gain_table(struct ath_hw *ah, int chain)
{
	unsigned int i, desired_gain, gain_index;
	unsigned int train_power = ah->paprd_training_power;

	desired_gain = ar9003_get_desired_gain(ah, chain, train_power);

	gain_index = 0;
	for (i = 0; i < PAPRD_GAIN_TABLE_ENTRIES; i++) {
		if (ah->paprd_gain_table_index[i] >= desired_gain)
			break;
		gain_index++;
	}

	ar9003_tx_force_gain(ah, gain_index);

	REG_CLR_BIT(ah, AR_PHY_PAPRD_TRAINER_STAT1,
			AR_PHY_PAPRD_TRAINER_STAT1_PAPRD_TRAIN_DONE);
}