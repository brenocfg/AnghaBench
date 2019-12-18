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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  u_int16_t ;
typedef  int u_int ;
struct seeprom_descriptor {int /*<<< orphan*/  sd_DI; int /*<<< orphan*/  sd_DO; int /*<<< orphan*/  sd_CK; int /*<<< orphan*/  sd_CS; int /*<<< orphan*/  sd_RDY; scalar_t__ sd_MS; void* sd_chip; void* sd_dataout_offset; void* sd_status_offset; void* sd_control_offset; struct ahc_softc* sd_ahc; } ;
struct seeprom_config {int dummy; } ;
struct ahc_softc {int chip; int flags; char channel; int /*<<< orphan*/ * seep_config; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;

/* Variables and functions */
 int AHC_LARGE_SEEPROM ; 
 int AHC_PCI ; 
 int AHC_VL ; 
 void* C46 ; 
 void* C56_66 ; 
 int /*<<< orphan*/  CK_2840 ; 
 int /*<<< orphan*/  CS_2840 ; 
 int /*<<< orphan*/  DI_2840 ; 
 int /*<<< orphan*/  DO_2840 ; 
 int /*<<< orphan*/  EEPROM_TF ; 
 int EINVAL ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  SEECK ; 
 int /*<<< orphan*/  SEECS ; 
 void* SEECTL ; 
 void* SEECTL_2840 ; 
 int /*<<< orphan*/  SEEDI ; 
 int /*<<< orphan*/  SEEDO ; 
 scalar_t__ SEEMS ; 
 int /*<<< orphan*/  SEERDY ; 
 void* STATUS_2840 ; 
 int TRUE ; 
 int ahc_acquire_seeprom (struct ahc_softc*,struct seeprom_descriptor*) ; 
 int ahc_is_paused (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_lock (struct ahc_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ahc_pause (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_read_seeprom (struct seeprom_descriptor*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ahc_release_seeprom (struct seeprom_descriptor*) ; 
 int /*<<< orphan*/  ahc_unlock (struct ahc_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ahc_unpause (struct ahc_softc*) ; 
 int ahc_verify_cksum (struct seeprom_config*) ; 
 int /*<<< orphan*/  ahc_write_seeprom (struct seeprom_descriptor*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 

int
ahc_proc_write_seeprom(struct Scsi_Host *shost, char *buffer, int length)
{
	struct	ahc_softc *ahc = *(struct ahc_softc **)shost->hostdata;
	struct seeprom_descriptor sd;
	int have_seeprom;
	u_long s;
	int paused;
	int written;

	/* Default to failure. */
	written = -EINVAL;
	ahc_lock(ahc, &s);
	paused = ahc_is_paused(ahc);
	if (!paused)
		ahc_pause(ahc);

	if (length != sizeof(struct seeprom_config)) {
		printk("ahc_proc_write_seeprom: incorrect buffer size\n");
		goto done;
	}

	have_seeprom = ahc_verify_cksum((struct seeprom_config*)buffer);
	if (have_seeprom == 0) {
		printk("ahc_proc_write_seeprom: cksum verification failed\n");
		goto done;
	}

	sd.sd_ahc = ahc;
#if AHC_PCI_CONFIG > 0
	if ((ahc->chip & AHC_PCI) != 0) {
		sd.sd_control_offset = SEECTL;
		sd.sd_status_offset = SEECTL;
		sd.sd_dataout_offset = SEECTL;
		if (ahc->flags & AHC_LARGE_SEEPROM)
			sd.sd_chip = C56_66;
		else
			sd.sd_chip = C46;
		sd.sd_MS = SEEMS;
		sd.sd_RDY = SEERDY;
		sd.sd_CS = SEECS;
		sd.sd_CK = SEECK;
		sd.sd_DO = SEEDO;
		sd.sd_DI = SEEDI;
		have_seeprom = ahc_acquire_seeprom(ahc, &sd);
	} else
#endif
	if ((ahc->chip & AHC_VL) != 0) {
		sd.sd_control_offset = SEECTL_2840;
		sd.sd_status_offset = STATUS_2840;
		sd.sd_dataout_offset = STATUS_2840;		
		sd.sd_chip = C46;
		sd.sd_MS = 0;
		sd.sd_RDY = EEPROM_TF;
		sd.sd_CS = CS_2840;
		sd.sd_CK = CK_2840;
		sd.sd_DO = DO_2840;
		sd.sd_DI = DI_2840;
		have_seeprom = TRUE;
	} else {
		printk("ahc_proc_write_seeprom: unsupported adapter type\n");
		goto done;
	}

	if (!have_seeprom) {
		printk("ahc_proc_write_seeprom: No Serial EEPROM\n");
		goto done;
	} else {
		u_int start_addr;

		if (ahc->seep_config == NULL) {
			ahc->seep_config = kmalloc(sizeof(*ahc->seep_config), GFP_ATOMIC);
			if (ahc->seep_config == NULL) {
				printk("aic7xxx: Unable to allocate serial "
				       "eeprom buffer.  Write failing\n");
				goto done;
			}
		}
		printk("aic7xxx: Writing Serial EEPROM\n");
		start_addr = 32 * (ahc->channel - 'A');
		ahc_write_seeprom(&sd, (u_int16_t *)buffer, start_addr,
				  sizeof(struct seeprom_config)/2);
		ahc_read_seeprom(&sd, (uint16_t *)ahc->seep_config,
				 start_addr, sizeof(struct seeprom_config)/2);
#if AHC_PCI_CONFIG > 0
		if ((ahc->chip & AHC_VL) == 0)
			ahc_release_seeprom(&sd);
#endif
		written = length;
	}

done:
	if (!paused)
		ahc_unpause(ahc);
	ahc_unlock(ahc, &s);
	return (written);
}