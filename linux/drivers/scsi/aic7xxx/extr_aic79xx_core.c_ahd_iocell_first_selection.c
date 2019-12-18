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
struct ahd_softc {int flags; } ;
typedef  int /*<<< orphan*/  ahd_mode_state ;

/* Variables and functions */
 int AHD_HAD_FIRST_SEL ; 
 int /*<<< orphan*/  AHD_MODE_CFG ; 
 int /*<<< orphan*/  AHD_MODE_SCSI ; 
 int AHD_SHOW_MISC ; 
 int BYPASSENAB ; 
 int /*<<< orphan*/  CLRINT ; 
 int CLRSCSIINT ; 
 int /*<<< orphan*/  DSPDATACTL ; 
 int ENAB40 ; 
 int ENSELDI ; 
 int ENSELDO ; 
 int /*<<< orphan*/  SBLKCTL ; 
 int /*<<< orphan*/  SIMODE0 ; 
 int ahd_debug ; 
 int ahd_inb (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_name (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_outb (struct ahd_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ahd_restore_modes (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_save_modes (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_set_modes (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ahd_iocell_first_selection(struct ahd_softc *ahd)
{
	ahd_mode_state	saved_modes;
	u_int		sblkctl;

	if ((ahd->flags & AHD_HAD_FIRST_SEL) != 0)
		return;
	saved_modes = ahd_save_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	sblkctl = ahd_inb(ahd, SBLKCTL);
	ahd_set_modes(ahd, AHD_MODE_CFG, AHD_MODE_CFG);
#ifdef AHD_DEBUG
	if ((ahd_debug & AHD_SHOW_MISC) != 0)
		printk("%s: iocell first selection\n", ahd_name(ahd));
#endif
	if ((sblkctl & ENAB40) != 0) {
		ahd_outb(ahd, DSPDATACTL,
			 ahd_inb(ahd, DSPDATACTL) & ~BYPASSENAB);
#ifdef AHD_DEBUG
		if ((ahd_debug & AHD_SHOW_MISC) != 0)
			printk("%s: BYPASS now disabled\n", ahd_name(ahd));
#endif
	}
	ahd_outb(ahd, SIMODE0, ahd_inb(ahd, SIMODE0) & ~(ENSELDO|ENSELDI));
	ahd_outb(ahd, CLRINT, CLRSCSIINT);
	ahd_restore_modes(ahd, saved_modes);
	ahd->flags |= AHD_HAD_FIRST_SEL;
}