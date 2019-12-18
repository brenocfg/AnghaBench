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
struct sym_hcb {int istat_sem; } ;
struct sym_ccb {scalar_t__ host_status; int to_abort; } ;

/* Variables and functions */
 scalar_t__ HS_WAIT ; 
 int /*<<< orphan*/  OUTB (struct sym_hcb*,int /*<<< orphan*/ ,int) ; 
 int SEM ; 
 int SIGP ; 
 int /*<<< orphan*/  nc_istat ; 
 int /*<<< orphan*/  sym_reset_scsi_bus (struct sym_hcb*,int) ; 

__attribute__((used)) static int sym_abort_ccb(struct sym_hcb *np, struct sym_ccb *cp, int timed_out)
{
	/*
	 *  Check that the IO is active.
	 */
	if (!cp || !cp->host_status || cp->host_status == HS_WAIT)
		return -1;

	/*
	 *  If a previous abort didn't succeed in time,
	 *  perform a BUS reset.
	 */
	if (cp->to_abort) {
		sym_reset_scsi_bus(np, 1);
		return 0;
	}

	/*
	 *  Mark the CCB for abort and allow time for.
	 */
	cp->to_abort = timed_out ? 2 : 1;

	/*
	 *  Tell the SCRIPTS processor to stop and synchronize with us.
	 */
	np->istat_sem = SEM;
	OUTB(np, nc_istat, SIGP|SEM);
	return 0;
}