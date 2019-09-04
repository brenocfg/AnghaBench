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
typedef  int u8 ;
struct pci_dev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_5__ {int dn; scalar_t__ media; TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 scalar_t__ ide_disk ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void config_drive_art_rwp(ide_drive_t *drive)
{
	ide_hwif_t *hwif	= drive->hwif;
	struct pci_dev *dev	= to_pci_dev(hwif->dev);
	u8 reg4bh		= 0;
	u8 rw_prefetch		= 0;

	pci_read_config_byte(dev, 0x4b, &reg4bh);

	rw_prefetch = reg4bh & ~(0x11 << drive->dn);

	if (drive->media == ide_disk)
		rw_prefetch |= 0x11 << drive->dn;

	if (reg4bh != rw_prefetch)
		pci_write_config_byte(dev, 0x4b, rw_prefetch);
}