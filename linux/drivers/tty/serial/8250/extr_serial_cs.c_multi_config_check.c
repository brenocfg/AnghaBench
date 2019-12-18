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
struct TYPE_2__ {int end; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH ; 
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH_8 ; 
 scalar_t__ pcmcia_request_io (struct pcmcia_device*) ; 

__attribute__((used)) static int multi_config_check(struct pcmcia_device *p_dev, void *priv_data)
{
	int *multi = priv_data;

	if (p_dev->resource[1]->end)
		return -EINVAL;

	/*
	 * The quad port cards have bad CIS's, so just look for a
	 * window larger than 8 ports and assume it will be right.
	 */
	if (p_dev->resource[0]->end <= 8)
		return -EINVAL;

	p_dev->resource[0]->flags &= ~IO_DATA_PATH_WIDTH;
	p_dev->resource[0]->flags |= IO_DATA_PATH_WIDTH_8;
	p_dev->resource[0]->end = *multi * 8;

	if (pcmcia_request_io(p_dev))
		return -ENODEV;
	return 0;
}