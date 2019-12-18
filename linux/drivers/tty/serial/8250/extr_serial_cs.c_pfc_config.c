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
struct serial_info {int slave; scalar_t__ manfid; } ;
struct pcmcia_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; TYPE_1__** resource; struct serial_info* priv; } ;
struct TYPE_2__ {scalar_t__ end; unsigned int start; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ MANFID_OSITECH ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int resource_size (TYPE_1__*) ; 
 int setup_serial (struct pcmcia_device*,struct serial_info*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pfc_config(struct pcmcia_device *p_dev)
{
	unsigned int port = 0;
	struct serial_info *info = p_dev->priv;

	if ((p_dev->resource[1]->end != 0) &&
		(resource_size(p_dev->resource[1]) == 8)) {
		port = p_dev->resource[1]->start;
		info->slave = 1;
	} else if ((info->manfid == MANFID_OSITECH) &&
		(resource_size(p_dev->resource[0]) == 0x40)) {
		port = p_dev->resource[0]->start + 0x28;
		info->slave = 1;
	}
	if (info->slave)
		return setup_serial(p_dev, info, port, p_dev->irq);

	dev_warn(&p_dev->dev, "no usable port range found, giving up\n");
	return -ENODEV;
}