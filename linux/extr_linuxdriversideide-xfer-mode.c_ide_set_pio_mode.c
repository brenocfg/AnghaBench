#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct ide_port_ops {int /*<<< orphan*/  (* set_pio_mode ) (TYPE_1__*,TYPE_2__*) ;int /*<<< orphan*/ * set_dma_mode; } ;
struct TYPE_11__ {int host_flags; struct ide_port_ops* port_ops; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_12__ {int /*<<< orphan*/  pio_mode; TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 int IDE_HFLAG_NO_SET_MODE ; 
 int IDE_HFLAG_POST_SET_MODE ; 
 int ide_config_drive_speed (TYPE_2__*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,TYPE_2__*) ; 

int ide_set_pio_mode(ide_drive_t *drive, const u8 mode)
{
	ide_hwif_t *hwif = drive->hwif;
	const struct ide_port_ops *port_ops = hwif->port_ops;

	if (hwif->host_flags & IDE_HFLAG_NO_SET_MODE)
		return 0;

	if (port_ops == NULL || port_ops->set_pio_mode == NULL)
		return -1;

	/*
	 * TODO: temporary hack for some legacy host drivers that didn't
	 * set transfer mode on the device in ->set_pio_mode method...
	 */
	if (port_ops->set_dma_mode == NULL) {
		drive->pio_mode = mode;
		port_ops->set_pio_mode(hwif, drive);
		return 0;
	}

	if (hwif->host_flags & IDE_HFLAG_POST_SET_MODE) {
		if (ide_config_drive_speed(drive, mode))
			return -1;
		drive->pio_mode = mode;
		port_ops->set_pio_mode(hwif, drive);
		return 0;
	} else {
		drive->pio_mode = mode;
		port_ops->set_pio_mode(hwif, drive);
		return ide_config_drive_speed(drive, mode);
	}
}