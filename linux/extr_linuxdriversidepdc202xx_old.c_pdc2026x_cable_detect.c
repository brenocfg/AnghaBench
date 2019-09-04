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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct pci_dev {int dummy; } ;
struct TYPE_3__ {scalar_t__ channel; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ide_hwif_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_CBL_PATA40 ; 
 int /*<<< orphan*/  ATA_CBL_PATA80 ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int,int*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 pdc2026x_cable_detect(ide_hwif_t *hwif)
{
	struct pci_dev *dev = to_pci_dev(hwif->dev);
	u16 CIS, mask = hwif->channel ? (1 << 11) : (1 << 10);

	pci_read_config_word(dev, 0x50, &CIS);

	return (CIS & mask) ? ATA_CBL_PATA40 : ATA_CBL_PATA80;
}