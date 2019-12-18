#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct pci_dev {int dummy; } ;
struct TYPE_8__ {scalar_t__ ctl_addr; } ;
struct TYPE_10__ {int channel; unsigned long select_data; scalar_t__ dma_base; int /*<<< orphan*/  irq; TYPE_3__* tp_ops; TYPE_2__ io_ports; TYPE_1__* mate; int /*<<< orphan*/  dev; } ;
typedef  TYPE_4__ ide_hwif_t ;
struct TYPE_9__ {int (* read_status ) (TYPE_4__*) ;} ;
struct TYPE_7__ {unsigned long select_data; } ;

/* Variables and functions */
 int ATA_BUSY ; 
 scalar_t__ ATA_DMA_STATUS ; 
 int /*<<< orphan*/ * ns87415_control ; 
 int /*<<< orphan*/  ns87415_count ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  pci_get_legacy_ide_irq (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,unsigned int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int,unsigned int) ; 
 int stub1 (TYPE_4__*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void init_hwif_ns87415 (ide_hwif_t *hwif)
{
	struct pci_dev *dev = to_pci_dev(hwif->dev);
	unsigned int ctrl, using_inta;
	u8 progif;
#ifdef __sparc_v9__
	int timeout;
	u8 stat;
#endif

	/*
	 * We cannot probe for IRQ: both ports share common IRQ on INTA.
	 * Also, leave IRQ masked during drive probing, to prevent infinite
	 * interrupts from a potentially floating INTA..
	 *
	 * IRQs get unmasked in dev_select() when drive is first used.
	 */
	(void) pci_read_config_dword(dev, 0x40, &ctrl);
	(void) pci_read_config_byte(dev, 0x09, &progif);
	/* is irq in "native" mode? */
	using_inta = progif & (1 << (hwif->channel << 1));
	if (!using_inta)
		using_inta = ctrl & (1 << (4 + hwif->channel));
	if (hwif->mate) {
		hwif->select_data = hwif->mate->select_data;
	} else {
		hwif->select_data = (unsigned long)
					&ns87415_control[ns87415_count++];
		ctrl |= (1 << 8) | (1 << 9);	/* mask both IRQs */
		if (using_inta)
			ctrl &= ~(1 << 6);	/* unmask INTA */
		*((unsigned int *)hwif->select_data) = ctrl;
		(void) pci_write_config_dword(dev, 0x40, ctrl);

		/*
		 * Set prefetch size to 512 bytes for both ports,
		 * but don't turn on/off prefetching here.
		 */
		pci_write_config_byte(dev, 0x55, 0xee);

#ifdef __sparc_v9__
		/*
		 * XXX: Reset the device, if we don't it will not respond to
		 *      dev_select() properly during first ide_probe_port().
		 */
		timeout = 10000;
		outb(12, hwif->io_ports.ctl_addr);
		udelay(10);
		outb(8, hwif->io_ports.ctl_addr);
		do {
			udelay(50);
			stat = hwif->tp_ops->read_status(hwif);
			if (stat == 0xff)
				break;
		} while ((stat & ATA_BUSY) && --timeout);
#endif
	}

	if (!using_inta)
		hwif->irq = pci_get_legacy_ide_irq(dev, hwif->channel);

	if (!hwif->dma_base)
		return;

	outb(0x60, hwif->dma_base + ATA_DMA_STATUS);
}