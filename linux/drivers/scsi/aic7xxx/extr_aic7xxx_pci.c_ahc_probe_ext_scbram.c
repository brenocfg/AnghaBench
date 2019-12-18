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
struct ahc_softc {int features; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int AHC_LARGE_SCBS ; 
 int /*<<< orphan*/  AHC_SCB_BTT ; 
 int BRKADRINT ; 
 int CLRBRKADRINT ; 
 int /*<<< orphan*/  CLRINT ; 
 int CLRPARERR ; 
 int /*<<< orphan*/  ERROR ; 
 int FAILDIS ; 
 int FALSE ; 
 int /*<<< orphan*/  INTSTAT ; 
 int MPARERR ; 
 int PERRORDIS ; 
 int /*<<< orphan*/  SEQCTL ; 
 int TRUE ; 
 scalar_t__ ahc_ext_scbram_present (struct ahc_softc*) ; 
 int ahc_inb (struct ahc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_name (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_outb (struct ahc_softc*,int /*<<< orphan*/ ,int) ; 
 int ahc_probe_scbs (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_scbram_config (struct ahc_softc*,int,int,int,int) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,char*,char*,int) ; 

__attribute__((used)) static void
ahc_probe_ext_scbram(struct ahc_softc *ahc)
{
	int num_scbs;
	int test_num_scbs;
	int enable;
	int pcheck;
	int fast;
	int large;

	enable = FALSE;
	pcheck = FALSE;
	fast = FALSE;
	large = FALSE;
	num_scbs = 0;
	
	if (ahc_ext_scbram_present(ahc) == 0)
		goto done;

	/*
	 * Probe for the best parameters to use.
	 */
	ahc_scbram_config(ahc, /*enable*/TRUE, pcheck, fast, large);
	num_scbs = ahc_probe_scbs(ahc);
	if (num_scbs == 0) {
		/* The SRAM wasn't really present. */
		goto done;
	}
	enable = TRUE;

	/*
	 * Clear any outstanding parity error
	 * and ensure that parity error reporting
	 * is enabled.
	 */
	ahc_outb(ahc, SEQCTL, 0);
	ahc_outb(ahc, CLRINT, CLRPARERR);
	ahc_outb(ahc, CLRINT, CLRBRKADRINT);

	/* Now see if we can do parity */
	ahc_scbram_config(ahc, enable, /*pcheck*/TRUE, fast, large);
	num_scbs = ahc_probe_scbs(ahc);
	if ((ahc_inb(ahc, INTSTAT) & BRKADRINT) == 0
	 || (ahc_inb(ahc, ERROR) & MPARERR) == 0)
		pcheck = TRUE;

	/* Clear any resulting parity error */
	ahc_outb(ahc, CLRINT, CLRPARERR);
	ahc_outb(ahc, CLRINT, CLRBRKADRINT);

	/* Now see if we can do fast timing */
	ahc_scbram_config(ahc, enable, pcheck, /*fast*/TRUE, large);
	test_num_scbs = ahc_probe_scbs(ahc);
	if (test_num_scbs == num_scbs
	 && ((ahc_inb(ahc, INTSTAT) & BRKADRINT) == 0
	  || (ahc_inb(ahc, ERROR) & MPARERR) == 0))
		fast = TRUE;

	/*
	 * See if we can use large SCBs and still maintain
	 * the same overall count of SCBs.
	 */
	if ((ahc->features & AHC_LARGE_SCBS) != 0) {
		ahc_scbram_config(ahc, enable, pcheck, fast, /*large*/TRUE);
		test_num_scbs = ahc_probe_scbs(ahc);
		if (test_num_scbs >= num_scbs) {
			large = TRUE;
			num_scbs = test_num_scbs;
	 		if (num_scbs >= 64) {
				/*
				 * We have enough space to move the
				 * "busy targets table" into SCB space
				 * and make it qualify all the way to the
				 * lun level.
				 */
				ahc->flags |= AHC_SCB_BTT;
			}
		}
	}
done:
	/*
	 * Disable parity error reporting until we
	 * can load instruction ram.
	 */
	ahc_outb(ahc, SEQCTL, PERRORDIS|FAILDIS);
	/* Clear any latched parity error */
	ahc_outb(ahc, CLRINT, CLRPARERR);
	ahc_outb(ahc, CLRINT, CLRBRKADRINT);
	if (bootverbose && enable) {
		printk("%s: External SRAM, %s access%s, %dbytes/SCB\n",
		       ahc_name(ahc), fast ? "fast" : "slow", 
		       pcheck ? ", parity checking enabled" : "",
		       large ? 64 : 32);
	}
	ahc_scbram_config(ahc, enable, pcheck, fast, large);
}