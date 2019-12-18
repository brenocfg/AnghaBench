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
typedef  scalar_t__ u_int ;
struct ahc_softc {int flags; } ;

/* Variables and functions */
 int AHC_SCB_BTT ; 
 scalar_t__ BUSY_TARGETS ; 
 scalar_t__ SCBPTR ; 
 scalar_t__ SCB_64_BTT ; 
 scalar_t__ TCL_LUN (scalar_t__) ; 
 scalar_t__ TCL_TARGET_OFFSET (scalar_t__) ; 
 scalar_t__ ahc_inb (struct ahc_softc*,scalar_t__) ; 
 int /*<<< orphan*/  ahc_outb (struct ahc_softc*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
ahc_busy_tcl(struct ahc_softc *ahc, u_int tcl, u_int scbid)
{
	u_int target_offset;

	if ((ahc->flags & AHC_SCB_BTT) != 0) {
		u_int saved_scbptr;
		
		saved_scbptr = ahc_inb(ahc, SCBPTR);
		ahc_outb(ahc, SCBPTR, TCL_LUN(tcl));
		ahc_outb(ahc, SCB_64_BTT + TCL_TARGET_OFFSET(tcl), scbid);
		ahc_outb(ahc, SCBPTR, saved_scbptr);
	} else {
		target_offset = TCL_TARGET_OFFSET(tcl);
		ahc_outb(ahc, BUSY_TARGETS + target_offset, scbid);
	}
}