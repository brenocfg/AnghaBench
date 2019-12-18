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
struct pcmcia_device {int io_lines; TYPE_1__** resource; } ;
struct TYPE_2__ {int start; int end; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH ; 
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH_16 ; 
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH_8 ; 
 int /*<<< orphan*/  pcmcia_request_io (struct pcmcia_device*) ; 

__attribute__((used)) static int
xirc2ps_config_modem(struct pcmcia_device *p_dev, void *priv_data)
{
	unsigned int ioaddr;

	if ((p_dev->resource[0]->start & 0xf) == 8)
		return -ENODEV;

	p_dev->resource[0]->end = 16;
	p_dev->resource[1]->end = 8;
	p_dev->resource[0]->flags &= ~IO_DATA_PATH_WIDTH;
	p_dev->resource[0]->flags |= IO_DATA_PATH_WIDTH_16;
	p_dev->resource[1]->flags &= ~IO_DATA_PATH_WIDTH;
	p_dev->resource[1]->flags |= IO_DATA_PATH_WIDTH_8;
	p_dev->io_lines = 10;

	p_dev->resource[1]->start = p_dev->resource[0]->start;
	for (ioaddr = 0x300; ioaddr < 0x400; ioaddr += 0x10) {
		p_dev->resource[0]->start = ioaddr;
		if (!pcmcia_request_io(p_dev))
			return 0;
	}
	return -ENODEV;
}