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
typedef  int u16 ;
struct pci_dev {int dummy; } ;
struct TYPE_3__ {unsigned long config_data; int rqsize; int /*<<< orphan*/  dma_base; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ide_hwif_t ;

/* Variables and functions */
 int inw (unsigned long) ; 
 int /*<<< orphan*/  outw (int,unsigned long) ; 
 unsigned long pci_resource_start (struct pci_dev*,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_hwif_tc86c001(ide_hwif_t *hwif)
{
	struct pci_dev *dev	= to_pci_dev(hwif->dev);
	unsigned long sc_base	= pci_resource_start(dev, 5);
	u16 scr1		= inw(sc_base + 0x00);

	/* System Control 1 Register bit 15 (Soft Reset) set */
	outw(scr1 |  0x8000, sc_base + 0x00);

	/* System Control 1 Register bit 14 (FIFO Reset) set */
	outw(scr1 |  0x4000, sc_base + 0x00);

	/* System Control 1 Register: reset clear */
	outw(scr1 & ~0xc000, sc_base + 0x00);

	/* Store the system control register base for convenience... */
	hwif->config_data = sc_base;

	if (!hwif->dma_base)
		return;

	/*
	 * Sector Count Control Register bits 0 and 1 set:
	 * software sets Sector Count Register for master and slave device
	 */
	outw(0x0003, sc_base + 0x0c);

	/* Sector Count Register limit */
	hwif->rqsize	 = 0xffff;
}