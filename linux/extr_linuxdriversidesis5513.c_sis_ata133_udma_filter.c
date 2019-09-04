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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct TYPE_6__ {TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_UDMA5 ; 
 int /*<<< orphan*/  ATA_UDMA6 ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sis_ata133_get_base (TYPE_2__*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 sis_ata133_udma_filter(ide_drive_t *drive)
{
	struct pci_dev *dev = to_pci_dev(drive->hwif->dev);
	u32 regdw = 0;
	u8 drive_pci = sis_ata133_get_base(drive);

	pci_read_config_dword(dev, drive_pci, &regdw);

	/* if ATA133 disable, we should not set speed above UDMA5 */
	return (regdw & 0x08) ? ATA_UDMA6 : ATA_UDMA5;
}