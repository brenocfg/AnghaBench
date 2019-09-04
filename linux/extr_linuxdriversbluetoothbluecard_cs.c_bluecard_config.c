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
struct pcmcia_device {int config_index; int io_lines; TYPE_1__** resource; struct bluecard_info* priv; } ;
struct bluecard_info {int dummy; } ;
struct TYPE_2__ {int end; int start; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH_8 ; 
 int /*<<< orphan*/  bluecard_interrupt ; 
 scalar_t__ bluecard_open (struct bluecard_info*) ; 
 int /*<<< orphan*/  bluecard_release (struct pcmcia_device*) ; 
 int pcmcia_enable_device (struct pcmcia_device*) ; 
 int pcmcia_request_io (struct pcmcia_device*) ; 
 int pcmcia_request_irq (struct pcmcia_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bluecard_config(struct pcmcia_device *link)
{
	struct bluecard_info *info = link->priv;
	int i, n;

	link->config_index = 0x20;

	link->resource[0]->flags |= IO_DATA_PATH_WIDTH_8;
	link->resource[0]->end = 64;
	link->io_lines = 6;

	for (n = 0; n < 0x400; n += 0x40) {
		link->resource[0]->start = n ^ 0x300;
		i = pcmcia_request_io(link);
		if (i == 0)
			break;
	}

	if (i != 0)
		goto failed;

	i = pcmcia_request_irq(link, bluecard_interrupt);
	if (i != 0)
		goto failed;

	i = pcmcia_enable_device(link);
	if (i != 0)
		goto failed;

	if (bluecard_open(info) != 0)
		goto failed;

	return 0;

failed:
	bluecard_release(link);
	return -ENODEV;
}