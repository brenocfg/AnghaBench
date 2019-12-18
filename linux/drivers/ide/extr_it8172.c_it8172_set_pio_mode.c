#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct pci_dev {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_7__ {int pio_mode; int dn; scalar_t__ media; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 int XFER_PIO_0 ; 
 scalar_t__ ide_disk ; 
 scalar_t__ ide_pio_need_iordy (TYPE_2__*,int const) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int,int) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void it8172_set_pio_mode(ide_hwif_t *hwif, ide_drive_t *drive)
{
	struct pci_dev *dev	= to_pci_dev(hwif->dev);
	u16 drive_enables;
	u32 drive_timing;
	const u8 pio = drive->pio_mode - XFER_PIO_0;

	/*
	 * The highest value of DIOR/DIOW pulse width and recovery time
	 * that can be set in the IT8172 is 8 PCI clock cycles.  As a result,
	 * it cannot be configured for PIO mode 0.  This table sets these
	 * parameters to the maximum supported by the IT8172.
	 */
	static const u8 timings[] = { 0x3f, 0x3c, 0x1b, 0x12, 0x0a };

	pci_read_config_word(dev, 0x40, &drive_enables);
	pci_read_config_dword(dev, 0x44, &drive_timing);

	/*
	 * Enable port 0x44. The IT8172 spec is confused; it calls
	 * this register the "Slave IDE Timing Register", but in fact,
	 * it controls timing for both master and slave drives.
	 */
	drive_enables |= 0x4000;

	drive_enables &= drive->dn ? 0xc006 : 0xc060;
	if (drive->media == ide_disk)
		/* enable prefetch */
		drive_enables |= 0x0004 << (drive->dn * 4);
	if (ide_pio_need_iordy(drive, pio))
		/* enable IORDY sample-point */
		drive_enables |= 0x0002 << (drive->dn * 4);

	drive_timing &= drive->dn ? 0x00003f00 : 0x000fc000;
	drive_timing |= timings[pio] << (drive->dn * 6 + 8);

	pci_write_config_word(dev, 0x40, drive_enables);
	pci_write_config_dword(dev, 0x44, drive_timing);
}