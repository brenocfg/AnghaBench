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
typedef  int /*<<< orphan*/  ide_drive_t ;

/* Variables and functions */
 int ide_dma_check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ide_dma_off_quietly (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ide_dma_on (int /*<<< orphan*/ *) ; 

int ide_set_dma(ide_drive_t *drive)
{
	int rc;

	/*
	 * Force DMAing for the beginning of the check.
	 * Some chipsets appear to do interesting
	 * things, if not checked and cleared.
	 *   PARANOIA!!!
	 */
	ide_dma_off_quietly(drive);

	rc = ide_dma_check(drive);
	if (rc)
		return rc;

	ide_dma_on(drive);

	return 0;
}