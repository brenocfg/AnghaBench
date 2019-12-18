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
struct bfa_fcport_s {int /*<<< orphan*/  diag_busy; } ;
struct TYPE_2__ {scalar_t__ lock; } ;
struct bfa_fcdiag_s {TYPE_1__ lb; int /*<<< orphan*/  bfa; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 struct bfa_fcport_s* BFA_FCPORT_MOD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BFA_TRUE ; 

__attribute__((used)) static void
bfa_fcdiag_set_busy_status(struct bfa_fcdiag_s *fcdiag)
{
	struct bfa_fcport_s *fcport = BFA_FCPORT_MOD(fcdiag->bfa);

	if (fcdiag->lb.lock)
		fcport->diag_busy = BFA_TRUE;
	else
		fcport->diag_busy = BFA_FALSE;
}