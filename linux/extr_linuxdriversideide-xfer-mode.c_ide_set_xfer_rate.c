#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct ide_port_ops {int /*<<< orphan*/ * set_dma_mode; } ;
struct TYPE_7__ {int host_flags; struct ide_port_ops* port_ops; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_8__ {TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int IDE_HFLAG_NO_SET_MODE ; 
 scalar_t__ XFER_PIO_0 ; 
 scalar_t__ XFER_PIO_6 ; 
 scalar_t__ ide_rate_filter (TYPE_2__*,scalar_t__) ; 
 int ide_set_dma_mode (TYPE_2__*,scalar_t__) ; 
 int ide_set_pio_mode (TYPE_2__*,scalar_t__) ; 

int ide_set_xfer_rate(ide_drive_t *drive, u8 rate)
{
	ide_hwif_t *hwif = drive->hwif;
	const struct ide_port_ops *port_ops = hwif->port_ops;

	if (port_ops == NULL || port_ops->set_dma_mode == NULL ||
	    (hwif->host_flags & IDE_HFLAG_NO_SET_MODE))
		return -1;

	rate = ide_rate_filter(drive, rate);

	BUG_ON(rate < XFER_PIO_0);

	if (rate >= XFER_PIO_0 && rate <= XFER_PIO_6)
		return ide_set_pio_mode(drive, rate);

	return ide_set_dma_mode(drive, rate);
}