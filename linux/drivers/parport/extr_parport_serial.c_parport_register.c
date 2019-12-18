#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pci_device_id {size_t driver_data; } ;
struct pci_dev {int irq; int /*<<< orphan*/  dev; } ;
struct parport_pc_pci {int numports; int /*<<< orphan*/  (* postinit_hook ) (struct pci_dev*,struct parport_pc_pci*,int) ;TYPE_1__* addr; scalar_t__ (* preinit_hook ) (struct pci_dev*,struct parport_pc_pci*,int,int /*<<< orphan*/ ) ;} ;
struct parport_serial_private {scalar_t__ num_par; struct parport** port; struct parport_pc_pci par; } ;
struct parport {int dummy; } ;
struct TYPE_2__ {int lo; int hi; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (struct parport**) ; 
 int ENODEV ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int IRQ_NONE ; 
 int /*<<< orphan*/  PARPORT_DMA_NONE ; 
 int PARPORT_IRQ_NONE ; 
 struct parport_pc_pci* cards ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned long,unsigned long,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,scalar_t__,int) ; 
 struct parport* parport_pc_probe_port (unsigned long,unsigned long,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct parport_serial_private* pci_get_drvdata (struct pci_dev*) ; 
 unsigned long pci_resource_start (struct pci_dev*,int) ; 
 scalar_t__ stub1 (struct pci_dev*,struct parport_pc_pci*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct pci_dev*,struct parport_pc_pci*,int) ; 

__attribute__((used)) static int parport_register(struct pci_dev *dev, const struct pci_device_id *id)
{
	struct parport_pc_pci *card;
	struct parport_serial_private *priv = pci_get_drvdata (dev);
	int n, success = 0;

	priv->par = cards[id->driver_data];
	card = &priv->par;
	if (card->preinit_hook &&
	    card->preinit_hook (dev, card, PARPORT_IRQ_NONE, PARPORT_DMA_NONE))
		return -ENODEV;

	for (n = 0; n < card->numports; n++) {
		struct parport *port;
		int lo = card->addr[n].lo;
		int hi = card->addr[n].hi;
		unsigned long io_lo, io_hi;
		int irq;

		if (priv->num_par == ARRAY_SIZE (priv->port)) {
			dev_warn(&dev->dev,
				 "only %zu parallel ports supported (%d reported)\n",
				 ARRAY_SIZE(priv->port), card->numports);
			break;
		}

		io_lo = pci_resource_start (dev, lo);
		io_hi = 0;
		if ((hi >= 0) && (hi <= 6))
			io_hi = pci_resource_start (dev, hi);
		else if (hi > 6)
			io_lo += hi; /* Reinterpret the meaning of
                                        "hi" as an offset (see SYBA
                                        def.) */
		/* TODO: test if sharing interrupts works */
		irq = dev->irq;
		if (irq == IRQ_NONE) {
			dev_dbg(&dev->dev,
				"PCI parallel port detected: I/O at %#lx(%#lx)\n",
				io_lo, io_hi);
			irq = PARPORT_IRQ_NONE;
		} else {
			dev_dbg(&dev->dev,
				"PCI parallel port detected: I/O at %#lx(%#lx), IRQ %d\n",
				io_lo, io_hi, irq);
		}
		port = parport_pc_probe_port (io_lo, io_hi, irq,
			      PARPORT_DMA_NONE, &dev->dev, IRQF_SHARED);
		if (port) {
			priv->port[priv->num_par++] = port;
			success = 1;
		}
	}

	if (card->postinit_hook)
		card->postinit_hook (dev, card, !success);

	return 0;
}