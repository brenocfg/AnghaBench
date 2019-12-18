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
struct bfad_s {TYPE_1__* im; int /*<<< orphan*/  bfad_lock; int /*<<< orphan*/  bfad_flags; int /*<<< orphan*/  bfa_fcs; int /*<<< orphan*/  bfa; } ;
struct TYPE_2__ {int /*<<< orphan*/  drv_workq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFAD_HAL_START_DONE ; 
 int /*<<< orphan*/  bfa_fcs_fabric_modstart (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_fcs_pbc_vport_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_iocfc_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
bfad_drv_start(struct bfad_s *bfad)
{
	unsigned long	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	bfa_iocfc_start(&bfad->bfa);
	bfa_fcs_pbc_vport_init(&bfad->bfa_fcs);
	bfa_fcs_fabric_modstart(&bfad->bfa_fcs);
	bfad->bfad_flags |= BFAD_HAL_START_DONE;
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	if (bfad->im)
		flush_workqueue(bfad->im->drv_workq);
}