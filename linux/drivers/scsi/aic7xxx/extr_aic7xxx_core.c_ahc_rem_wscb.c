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
typedef  int u_int ;
struct ahc_softc {int dummy; } ;

/* Variables and functions */
 int ENSELO ; 
 int /*<<< orphan*/  SCBPTR ; 
 int /*<<< orphan*/  SCB_CONTROL ; 
 int SCB_LIST_NULL ; 
 int /*<<< orphan*/  SCB_NEXT ; 
 int /*<<< orphan*/  SCSISEQ ; 
 int /*<<< orphan*/  WAITING_SCBH ; 
 int /*<<< orphan*/  ahc_add_curscb_to_free_list (struct ahc_softc*) ; 
 int ahc_inb (struct ahc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_outb (struct ahc_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u_int
ahc_rem_wscb(struct ahc_softc *ahc, u_int scbpos, u_int prev)
{
	u_int curscb, next;

	/*
	 * Select the SCB we want to abort and
	 * pull the next pointer out of it.
	 */
	curscb = ahc_inb(ahc, SCBPTR);
	ahc_outb(ahc, SCBPTR, scbpos);
	next = ahc_inb(ahc, SCB_NEXT);

	/* Clear the necessary fields */
	ahc_outb(ahc, SCB_CONTROL, 0);

	ahc_add_curscb_to_free_list(ahc);

	/* update the waiting list */
	if (prev == SCB_LIST_NULL) {
		/* First in the list */
		ahc_outb(ahc, WAITING_SCBH, next); 

		/*
		 * Ensure we aren't attempting to perform
		 * selection for this entry.
		 */
		ahc_outb(ahc, SCSISEQ, (ahc_inb(ahc, SCSISEQ) & ~ENSELO));
	} else {
		/*
		 * Select the scb that pointed to us 
		 * and update its next pointer.
		 */
		ahc_outb(ahc, SCBPTR, prev);
		ahc_outb(ahc, SCB_NEXT, next);
	}

	/*
	 * Point us back at the original scb position.
	 */
	ahc_outb(ahc, SCBPTR, curscb);
	return next;
}