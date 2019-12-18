#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct ide_timing {int dummy; } ;
typedef  int /*<<< orphan*/  ide_hwif_t ;
struct TYPE_8__ {scalar_t__ media; scalar_t__ dma_mode; scalar_t__ pio_mode; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int IDE_TIMING_8BIT ; 
 int IDE_TIMING_SETUP ; 
 int /*<<< orphan*/  ali_fifo_control (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  ali_program_timings (int /*<<< orphan*/ *,TYPE_1__*,struct ide_timing*,int /*<<< orphan*/ ) ; 
 scalar_t__ ide_disk ; 
 TYPE_1__* ide_get_pair_dev (TYPE_1__*) ; 
 int ide_pci_clk ; 
 int /*<<< orphan*/  ide_timing_compute (TYPE_1__*,scalar_t__,struct ide_timing*,unsigned long,int) ; 
 int /*<<< orphan*/  ide_timing_merge (struct ide_timing*,struct ide_timing*,struct ide_timing*,int) ; 

__attribute__((used)) static void ali_set_pio_mode(ide_hwif_t *hwif, ide_drive_t *drive)
{
	ide_drive_t *pair = ide_get_pair_dev(drive);
	int bus_speed = ide_pci_clk ? ide_pci_clk : 33;
	unsigned long T =  1000000 / bus_speed; /* PCI clock based */
	struct ide_timing t;

	ide_timing_compute(drive, drive->pio_mode, &t, T, 1);
	if (pair) {
		struct ide_timing p;

		ide_timing_compute(pair, pair->pio_mode, &p, T, 1);
		ide_timing_merge(&p, &t, &t,
			IDE_TIMING_SETUP | IDE_TIMING_8BIT);
		if (pair->dma_mode) {
			ide_timing_compute(pair, pair->dma_mode, &p, T, 1);
			ide_timing_merge(&p, &t, &t,
				IDE_TIMING_SETUP | IDE_TIMING_8BIT);
		}
	}

	/* 
	 * PIO mode => ATA FIFO on, ATAPI FIFO off
	 */
	ali_fifo_control(hwif, drive, (drive->media == ide_disk) ? 0x05 : 0x00);

	ali_program_timings(hwif, drive, &t, 0);
}