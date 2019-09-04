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
struct TYPE_2__ {int end; scalar_t__ start; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH ; 
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH_8 ; 
 int pcmcia_request_io (struct pcmcia_device*) ; 

__attribute__((used)) static int bt3c_check_config(struct pcmcia_device *p_dev, void *priv_data)
{
	int *try = priv_data;

	if (!try)
		p_dev->io_lines = 16;

	if ((p_dev->resource[0]->end != 8) || (p_dev->resource[0]->start == 0))
		return -EINVAL;

	p_dev->resource[0]->end = 8;
	p_dev->resource[0]->flags &= ~IO_DATA_PATH_WIDTH;
	p_dev->resource[0]->flags |= IO_DATA_PATH_WIDTH_8;

	return pcmcia_request_io(p_dev);
}