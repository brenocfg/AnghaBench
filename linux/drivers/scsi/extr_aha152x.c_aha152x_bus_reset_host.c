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
struct Scsi_Host {int dummy; } ;
struct TYPE_2__ {scalar_t__ commands; } ;

/* Variables and functions */
 int DELAY ; 
 int /*<<< orphan*/  DISCONNECTED_SC ; 
 int /*<<< orphan*/  DO_LOCK (unsigned long) ; 
 int /*<<< orphan*/  DO_UNLOCK (unsigned long) ; 
 TYPE_1__* HOSTDATA (struct Scsi_Host*) ; 
 int /*<<< orphan*/  ISSUE_SC ; 
 int /*<<< orphan*/  PORTA ; 
 int /*<<< orphan*/  SCSIRSTO ; 
 int /*<<< orphan*/  SCSISEQ ; 
 int /*<<< orphan*/  SETPORT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SUCCESS ; 
 int /*<<< orphan*/  free_hard_reset_SCs (struct Scsi_Host*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  setup_expected_interrupts (struct Scsi_Host*) ; 

__attribute__((used)) static int aha152x_bus_reset_host(struct Scsi_Host *shpnt)
{
	unsigned long flags;

	DO_LOCK(flags);

	free_hard_reset_SCs(shpnt, &ISSUE_SC);
	free_hard_reset_SCs(shpnt, &DISCONNECTED_SC);

	SETPORT(SCSISEQ, SCSIRSTO);
	mdelay(256);
	SETPORT(SCSISEQ, 0);
	mdelay(DELAY);

	setup_expected_interrupts(shpnt);
	if(HOSTDATA(shpnt)->commands==0)
		SETPORT(PORTA, 0);

	DO_UNLOCK(flags);

	return SUCCESS;
}