#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct net2272 {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; int /*<<< orphan*/  gadget; int /*<<< orphan*/  chiprev; int /*<<< orphan*/  base_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHIPREV_2272 ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_attr_registers ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int device_create_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_mode_string () ; 
 int /*<<< orphan*/  driver_desc ; 
 int /*<<< orphan*/  driver_name ; 
 int /*<<< orphan*/  driver_vers ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net2272*) ; 
 int /*<<< orphan*/  net2272_gadget_release ; 
 int /*<<< orphan*/  net2272_irq ; 
 scalar_t__ net2272_present (struct net2272*) ; 
 int /*<<< orphan*/  net2272_read (struct net2272*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net2272_usb_reinit (struct net2272*) ; 
 int /*<<< orphan*/  net2272_usb_reset (struct net2272*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,struct net2272*) ; 
 int usb_add_gadget_udc_release (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
net2272_probe_fin(struct net2272 *dev, unsigned int irqflags)
{
	int ret;

	/* See if there... */
	if (net2272_present(dev)) {
		dev_warn(dev->dev, "2272 not found!\n");
		ret = -ENODEV;
		goto err;
	}

	net2272_usb_reset(dev);
	net2272_usb_reinit(dev);

	ret = request_irq(dev->irq, net2272_irq, irqflags, driver_name, dev);
	if (ret) {
		dev_err(dev->dev, "request interrupt %i failed\n", dev->irq);
		goto err;
	}

	dev->chiprev = net2272_read(dev, CHIPREV_2272);

	/* done */
	dev_info(dev->dev, "%s\n", driver_desc);
	dev_info(dev->dev, "irq %i, mem %p, chip rev %04x, dma %s\n",
		dev->irq, dev->base_addr, dev->chiprev,
		dma_mode_string());
	dev_info(dev->dev, "version: %s\n", driver_vers);

	ret = device_create_file(dev->dev, &dev_attr_registers);
	if (ret)
		goto err_irq;

	ret = usb_add_gadget_udc_release(dev->dev, &dev->gadget,
			net2272_gadget_release);
	if (ret)
		goto err_add_udc;

	return 0;

err_add_udc:
	device_remove_file(dev->dev, &dev_attr_registers);
 err_irq:
	free_irq(dev->irq, dev);
 err:
	return ret;
}