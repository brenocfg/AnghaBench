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
typedef  int u32 ;
struct ata_link {int flags; int /*<<< orphan*/  ap; } ;

/* Variables and functions */
 int ATA_LFLAG_NO_DB_DELAY ; 
 int ATA_LINK_RESUME_TRIES ; 
 int EINVAL ; 
 int /*<<< orphan*/  SCR_CONTROL ; 
 int /*<<< orphan*/  SCR_ERROR ; 
 int /*<<< orphan*/  ata_link_warn (struct ata_link*,char*,int) ; 
 int /*<<< orphan*/  ata_msleep (int /*<<< orphan*/ ,int) ; 
 int sata_link_debounce (struct ata_link*,unsigned long const*,unsigned long) ; 
 int sata_scr_read (struct ata_link*,int /*<<< orphan*/ ,int*) ; 
 int sata_scr_write (struct ata_link*,int /*<<< orphan*/ ,int) ; 

int sata_link_resume(struct ata_link *link, const unsigned long *params,
		     unsigned long deadline)
{
	int tries = ATA_LINK_RESUME_TRIES;
	u32 scontrol, serror;
	int rc;

	if ((rc = sata_scr_read(link, SCR_CONTROL, &scontrol)))
		return rc;

	/*
	 * Writes to SControl sometimes get ignored under certain
	 * controllers (ata_piix SIDPR).  Make sure DET actually is
	 * cleared.
	 */
	do {
		scontrol = (scontrol & 0x0f0) | 0x300;
		if ((rc = sata_scr_write(link, SCR_CONTROL, scontrol)))
			return rc;
		/*
		 * Some PHYs react badly if SStatus is pounded
		 * immediately after resuming.  Delay 200ms before
		 * debouncing.
		 */
		if (!(link->flags & ATA_LFLAG_NO_DB_DELAY))
			ata_msleep(link->ap, 200);

		/* is SControl restored correctly? */
		if ((rc = sata_scr_read(link, SCR_CONTROL, &scontrol)))
			return rc;
	} while ((scontrol & 0xf0f) != 0x300 && --tries);

	if ((scontrol & 0xf0f) != 0x300) {
		ata_link_warn(link, "failed to resume link (SControl %X)\n",
			     scontrol);
		return 0;
	}

	if (tries < ATA_LINK_RESUME_TRIES)
		ata_link_warn(link, "link resume succeeded after %d retries\n",
			      ATA_LINK_RESUME_TRIES - tries);

	if ((rc = sata_link_debounce(link, params, deadline)))
		return rc;

	/* clear SError, some PHYs require this even for SRST to work */
	if (!(rc = sata_scr_read(link, SCR_ERROR, &serror)))
		rc = sata_scr_write(link, SCR_ERROR, serror);

	return rc != -EINVAL ? rc : 0;
}