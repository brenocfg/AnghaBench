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
struct ahc_softc {int dummy; } ;

/* Variables and functions */
 int CLRATNO ; 
 int CLRBUSFREE ; 
 int /*<<< orphan*/  CLRINT ; 
 int CLRPHASECHG ; 
 int CLRREQINIT ; 
 int CLRSCSIINT ; 
 int CLRSCSIPERR ; 
 int CLRSCSIRSTI ; 
 int CLRSELDI ; 
 int CLRSELDO ; 
 int CLRSELINGO ; 
 int CLRSELTIMEO ; 
 int /*<<< orphan*/  CLRSINT0 ; 
 int /*<<< orphan*/  CLRSINT1 ; 
 int /*<<< orphan*/  ahc_flush_device_writes (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_outb (struct ahc_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ahc_clear_intstat(struct ahc_softc *ahc)
{
	/* Clear any interrupt conditions this may have caused */
	ahc_outb(ahc, CLRSINT1, CLRSELTIMEO|CLRATNO|CLRSCSIRSTI
				|CLRBUSFREE|CLRSCSIPERR|CLRPHASECHG|
				CLRREQINIT);
	ahc_flush_device_writes(ahc);
	ahc_outb(ahc, CLRSINT0, CLRSELDO|CLRSELDI|CLRSELINGO);
 	ahc_flush_device_writes(ahc);
	ahc_outb(ahc, CLRINT, CLRSCSIINT);
	ahc_flush_device_writes(ahc);
}