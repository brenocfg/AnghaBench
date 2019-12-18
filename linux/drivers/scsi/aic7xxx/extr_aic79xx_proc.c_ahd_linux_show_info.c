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
typedef  char* uint16_t ;
typedef  int u_int ;
struct seq_file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  numscbs; } ;
struct ahd_softc {char* description; int features; int /*<<< orphan*/  our_id; int /*<<< orphan*/ * seep_config; TYPE_1__ scb_data; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHD_NSEG ; 
 int AHD_WIDE ; 
 char* AIC79XX_DRIVER_VERSION ; 
 int /*<<< orphan*/  ahd_controller_info (struct ahd_softc*,char*) ; 
 int /*<<< orphan*/  ahd_dump_target_state (struct ahd_softc*,struct seq_file*,int /*<<< orphan*/ ,char,int) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,...) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

int
ahd_linux_show_info(struct seq_file *m, struct Scsi_Host *shost)
{
	struct	ahd_softc *ahd = *(struct ahd_softc **)shost->hostdata;
	char	ahd_info[256];
	u_int	max_targ;
	u_int	i;

	seq_printf(m, "Adaptec AIC79xx driver version: %s\n",
		  AIC79XX_DRIVER_VERSION);
	seq_printf(m, "%s\n", ahd->description);
	ahd_controller_info(ahd, ahd_info);
	seq_printf(m, "%s\n", ahd_info);
	seq_printf(m, "Allocated SCBs: %d, SG List Length: %d\n\n",
		  ahd->scb_data.numscbs, AHD_NSEG);

	max_targ = 16;

	if (ahd->seep_config == NULL)
		seq_puts(m, "No Serial EEPROM\n");
	else {
		seq_puts(m, "Serial EEPROM:\n");
		for (i = 0; i < sizeof(*ahd->seep_config)/2; i++) {
			if (((i % 8) == 0) && (i != 0)) {
				seq_putc(m, '\n');
			}
			seq_printf(m, "0x%.4x ",
				  ((uint16_t*)ahd->seep_config)[i]);
		}
		seq_putc(m, '\n');
	}
	seq_putc(m, '\n');

	if ((ahd->features & AHD_WIDE) == 0)
		max_targ = 8;

	for (i = 0; i < max_targ; i++) {

		ahd_dump_target_state(ahd, m, ahd->our_id, 'A',
				      /*target_id*/i);
	}
	return 0;
}