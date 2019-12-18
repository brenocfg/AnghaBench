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
struct pcmcia_device {TYPE_1__** resource; } ;
struct TYPE_2__ {int end; int start; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH ; 
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH_8 ; 
 scalar_t__ pcmcia_request_io (struct pcmcia_device*) ; 

__attribute__((used)) static int multi_config_check_notpicky(struct pcmcia_device *p_dev,
				       void *priv_data)
{
	int *base2 = priv_data;

	if (!p_dev->resource[0]->end || !p_dev->resource[1]->end ||
		p_dev->resource[0]->start + 8 != p_dev->resource[1]->start)
		return -ENODEV;

	p_dev->resource[0]->end = p_dev->resource[1]->end = 8;
	p_dev->resource[0]->flags &= ~IO_DATA_PATH_WIDTH;
	p_dev->resource[0]->flags |= IO_DATA_PATH_WIDTH_8;

	if (pcmcia_request_io(p_dev))
		return -ENODEV;

	*base2 = p_dev->resource[0]->start + 8;
	return 0;
}