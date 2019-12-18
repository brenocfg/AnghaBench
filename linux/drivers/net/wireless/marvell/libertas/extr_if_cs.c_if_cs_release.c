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
struct pcmcia_device {int /*<<< orphan*/  irq; struct if_cs_card* priv; } ;
struct if_cs_card {scalar_t__ iobase; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct if_cs_card*) ; 
 int /*<<< orphan*/  ioport_unmap (scalar_t__) ; 
 int /*<<< orphan*/  pcmcia_disable_device (struct pcmcia_device*) ; 

__attribute__((used)) static void if_cs_release(struct pcmcia_device *p_dev)
{
	struct if_cs_card *card = p_dev->priv;

	free_irq(p_dev->irq, card);
	pcmcia_disable_device(p_dev);
	if (card->iobase)
		ioport_unmap(card->iobase);
}