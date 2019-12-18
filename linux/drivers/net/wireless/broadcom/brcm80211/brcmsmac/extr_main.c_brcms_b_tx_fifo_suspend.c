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
typedef  int uint ;
typedef  int u8 ;
struct brcms_hardware {int suspended_fifos; int /*<<< orphan*/  wlc; int /*<<< orphan*/  band; scalar_t__* di; } ;

/* Variables and functions */
 scalar_t__ BRCMS_PHY_11N_CAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BRCMS_WAKE_OVERRIDE_TXFIFO ; 
 int /*<<< orphan*/  brcms_c_enable_mac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_c_suspend_mac_and_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_c_ucode_wake_override_set (struct brcms_hardware*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_txsuspend (scalar_t__) ; 

__attribute__((used)) static void brcms_b_tx_fifo_suspend(struct brcms_hardware *wlc_hw,
				    uint tx_fifo)
{
	u8 fifo = 1 << tx_fifo;

	/* Two clients of this code, 11h Quiet period and scanning. */

	/* only suspend if not already suspended */
	if ((wlc_hw->suspended_fifos & fifo) == fifo)
		return;

	/* force the core awake only if not already */
	if (wlc_hw->suspended_fifos == 0)
		brcms_c_ucode_wake_override_set(wlc_hw,
						BRCMS_WAKE_OVERRIDE_TXFIFO);

	wlc_hw->suspended_fifos |= fifo;

	if (wlc_hw->di[tx_fifo]) {
		/*
		 * Suspending AMPDU transmissions in the middle can cause
		 * underflow which may result in mismatch between ucode and
		 * driver so suspend the mac before suspending the FIFO
		 */
		if (BRCMS_PHY_11N_CAP(wlc_hw->band))
			brcms_c_suspend_mac_and_wait(wlc_hw->wlc);

		dma_txsuspend(wlc_hw->di[tx_fifo]);

		if (BRCMS_PHY_11N_CAP(wlc_hw->band))
			brcms_c_enable_mac(wlc_hw->wlc);
	}
}