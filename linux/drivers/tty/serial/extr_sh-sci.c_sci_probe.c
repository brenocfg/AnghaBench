#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int fifosize; scalar_t__ type; } ;
struct sci_port {TYPE_1__ port; } ;
struct TYPE_6__ {struct plat_sci_port* platform_data; scalar_t__ of_node; } ;
struct platform_device {unsigned int id; TYPE_2__ dev; } ;
struct plat_sci_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 int EINVAL ; 
 scalar_t__ PORT_HSCIF ; 
 scalar_t__ PORT_SCIFA ; 
 scalar_t__ PORT_SCIFB ; 
 int /*<<< orphan*/  dev_attr_rx_fifo_timeout ; 
 int /*<<< orphan*/  dev_attr_rx_fifo_trigger ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int device_create_file (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ is_early_platform_device (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sci_port*) ; 
 struct plat_sci_port* sci_parse_dt (struct platform_device*,unsigned int*) ; 
 struct sci_port* sci_ports ; 
 int /*<<< orphan*/  sci_ports_in_use ; 
 int sci_probe_earlyprintk (struct platform_device*) ; 
 int sci_probe_single (struct platform_device*,unsigned int,struct plat_sci_port*,struct sci_port*) ; 
 int /*<<< orphan*/  sh_bios_gdb_detach () ; 

__attribute__((used)) static int sci_probe(struct platform_device *dev)
{
	struct plat_sci_port *p;
	struct sci_port *sp;
	unsigned int dev_id;
	int ret;

	/*
	 * If we've come here via earlyprintk initialization, head off to
	 * the special early probe. We don't have sufficient device state
	 * to make it beyond this yet.
	 */
	if (is_early_platform_device(dev))
		return sci_probe_earlyprintk(dev);

	if (dev->dev.of_node) {
		p = sci_parse_dt(dev, &dev_id);
		if (p == NULL)
			return -EINVAL;
	} else {
		p = dev->dev.platform_data;
		if (p == NULL) {
			dev_err(&dev->dev, "no platform data supplied\n");
			return -EINVAL;
		}

		dev_id = dev->id;
	}

	sp = &sci_ports[dev_id];
	platform_set_drvdata(dev, sp);

	ret = sci_probe_single(dev, dev_id, p, sp);
	if (ret)
		return ret;

	if (sp->port.fifosize > 1) {
		ret = device_create_file(&dev->dev, &dev_attr_rx_fifo_trigger);
		if (ret)
			return ret;
	}
	if (sp->port.type == PORT_SCIFA || sp->port.type == PORT_SCIFB ||
	    sp->port.type == PORT_HSCIF) {
		ret = device_create_file(&dev->dev, &dev_attr_rx_fifo_timeout);
		if (ret) {
			if (sp->port.fifosize > 1) {
				device_remove_file(&dev->dev,
						   &dev_attr_rx_fifo_trigger);
			}
			return ret;
		}
	}

#ifdef CONFIG_SH_STANDARD_BIOS
	sh_bios_gdb_detach();
#endif

	sci_ports_in_use |= BIT(dev_id);
	return 0;
}