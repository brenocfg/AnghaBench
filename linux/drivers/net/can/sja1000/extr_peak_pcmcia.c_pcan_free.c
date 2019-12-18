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
struct pcmcia_device {struct pcan_pccard* priv; int /*<<< orphan*/  irq; } ;
struct pcan_pccard {int /*<<< orphan*/  ioport_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct pcan_pccard*) ; 
 int /*<<< orphan*/  ioport_unmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct pcan_pccard*) ; 
 int /*<<< orphan*/  pcan_free_channels (struct pcan_pccard*) ; 
 int /*<<< orphan*/  pcan_stop_led_timer (struct pcan_pccard*) ; 

__attribute__((used)) static void pcan_free(struct pcmcia_device *pdev)
{
	struct pcan_pccard *card = pdev->priv;

	if (!card)
		return;

	free_irq(pdev->irq, card);
	pcan_stop_led_timer(card);

	pcan_free_channels(card);

	ioport_unmap(card->ioport_addr);

	kfree(card);
	pdev->priv = NULL;
}