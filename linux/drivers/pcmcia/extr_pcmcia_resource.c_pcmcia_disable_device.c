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
struct resource {int flags; } ;
struct pcmcia_device {scalar_t__ _irq; int /*<<< orphan*/  priv; int /*<<< orphan*/  irq; struct resource** resource; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MAX_IO_WIN ; 
 int MAX_WIN ; 
 int WIN_FLAGS_REQ ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcmcia_release_configuration (struct pcmcia_device*) ; 
 int /*<<< orphan*/  pcmcia_release_io (struct pcmcia_device*) ; 
 int /*<<< orphan*/  pcmcia_release_window (struct pcmcia_device*,struct resource*) ; 

void pcmcia_disable_device(struct pcmcia_device *p_dev)
{
	int i;

	dev_dbg(&p_dev->dev, "disabling device\n");

	for (i = 0; i < MAX_WIN; i++) {
		struct resource *res = p_dev->resource[MAX_IO_WIN + i];
		if (res->flags & WIN_FLAGS_REQ)
			pcmcia_release_window(p_dev, res);
	}

	pcmcia_release_configuration(p_dev);
	pcmcia_release_io(p_dev);
	if (p_dev->_irq) {
		free_irq(p_dev->irq, p_dev->priv);
		p_dev->_irq = 0;
	}
}