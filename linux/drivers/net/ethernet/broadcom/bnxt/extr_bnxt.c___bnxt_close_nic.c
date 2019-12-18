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
struct bnxt {int /*<<< orphan*/  net_stats_prev; scalar_t__ bnapi; int /*<<< orphan*/  pdev; int /*<<< orphan*/  state; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 scalar_t__ BNXT_PF (struct bnxt*) ; 
 int /*<<< orphan*/  BNXT_STATE_IN_FW_RESET ; 
 int /*<<< orphan*/  BNXT_STATE_OPEN ; 
 int /*<<< orphan*/  bnxt_debug_dev_exit (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_del_napi (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_disable_napi (struct bnxt*) ; 
 scalar_t__ bnxt_drv_busy (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_free_irq (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_free_mem (struct bnxt*,int) ; 
 int /*<<< orphan*/  bnxt_free_skbs (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_get_ring_stats (struct bnxt*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnxt_shutdown_nic (struct bnxt*,int) ; 
 int /*<<< orphan*/  bnxt_tx_disable (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_vf_reps_close (struct bnxt*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_is_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __bnxt_close_nic(struct bnxt *bp, bool irq_re_init,
			     bool link_re_init)
{
	/* Close the VF-reps before closing PF */
	if (BNXT_PF(bp))
		bnxt_vf_reps_close(bp);

	/* Change device state to avoid TX queue wake up's */
	bnxt_tx_disable(bp);

	clear_bit(BNXT_STATE_OPEN, &bp->state);
	smp_mb__after_atomic();
	while (bnxt_drv_busy(bp))
		msleep(20);

	/* Flush rings and and disable interrupts */
	bnxt_shutdown_nic(bp, irq_re_init);

	/* TODO CHIMP_FW: Link/PHY related cleanup if (link_re_init) */

	bnxt_debug_dev_exit(bp);
	bnxt_disable_napi(bp);
	del_timer_sync(&bp->timer);
	if (test_bit(BNXT_STATE_IN_FW_RESET, &bp->state) &&
	    pci_is_enabled(bp->pdev))
		pci_disable_device(bp->pdev);

	bnxt_free_skbs(bp);

	/* Save ring stats before shutdown */
	if (bp->bnapi)
		bnxt_get_ring_stats(bp, &bp->net_stats_prev);
	if (irq_re_init) {
		bnxt_free_irq(bp);
		bnxt_del_napi(bp);
	}
	bnxt_free_mem(bp, irq_re_init);
}