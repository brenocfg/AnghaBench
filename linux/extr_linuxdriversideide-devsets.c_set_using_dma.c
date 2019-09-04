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
 int EINVAL ; 
 int EPERM ; 

__attribute__((used)) static int set_using_dma(ide_drive_t *drive, int arg)
{
#ifdef CONFIG_BLK_DEV_IDEDMA
	int err = -EPERM;

	if (arg < 0 || arg > 1)
		return -EINVAL;

	if (ata_id_has_dma(drive->id) == 0)
		goto out;

	if (drive->hwif->dma_ops == NULL)
		goto out;

	err = 0;

	if (arg) {
		if (ide_set_dma(drive))
			err = -EIO;
	} else
		ide_dma_off(drive);

out:
	return err;
#else
	if (arg < 0 || arg > 1)
		return -EINVAL;

	return -EPERM;
#endif
}