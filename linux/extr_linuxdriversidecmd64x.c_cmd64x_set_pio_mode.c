#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  ide_hwif_t ;
struct TYPE_4__ {int pio_mode; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int XFER_PIO_0 ; 
 int /*<<< orphan*/  cmd64x_program_timings (TYPE_1__*,int) ; 

__attribute__((used)) static void cmd64x_set_pio_mode(ide_hwif_t *hwif, ide_drive_t *drive)
{
	const u8 pio = drive->pio_mode - XFER_PIO_0;

	/*
	 * Filter out the prefetch control values
	 * to prevent PIO5 from being programmed
	 */
	if (pio == 8 || pio == 9)
		return;

	cmd64x_program_timings(drive, XFER_PIO_0 + pio);
}