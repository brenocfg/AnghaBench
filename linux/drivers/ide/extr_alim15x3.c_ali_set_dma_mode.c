#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct pci_dev {int dummy; } ;
struct ide_timing {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_11__ {int dma_mode; int pio_mode; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 int IDE_TIMING_8BIT ; 
 int IDE_TIMING_SETUP ; 
 int const XFER_UDMA_0 ; 
 int const XFER_UDMA_3 ; 
 int /*<<< orphan*/  ali_program_timings (TYPE_1__*,TYPE_2__*,struct ide_timing*,int) ; 
 TYPE_2__* ide_get_pair_dev (TYPE_2__*) ; 
 int ide_pci_clk ; 
 int /*<<< orphan*/  ide_timing_compute (TYPE_2__*,int,struct ide_timing*,unsigned long,int) ; 
 int /*<<< orphan*/  ide_timing_merge (struct ide_timing*,struct ide_timing*,struct ide_timing*,int) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ali_set_dma_mode(ide_hwif_t *hwif, ide_drive_t *drive)
{
	static u8 udma_timing[7] = { 0xC, 0xB, 0xA, 0x9, 0x8, 0xF, 0xD };
	struct pci_dev *dev	= to_pci_dev(hwif->dev);
	ide_drive_t *pair	= ide_get_pair_dev(drive);
	int bus_speed		= ide_pci_clk ? ide_pci_clk : 33;
	unsigned long T		=  1000000 / bus_speed; /* PCI clock based */
	const u8 speed		= drive->dma_mode;
	u8 tmpbyte		= 0x00;
	struct ide_timing t;

	if (speed < XFER_UDMA_0) {
		ide_timing_compute(drive, drive->dma_mode, &t, T, 1);
		if (pair) {
			struct ide_timing p;

			ide_timing_compute(pair, pair->pio_mode, &p, T, 1);
			ide_timing_merge(&p, &t, &t,
				IDE_TIMING_SETUP | IDE_TIMING_8BIT);
			if (pair->dma_mode) {
				ide_timing_compute(pair, pair->dma_mode,
						&p, T, 1);
				ide_timing_merge(&p, &t, &t,
					IDE_TIMING_SETUP | IDE_TIMING_8BIT);
			}
		}
		ali_program_timings(hwif, drive, &t, 0);
	} else {
		ali_program_timings(hwif, drive, NULL,
				udma_timing[speed - XFER_UDMA_0]);
		if (speed >= XFER_UDMA_3) {
			pci_read_config_byte(dev, 0x4b, &tmpbyte);
			tmpbyte |= 1;
			pci_write_config_byte(dev, 0x4b, tmpbyte);
		}
	}
}