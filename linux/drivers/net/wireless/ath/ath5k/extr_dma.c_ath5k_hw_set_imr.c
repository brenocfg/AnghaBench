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
typedef  int u32 ;
struct ath5k_hw {int ah_imr; scalar_t__ ah_version; } ;
typedef  enum ath5k_int { ____Placeholder_ath5k_int } ath5k_int ;

/* Variables and functions */
 scalar_t__ AR5K_AR5210 ; 
 int /*<<< orphan*/  AR5K_IER ; 
 int AR5K_IER_DISABLE ; 
 int AR5K_IER_ENABLE ; 
 int /*<<< orphan*/  AR5K_IMR ; 
 int AR5K_IMR_DPERR ; 
 int AR5K_IMR_HIUERR ; 
 int AR5K_IMR_MCABT ; 
 int AR5K_IMR_SSERR ; 
 int AR5K_IMR_TIM ; 
 int AR5K_INT_BCN_TIMEOUT ; 
 int AR5K_INT_BNR ; 
 int AR5K_INT_CAB_TIMEOUT ; 
 int AR5K_INT_COMMON ; 
 int AR5K_INT_DTIM ; 
 int AR5K_INT_DTIM_SYNC ; 
 int AR5K_INT_FATAL ; 
 int AR5K_INT_GLOBAL ; 
 int AR5K_INT_RXNOFRM ; 
 int AR5K_INT_TIM ; 
 int /*<<< orphan*/  AR5K_PIMR ; 
 int /*<<< orphan*/  AR5K_RXNOFRM ; 
 int /*<<< orphan*/  AR5K_SIMR2 ; 
 int AR5K_SIMR2_DPERR ; 
 int AR5K_SIMR2_MCABT ; 
 int AR5K_SIMR2_QCU_TXURN ; 
 int AR5K_SIMR2_SSERR ; 
 int AR5K_SISR2_BCN_TIMEOUT ; 
 int AR5K_SISR2_CAB_TIMEOUT ; 
 int AR5K_SISR2_DTIM ; 
 int AR5K_SISR2_DTIM_SYNC ; 
 int AR5K_SISR2_TIM ; 
 int ath5k_hw_reg_read (struct ath5k_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath5k_hw_reg_write (struct ath5k_hw*,int,int /*<<< orphan*/ ) ; 

enum ath5k_int
ath5k_hw_set_imr(struct ath5k_hw *ah, enum ath5k_int new_mask)
{
	enum ath5k_int old_mask, int_mask;

	old_mask = ah->ah_imr;

	/*
	 * Disable card interrupts to prevent any race conditions
	 * (they will be re-enabled afterwards if AR5K_INT GLOBAL
	 * is set again on the new mask).
	 */
	if (old_mask & AR5K_INT_GLOBAL) {
		ath5k_hw_reg_write(ah, AR5K_IER_DISABLE, AR5K_IER);
		ath5k_hw_reg_read(ah, AR5K_IER);
	}

	/*
	 * Add additional, chipset-dependent interrupt mask flags
	 * and write them to the IMR (interrupt mask register).
	 */
	int_mask = new_mask & AR5K_INT_COMMON;

	if (ah->ah_version != AR5K_AR5210) {
		/* Preserve per queue TXURN interrupt mask */
		u32 simr2 = ath5k_hw_reg_read(ah, AR5K_SIMR2)
				& AR5K_SIMR2_QCU_TXURN;

		/* Fatal interrupt abstraction for 5211+ */
		if (new_mask & AR5K_INT_FATAL) {
			int_mask |= AR5K_IMR_HIUERR;
			simr2 |= (AR5K_SIMR2_MCABT | AR5K_SIMR2_SSERR
				| AR5K_SIMR2_DPERR);
		}

		/* Misc beacon related interrupts */
		if (new_mask & AR5K_INT_TIM)
			int_mask |= AR5K_IMR_TIM;

		if (new_mask & AR5K_INT_TIM)
			simr2 |= AR5K_SISR2_TIM;
		if (new_mask & AR5K_INT_DTIM)
			simr2 |= AR5K_SISR2_DTIM;
		if (new_mask & AR5K_INT_DTIM_SYNC)
			simr2 |= AR5K_SISR2_DTIM_SYNC;
		if (new_mask & AR5K_INT_BCN_TIMEOUT)
			simr2 |= AR5K_SISR2_BCN_TIMEOUT;
		if (new_mask & AR5K_INT_CAB_TIMEOUT)
			simr2 |= AR5K_SISR2_CAB_TIMEOUT;

		/*Beacon Not Ready*/
		if (new_mask & AR5K_INT_BNR)
			int_mask |= AR5K_INT_BNR;

		/* Note: Per queue interrupt masks
		 * are set via ath5k_hw_reset_tx_queue() (qcu.c) */
		ath5k_hw_reg_write(ah, int_mask, AR5K_PIMR);
		ath5k_hw_reg_write(ah, simr2, AR5K_SIMR2);

	} else {
		/* Fatal interrupt abstraction for 5210 */
		if (new_mask & AR5K_INT_FATAL)
			int_mask |= (AR5K_IMR_SSERR | AR5K_IMR_MCABT
				| AR5K_IMR_HIUERR | AR5K_IMR_DPERR);

		/* Only common interrupts left for 5210 (no SIMRs) */
		ath5k_hw_reg_write(ah, int_mask, AR5K_IMR);
	}

	/* If RXNOFRM interrupt is masked disable it
	 * by setting AR5K_RXNOFRM to zero */
	if (!(new_mask & AR5K_INT_RXNOFRM))
		ath5k_hw_reg_write(ah, 0, AR5K_RXNOFRM);

	/* Store new interrupt mask */
	ah->ah_imr = new_mask;

	/* ..re-enable interrupts if AR5K_INT_GLOBAL is set */
	if (new_mask & AR5K_INT_GLOBAL) {
		ath5k_hw_reg_write(ah, AR5K_IER_ENABLE, AR5K_IER);
		ath5k_hw_reg_read(ah, AR5K_IER);
	}

	return old_mask;
}