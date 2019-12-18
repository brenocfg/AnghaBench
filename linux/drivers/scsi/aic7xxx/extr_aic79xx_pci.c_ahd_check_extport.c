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
typedef  int /*<<< orphan*/  vpd ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int u_int ;
struct vpd_config {int dummy; } ;
struct seeprom_config {int adapter_control; } ;
struct ahd_softc {char channel; struct seeprom_config* seep_config; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int AHD_DUMP_SEEPROM ; 
 int /*<<< orphan*/  AHD_SCB_CONFIG_USED ; 
 int /*<<< orphan*/  AHD_USEDEFAULTS ; 
 int CFAUTOTERM ; 
 int CFSEAUTOTERM ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ NVRAM_SCB_OFFSET ; 
 scalar_t__ SCB_BASE ; 
 int /*<<< orphan*/  TRUE ; 
 int ahd_acquire_seeprom (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_configure_termination (struct ahd_softc*,int) ; 
 int ahd_debug ; 
 int ahd_default_config (struct ahd_softc*) ; 
 char ahd_inb_scbram (struct ahd_softc*,scalar_t__) ; 
 int /*<<< orphan*/  ahd_inw_scbram (struct ahd_softc*,scalar_t__) ; 
 int /*<<< orphan*/  ahd_name (struct ahd_softc*) ; 
 int ahd_parse_cfgdata (struct ahd_softc*,struct seeprom_config*) ; 
 int ahd_parse_vpddata (struct ahd_softc*,struct vpd_config*) ; 
 int ahd_read_seeprom (struct ahd_softc*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_release_seeprom (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_set_scbptr (struct ahd_softc*,int) ; 
 int ahd_verify_cksum (struct seeprom_config*) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  kfree (struct seeprom_config*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static int
ahd_check_extport(struct ahd_softc *ahd)
{
	struct	vpd_config vpd;
	struct	seeprom_config *sc;
	u_int	adapter_control;
	int	have_seeprom;
	int	error;

	sc = ahd->seep_config;
	have_seeprom = ahd_acquire_seeprom(ahd);
	if (have_seeprom) {
		u_int start_addr;

		/*
		 * Fetch VPD for this function and parse it.
		 */
		if (bootverbose) 
			printk("%s: Reading VPD from SEEPROM...",
			       ahd_name(ahd));

		/* Address is always in units of 16bit words */
		start_addr = ((2 * sizeof(*sc))
			    + (sizeof(vpd) * (ahd->channel - 'A'))) / 2;

		error = ahd_read_seeprom(ahd, (uint16_t *)&vpd,
					 start_addr, sizeof(vpd)/2,
					 /*bytestream*/TRUE);
		if (error == 0)
			error = ahd_parse_vpddata(ahd, &vpd);
		if (bootverbose) 
			printk("%s: VPD parsing %s\n",
			       ahd_name(ahd),
			       error == 0 ? "successful" : "failed");

		if (bootverbose) 
			printk("%s: Reading SEEPROM...", ahd_name(ahd));

		/* Address is always in units of 16bit words */
		start_addr = (sizeof(*sc) / 2) * (ahd->channel - 'A');

		error = ahd_read_seeprom(ahd, (uint16_t *)sc,
					 start_addr, sizeof(*sc)/2,
					 /*bytestream*/FALSE);

		if (error != 0) {
			printk("Unable to read SEEPROM\n");
			have_seeprom = 0;
		} else {
			have_seeprom = ahd_verify_cksum(sc);

			if (bootverbose) {
				if (have_seeprom == 0)
					printk ("checksum error\n");
				else
					printk ("done.\n");
			}
		}
		ahd_release_seeprom(ahd);
	}

	if (!have_seeprom) {
		u_int	  nvram_scb;

		/*
		 * Pull scratch ram settings and treat them as
		 * if they are the contents of an seeprom if
		 * the 'ADPT', 'BIOS', or 'ASPI' signature is found
		 * in SCB 0xFF.  We manually compose the data as 16bit
		 * values to avoid endian issues.
		 */
		ahd_set_scbptr(ahd, 0xFF);
		nvram_scb = ahd_inb_scbram(ahd, SCB_BASE + NVRAM_SCB_OFFSET);
		if (nvram_scb != 0xFF
		 && ((ahd_inb_scbram(ahd, SCB_BASE + 0) == 'A'
		   && ahd_inb_scbram(ahd, SCB_BASE + 1) == 'D'
		   && ahd_inb_scbram(ahd, SCB_BASE + 2) == 'P'
		   && ahd_inb_scbram(ahd, SCB_BASE + 3) == 'T')
		  || (ahd_inb_scbram(ahd, SCB_BASE + 0) == 'B'
		   && ahd_inb_scbram(ahd, SCB_BASE + 1) == 'I'
		   && ahd_inb_scbram(ahd, SCB_BASE + 2) == 'O'
		   && ahd_inb_scbram(ahd, SCB_BASE + 3) == 'S')
		  || (ahd_inb_scbram(ahd, SCB_BASE + 0) == 'A'
		   && ahd_inb_scbram(ahd, SCB_BASE + 1) == 'S'
		   && ahd_inb_scbram(ahd, SCB_BASE + 2) == 'P'
		   && ahd_inb_scbram(ahd, SCB_BASE + 3) == 'I'))) {
			uint16_t *sc_data;
			int	  i;

			ahd_set_scbptr(ahd, nvram_scb);
			sc_data = (uint16_t *)sc;
			for (i = 0; i < 64; i += 2)
				*sc_data++ = ahd_inw_scbram(ahd, SCB_BASE+i);
			have_seeprom = ahd_verify_cksum(sc);
			if (have_seeprom)
				ahd->flags |= AHD_SCB_CONFIG_USED;
		}
	}

#ifdef AHD_DEBUG
	if (have_seeprom != 0
	 && (ahd_debug & AHD_DUMP_SEEPROM) != 0) {
		uint16_t *sc_data;
		int	  i;

		printk("%s: Seeprom Contents:", ahd_name(ahd));
		sc_data = (uint16_t *)sc;
		for (i = 0; i < (sizeof(*sc)); i += 2)
			printk("\n\t0x%.4x", sc_data[i]);
		printk("\n");
	}
#endif

	if (!have_seeprom) {
		if (bootverbose)
			printk("%s: No SEEPROM available.\n", ahd_name(ahd));
		ahd->flags |= AHD_USEDEFAULTS;
		error = ahd_default_config(ahd);
		adapter_control = CFAUTOTERM|CFSEAUTOTERM;
		kfree(ahd->seep_config);
		ahd->seep_config = NULL;
	} else {
		error = ahd_parse_cfgdata(ahd, sc);
		adapter_control = sc->adapter_control;
	}
	if (error != 0)
		return (error);

	ahd_configure_termination(ahd, adapter_control);

	return (0);
}