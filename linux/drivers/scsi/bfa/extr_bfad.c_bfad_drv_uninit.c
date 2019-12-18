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
struct bfad_s {int /*<<< orphan*/  bfad_flags; int /*<<< orphan*/  bfa; int /*<<< orphan*/  hal_tmo; int /*<<< orphan*/  comp; int /*<<< orphan*/  bfad_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFAD_DRV_INIT_DONE ; 
 int /*<<< orphan*/  bfa_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_iocfc_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_isr_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfad_hal_mem_release (struct bfad_s*) ; 
 int /*<<< orphan*/  bfad_remove_intr (struct bfad_s*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void
bfad_drv_uninit(struct bfad_s *bfad)
{
	unsigned long   flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	init_completion(&bfad->comp);
	bfa_iocfc_stop(&bfad->bfa);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	wait_for_completion(&bfad->comp);

	del_timer_sync(&bfad->hal_tmo);
	bfa_isr_disable(&bfad->bfa);
	bfa_detach(&bfad->bfa);
	bfad_remove_intr(bfad);
	bfad_hal_mem_release(bfad);

	bfad->bfad_flags &= ~BFAD_DRV_INIT_DONE;
}