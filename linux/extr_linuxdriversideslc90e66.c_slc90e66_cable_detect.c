#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct pci_dev {int dummy; } ;
struct TYPE_3__ {scalar_t__ channel; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ide_hwif_t ;

/* Variables and functions */
 int ATA_CBL_PATA40 ; 
 int ATA_CBL_PATA80 ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 slc90e66_cable_detect(ide_hwif_t *hwif)
{
	struct pci_dev *dev = to_pci_dev(hwif->dev);
	u8 reg47 = 0, mask = hwif->channel ? 0x01 : 0x02;

	pci_read_config_byte(dev, 0x47, &reg47);

	/* bit[0(1)]: 0:80, 1:40 */
	return (reg47 & mask) ? ATA_CBL_PATA40 : ATA_CBL_PATA80;
}