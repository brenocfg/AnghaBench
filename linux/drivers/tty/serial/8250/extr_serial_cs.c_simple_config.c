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
struct serial_info {scalar_t__ manfid; TYPE_1__* quirk; scalar_t__ multi; } ;
struct pcmcia_device {int config_index; int /*<<< orphan*/  irq; TYPE_2__** resource; int /*<<< orphan*/  dev; int /*<<< orphan*/  config_flags; struct serial_info* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  start; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* config ) (struct pcmcia_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_AUTO_SET_VPP ; 
 int ENODEV ; 
 scalar_t__ MANFID_3COM ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int pcmcia_enable_device (struct pcmcia_device*) ; 
 int /*<<< orphan*/  pcmcia_loop_config (struct pcmcia_device*,int /*<<< orphan*/ ,int*) ; 
 int setup_serial (struct pcmcia_device*,struct serial_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_config_check ; 
 int /*<<< orphan*/  simple_config_check_notpicky ; 
 int /*<<< orphan*/  stub1 (struct pcmcia_device*) ; 

__attribute__((used)) static int simple_config(struct pcmcia_device *link)
{
	struct serial_info *info = link->priv;
	int i = -ENODEV, try;

	/*
	 * First pass: look for a config entry that looks normal.
	 * Two tries: without IO aliases, then with aliases.
	 */
	link->config_flags |= CONF_AUTO_SET_VPP;
	for (try = 0; try < 4; try++)
		if (!pcmcia_loop_config(link, simple_config_check, &try))
			goto found_port;

	/*
	 * Second pass: try to find an entry that isn't picky about
	 * its base address, then try to grab any standard serial port
	 * address, and finally try to get any free port.
	 */
	if (!pcmcia_loop_config(link, simple_config_check_notpicky, NULL))
		goto found_port;

	dev_warn(&link->dev, "no usable port range found, giving up\n");
	return -1;

found_port:
	if (info->multi && (info->manfid == MANFID_3COM))
		link->config_index &= ~(0x08);

	/*
	 * Apply any configuration quirks.
	 */
	if (info->quirk && info->quirk->config)
		info->quirk->config(link);

	i = pcmcia_enable_device(link);
	if (i != 0)
		return -1;
	return setup_serial(link, info, link->resource[0]->start, link->irq);
}