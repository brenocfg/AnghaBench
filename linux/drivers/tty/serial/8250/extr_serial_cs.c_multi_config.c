#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct serial_info {int multi; scalar_t__ manfid; scalar_t__ prodid; int c950ctrl; TYPE_1__* quirk; } ;
struct pcmcia_device {int config_index; int /*<<< orphan*/  irq; TYPE_2__** resource; int /*<<< orphan*/  dev; struct serial_info* priv; } ;
struct TYPE_4__ {int start; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* wakeup ) (struct pcmcia_device*) ;int /*<<< orphan*/  (* config ) (struct pcmcia_device*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ MANFID_OXSEMI ; 
 scalar_t__ MANFID_POSSIO ; 
 scalar_t__ PRODID_POSSIO_GCC ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  multi_config_check ; 
 int /*<<< orphan*/  multi_config_check_notpicky ; 
 int pcmcia_enable_device (struct pcmcia_device*) ; 
 scalar_t__ pcmcia_loop_config (struct pcmcia_device*,int /*<<< orphan*/ ,int*) ; 
 int setup_serial (struct pcmcia_device*,struct serial_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct pcmcia_device*) ; 
 int /*<<< orphan*/  stub2 (struct pcmcia_device*) ; 

__attribute__((used)) static int multi_config(struct pcmcia_device *link)
{
	struct serial_info *info = link->priv;
	int i, base2 = 0;

	/* First, look for a generic full-sized window */
	if (!pcmcia_loop_config(link, multi_config_check, &info->multi))
		base2 = link->resource[0]->start + 8;
	else {
		/* If that didn't work, look for two windows */
		info->multi = 2;
		if (pcmcia_loop_config(link, multi_config_check_notpicky,
				       &base2)) {
			dev_warn(&link->dev,
				 "no usable port range found, giving up\n");
			return -ENODEV;
		}
	}

	if (!link->irq)
		dev_warn(&link->dev, "no usable IRQ found, continuing...\n");

	/*
	 * Apply any configuration quirks.
	 */
	if (info->quirk && info->quirk->config)
		info->quirk->config(link);

	i = pcmcia_enable_device(link);
	if (i != 0)
		return -ENODEV;

	/* The Oxford Semiconductor OXCF950 cards are in fact single-port:
	 * 8 registers are for the UART, the others are extra registers.
	 * Siemen's MC45 PCMCIA (Possio's GCC) is OXCF950 based too.
	 */
	if (info->manfid == MANFID_OXSEMI || (info->manfid == MANFID_POSSIO &&
				info->prodid == PRODID_POSSIO_GCC)) {
		int err;

		if (link->config_index == 1 ||
		    link->config_index == 3) {
			err = setup_serial(link, info, base2,
					link->irq);
			base2 = link->resource[0]->start;
		} else {
			err = setup_serial(link, info, link->resource[0]->start,
					link->irq);
		}
		info->c950ctrl = base2;

		/*
		 * FIXME: We really should wake up the port prior to
		 * handing it over to the serial layer.
		 */
		if (info->quirk && info->quirk->wakeup)
			info->quirk->wakeup(link);

		return 0;
	}

	setup_serial(link, info, link->resource[0]->start, link->irq);
	for (i = 0; i < info->multi - 1; i++)
		setup_serial(link, info, base2 + (8 * i),
				link->irq);
	return 0;
}