#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct pci_dev {int dummy; } ;
struct TYPE_4__ {scalar_t__ channel; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_5__ {int dn; TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ sc1200_get_pci_clock () ; 
 int /*<<< orphan*/ ** sc1200_pio_timings ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sc1200_tunepio(ide_drive_t *drive, u8 pio)
{
	ide_hwif_t *hwif = drive->hwif;
	struct pci_dev *pdev = to_pci_dev(hwif->dev);
	unsigned int basereg = hwif->channel ? 0x50 : 0x40, format = 0;

	pci_read_config_dword(pdev, basereg + 4, &format);
	format = (format >> 31) & 1;
	if (format)
		format += sc1200_get_pci_clock();
	pci_write_config_dword(pdev, basereg + ((drive->dn & 1) << 3),
			       sc1200_pio_timings[format][pio]);
}