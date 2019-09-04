#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct pci_dev {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_6__ {int pio_mode; size_t dn; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 int XFER_PIO_0 ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int const,int const) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int,int) ; 
 scalar_t__ svwks_csb_check (struct pci_dev*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void svwks_set_pio_mode(ide_hwif_t *hwif, ide_drive_t *drive)
{
	static const u8 pio_modes[] = { 0x5d, 0x47, 0x34, 0x22, 0x20 };
	static const u8 drive_pci[] = { 0x41, 0x40, 0x43, 0x42 };

	struct pci_dev *dev = to_pci_dev(hwif->dev);
	const u8 pio = drive->pio_mode - XFER_PIO_0;

	pci_write_config_byte(dev, drive_pci[drive->dn], pio_modes[pio]);

	if (svwks_csb_check(dev)) {
		u16 csb_pio = 0;

		pci_read_config_word(dev, 0x4a, &csb_pio);

		csb_pio &= ~(0x0f << (4 * drive->dn));
		csb_pio |= (pio << (4 * drive->dn));

		pci_write_config_word(dev, 0x4a, csb_pio);
	}
}