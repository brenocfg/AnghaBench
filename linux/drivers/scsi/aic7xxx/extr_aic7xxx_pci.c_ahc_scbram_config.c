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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_int ;
struct ahc_softc {int features; int /*<<< orphan*/  dev_softc; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHC_LSCBS_ENABLED ; 
 int AHC_MULTI_FUNC ; 
 int AHC_ULTRA2 ; 
 int /*<<< orphan*/  DEVCONFIG ; 
 int /*<<< orphan*/  DSCOMMAND0 ; 
 int /*<<< orphan*/  EXTSCBPEN ; 
 int /*<<< orphan*/  EXTSCBTIME ; 
 int /*<<< orphan*/  INTSCBRAMSEL ; 
 int /*<<< orphan*/  SCBBADDR ; 
 int /*<<< orphan*/  SCBRAMSEL ; 
 int /*<<< orphan*/  SCBSIZE32 ; 
 int /*<<< orphan*/  USCBSIZE32 ; 
 int /*<<< orphan*/  ahc_get_pci_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_inb (struct ahc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_outb (struct ahc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ahc_pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ahc_scbram_config(struct ahc_softc *ahc, int enable, int pcheck,
		  int fast, int large)
{
	uint32_t devconfig;

	if (ahc->features & AHC_MULTI_FUNC) {
		/*
		 * Set the SCB Base addr (highest address bit)
		 * depending on which channel we are.
		 */
		ahc_outb(ahc, SCBBADDR, ahc_get_pci_function(ahc->dev_softc));
	}

	ahc->flags &= ~AHC_LSCBS_ENABLED;
	if (large)
		ahc->flags |= AHC_LSCBS_ENABLED;
	devconfig = ahc_pci_read_config(ahc->dev_softc, DEVCONFIG, /*bytes*/4);
	if ((ahc->features & AHC_ULTRA2) != 0) {
		u_int dscommand0;

		dscommand0 = ahc_inb(ahc, DSCOMMAND0);
		if (enable)
			dscommand0 &= ~INTSCBRAMSEL;
		else
			dscommand0 |= INTSCBRAMSEL;
		if (large)
			dscommand0 &= ~USCBSIZE32;
		else
			dscommand0 |= USCBSIZE32;
		ahc_outb(ahc, DSCOMMAND0, dscommand0);
	} else {
		if (fast)
			devconfig &= ~EXTSCBTIME;
		else
			devconfig |= EXTSCBTIME;
		if (enable)
			devconfig &= ~SCBRAMSEL;
		else
			devconfig |= SCBRAMSEL;
		if (large)
			devconfig &= ~SCBSIZE32;
		else
			devconfig |= SCBSIZE32;
	}
	if (pcheck)
		devconfig |= EXTSCBPEN;
	else
		devconfig &= ~EXTSCBPEN;

	ahc_pci_write_config(ahc->dev_softc, DEVCONFIG, devconfig, /*bytes*/4);
}