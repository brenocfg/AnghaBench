#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pcmcia_socket {scalar_t__ pci_irq; scalar_t__ pcmcia_irq; } ;
struct pcmcia_device {scalar_t__ irq; struct pcmcia_socket* socket; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  pcmcia_setup_isa_irq (struct pcmcia_device*,int /*<<< orphan*/ ) ; 

int pcmcia_setup_irq(struct pcmcia_device *p_dev)
{
	struct pcmcia_socket *s = p_dev->socket;

	if (p_dev->irq)
		return 0;

	/* already assigned? */
	if (s->pcmcia_irq) {
		p_dev->irq = s->pcmcia_irq;
		return 0;
	}

	/* prefer an exclusive ISA irq */
	if (!pcmcia_setup_isa_irq(p_dev, 0))
		return 0;

	/* but accept a shared ISA irq */
	if (!pcmcia_setup_isa_irq(p_dev, IRQF_SHARED))
		return 0;

	/* but use the PCI irq otherwise */
	if (s->pci_irq) {
		p_dev->irq = s->pcmcia_irq = s->pci_irq;
		return 0;
	}

	return -EINVAL;
}