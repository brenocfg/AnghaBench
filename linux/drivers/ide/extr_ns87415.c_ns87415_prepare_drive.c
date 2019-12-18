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
struct pci_dev {int dummy; } ;
struct TYPE_4__ {int channel; scalar_t__ select_data; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_5__ {int dev_flags; int dn; TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 int IDE_DFLAG_PRESENT ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,unsigned char*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int,unsigned int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ns87415_prepare_drive (ide_drive_t *drive, unsigned int use_dma)
{
	ide_hwif_t *hwif = drive->hwif;
	struct pci_dev *dev = to_pci_dev(hwif->dev);
	unsigned int bit, other, new, *old = (unsigned int *) hwif->select_data;
	unsigned long flags;

	local_irq_save(flags);
	new = *old;

	/* Adjust IRQ enable bit */
	bit = 1 << (8 + hwif->channel);

	if (drive->dev_flags & IDE_DFLAG_PRESENT)
		new &= ~bit;
	else
		new |= bit;

	/* Select PIO or DMA, DMA may only be selected for one drive/channel. */
	bit   = 1 << (20 + (drive->dn & 1) + (hwif->channel << 1));
	other = 1 << (20 + (1 - (drive->dn & 1)) + (hwif->channel << 1));
	new = use_dma ? ((new & ~other) | bit) : (new & ~bit);

	if (new != *old) {
		unsigned char stat;

		/*
		 * Don't change DMA engine settings while Write Buffers
		 * are busy.
		 */
		(void) pci_read_config_byte(dev, 0x43, &stat);
		while (stat & 0x03) {
			udelay(1);
			(void) pci_read_config_byte(dev, 0x43, &stat);
		}

		*old = new;
		(void) pci_write_config_dword(dev, 0x40, new);

		/*
		 * And let things settle...
		 */
		udelay(10);
	}

	local_irq_restore(flags);
}