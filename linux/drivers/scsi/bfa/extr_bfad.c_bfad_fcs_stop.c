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
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct bfad_s {int /*<<< orphan*/  comp; int /*<<< orphan*/  bfad_lock; int /*<<< orphan*/  bfa_fcs; TYPE_1__ pport; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFAD_E_FCS_EXIT_COMP ; 
 int /*<<< orphan*/  BFAD_PORT_DELETE ; 
 int /*<<< orphan*/  bfa_fcs_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfad_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void
bfad_fcs_stop(struct bfad_s *bfad)
{
	unsigned long	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	init_completion(&bfad->comp);
	bfad->pport.flags |= BFAD_PORT_DELETE;
	bfa_fcs_exit(&bfad->bfa_fcs);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	wait_for_completion(&bfad->comp);

	bfa_sm_send_event(bfad, BFAD_E_FCS_EXIT_COMP);
}