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
struct ata_link {int /*<<< orphan*/  ap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_WAIT_AFTER_RESET ; 
 int /*<<< orphan*/  ata_msleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ata_sff_wait_ready (struct ata_link*,unsigned long) ; 

__attribute__((used)) static int pata_s3c_wait_after_reset(struct ata_link *link,
		unsigned long deadline)
{
	int rc;

	ata_msleep(link->ap, ATA_WAIT_AFTER_RESET);

	/* always check readiness of the master device */
	rc = ata_sff_wait_ready(link, deadline);
	/* -ENODEV means the odd clown forgot the D7 pulldown resistor
	 * and TF status is 0xff, bail out on it too.
	 */
	if (rc)
		return rc;

	return 0;
}