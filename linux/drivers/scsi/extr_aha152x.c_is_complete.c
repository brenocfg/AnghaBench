#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct Scsi_Host {int dummy; } ;
struct TYPE_9__ {scalar_t__ service; scalar_t__ in_intr; int /*<<< orphan*/ * time; int /*<<< orphan*/ * count_trans; int /*<<< orphan*/ * count; } ;
struct TYPE_6__ {int /*<<< orphan*/  phase; } ;
struct TYPE_8__ {TYPE_1__ SCp; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* run ) (struct Scsi_Host*) ;int /*<<< orphan*/  (* init ) (struct Scsi_Host*) ;scalar_t__ spio; int /*<<< orphan*/  (* end ) (struct Scsi_Host*) ;} ;

/* Variables and functions */
 int CH1 ; 
 TYPE_3__* CURRENT_SC ; 
 int /*<<< orphan*/  DMACNTRL0 ; 
 int /*<<< orphan*/  DO_LOCK (unsigned long) ; 
 int /*<<< orphan*/  DO_UNLOCK (unsigned long) ; 
 int GETPORT (int /*<<< orphan*/ ) ; 
 TYPE_4__* HOSTDATA (struct Scsi_Host*) ; 
 int /*<<< orphan*/  INTEN ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int PHASECHG ; 
 size_t PREVSTATE ; 
 int P_MASK ; 
 int REQINIT ; 
 int /*<<< orphan*/  SCSISIG ; 
 int /*<<< orphan*/  SETBITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SETPORT (int /*<<< orphan*/ ,int) ; 
 int SPIOEN ; 
 int /*<<< orphan*/  SSTAT0 ; 
 int /*<<< orphan*/  SSTAT1 ; 
 size_t STATE ; 
 int /*<<< orphan*/  SXFRCTL0 ; 
 int /*<<< orphan*/  aha152x_error (struct Scsi_Host*,char*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  scmd_printk (int /*<<< orphan*/ ,TYPE_3__*,char*,size_t) ; 
 int setup_expected_interrupts (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spiordy ; 
 TYPE_2__* states ; 
 int /*<<< orphan*/  stub1 (struct Scsi_Host*) ; 
 int /*<<< orphan*/  stub2 (struct Scsi_Host*) ; 
 int /*<<< orphan*/  stub3 (struct Scsi_Host*) ; 
 int update_state (struct Scsi_Host*) ; 

__attribute__((used)) static void is_complete(struct Scsi_Host *shpnt)
{
	int dataphase;
	unsigned long flags;
	int pending;

	if(!shpnt)
		return;

	DO_LOCK(flags);

	if( HOSTDATA(shpnt)->service==0 )  {
		DO_UNLOCK(flags);
		return;
	}

	HOSTDATA(shpnt)->service = 0;

	if(HOSTDATA(shpnt)->in_intr) {
		DO_UNLOCK(flags);
		/* aha152x_error never returns.. */
		aha152x_error(shpnt, "bottom-half already running!?");
	}
	HOSTDATA(shpnt)->in_intr++;

	/*
	 * loop while there are interrupt conditions pending
	 *
	 */
	do {
		unsigned long start = jiffies;
		DO_UNLOCK(flags);

		dataphase=update_state(shpnt);

		/*
		 * end previous state
		 *
		 */
		if(PREVSTATE!=STATE && states[PREVSTATE].end)
			states[PREVSTATE].end(shpnt);

		/*
		 * disable SPIO mode if previous phase used it
		 * and this one doesn't
		 *
		 */
		if(states[PREVSTATE].spio && !states[STATE].spio) {
			SETPORT(SXFRCTL0, CH1);
			SETPORT(DMACNTRL0, 0);
			if(CURRENT_SC)
				CURRENT_SC->SCp.phase &= ~spiordy;
		}

		/*
		 * accept current dataphase phase
		 *
		 */
		if(dataphase) {
			SETPORT(SSTAT0, REQINIT);
			SETPORT(SCSISIG, GETPORT(SCSISIG) & P_MASK);
			SETPORT(SSTAT1, PHASECHG);
		}

		/*
		 * enable SPIO mode if previous didn't use it
		 * and this one does
		 *
		 */
		if(!states[PREVSTATE].spio && states[STATE].spio) {
			SETPORT(DMACNTRL0, 0);
			SETPORT(SXFRCTL0, CH1|SPIOEN);
			if(CURRENT_SC)
				CURRENT_SC->SCp.phase |= spiordy;
		}

		/*
		 * initialize for new state
		 *
		 */
		if(PREVSTATE!=STATE && states[STATE].init)
			states[STATE].init(shpnt);

		/*
		 * handle current state
		 *
		 */
		if(states[STATE].run)
			states[STATE].run(shpnt);
		else
			scmd_printk(KERN_ERR, CURRENT_SC,
				    "unexpected state (%x)\n", STATE);

		/*
		 * setup controller to interrupt on
		 * the next expected condition and
		 * loop if it's already there
		 *
		 */
		DO_LOCK(flags);
		pending=setup_expected_interrupts(shpnt);
#if defined(AHA152X_STAT)
		HOSTDATA(shpnt)->count[STATE]++;
		if(PREVSTATE!=STATE)
			HOSTDATA(shpnt)->count_trans[STATE]++;
		HOSTDATA(shpnt)->time[STATE] += jiffies-start;
#endif

	} while(pending);

	/*
	 * enable interrupts and leave bottom-half
	 *
	 */
	HOSTDATA(shpnt)->in_intr--;
	SETBITS(DMACNTRL0, INTEN);
	DO_UNLOCK(flags);
}