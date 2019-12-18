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
 int AHC_SCB_MAX ; 
 int /*<<< orphan*/  SCBPTR ; 
 int /*<<< orphan*/  SCB_BASE ; 
 int ahc_inb (struct ahc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_outb (struct ahc_softc*,int /*<<< orphan*/ ,int) ; 

int
ahc_probe_scbs(struct ahc_softc *ahc) {
	int i;

	for (i = 0; i < AHC_SCB_MAX; i++) {

		ahc_outb(ahc, SCBPTR, i);
		ahc_outb(ahc, SCB_BASE, i);
		if (ahc_inb(ahc, SCB_BASE) != i)
			break;
		ahc_outb(ahc, SCBPTR, 0);
		if (ahc_inb(ahc, SCB_BASE) != 0)
			break;
	}
	return (i);
}