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
struct pcmcia_device {int config_index; TYPE_1__** resource; } ;
struct TYPE_2__ {int end; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int try_io_port (struct pcmcia_device*) ; 

__attribute__((used)) static int axnet_configcheck(struct pcmcia_device *p_dev, void *priv_data)
{
	if (p_dev->config_index == 0)
		return -EINVAL;

	p_dev->config_index = 0x05;
	if (p_dev->resource[0]->end + p_dev->resource[1]->end < 32)
		return -ENODEV;

	return try_io_port(p_dev);
}