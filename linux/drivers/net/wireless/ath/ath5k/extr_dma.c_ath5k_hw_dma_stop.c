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
struct ath5k_hw {scalar_t__ ah_version; } ;

/* Variables and functions */
 scalar_t__ AR5K_AR5210 ; 
 int /*<<< orphan*/  AR5K_ISR ; 
 int AR5K_NUM_TX_QUEUES ; 
 int AR5K_NUM_TX_QUEUES_NOQCU ; 
 int /*<<< orphan*/  AR5K_PISR ; 
 int EINVAL ; 
 int /*<<< orphan*/  ath5k_hw_reg_read (struct ath5k_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath5k_hw_reg_write (struct ath5k_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath5k_hw_set_imr (struct ath5k_hw*,int /*<<< orphan*/ ) ; 
 int ath5k_hw_stop_rx_dma (struct ath5k_hw*) ; 
 int ath5k_hw_stop_tx_dma (struct ath5k_hw*,int) ; 

int
ath5k_hw_dma_stop(struct ath5k_hw *ah)
{
	int i, qmax, err;
	err = 0;

	/* Disable interrupts */
	ath5k_hw_set_imr(ah, 0);

	/* Stop rx dma */
	err = ath5k_hw_stop_rx_dma(ah);
	if (err)
		return err;

	/* Clear any pending interrupts
	 * and disable tx dma */
	if (ah->ah_version != AR5K_AR5210) {
		ath5k_hw_reg_write(ah, 0xffffffff, AR5K_PISR);
		qmax = AR5K_NUM_TX_QUEUES;
	} else {
		/* PISR/SISR Not available on 5210 */
		ath5k_hw_reg_read(ah, AR5K_ISR);
		qmax = AR5K_NUM_TX_QUEUES_NOQCU;
	}

	for (i = 0; i < qmax; i++) {
		err = ath5k_hw_stop_tx_dma(ah, i);
		/* -EINVAL -> queue inactive */
		if (err && err != -EINVAL)
			return err;
	}

	return 0;
}