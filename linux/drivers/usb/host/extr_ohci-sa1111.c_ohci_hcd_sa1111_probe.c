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
struct TYPE_3__ {int /*<<< orphan*/  controller; } ;
struct usb_hcd {int /*<<< orphan*/  rsrc_len; int /*<<< orphan*/  rsrc_start; TYPE_1__ self; int /*<<< orphan*/  regs; } ;
struct TYPE_4__ {int /*<<< orphan*/  start; } ;
struct sa1111_dev {int /*<<< orphan*/  mapbase; int /*<<< orphan*/  dev; TYPE_2__ res; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_wakeup_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hcd_name ; 
 int /*<<< orphan*/  ohci_sa1111_hc_driver ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (TYPE_2__*) ; 
 int sa1111_get_irq (struct sa1111_dev*,int) ; 
 int sa1111_start_hc (struct sa1111_dev*) ; 
 int /*<<< orphan*/  sa1111_stop_hc (struct sa1111_dev*) ; 
 int usb_add_hcd (struct usb_hcd*,int,int /*<<< orphan*/ ) ; 
 struct usb_hcd* usb_create_hcd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ usb_disabled () ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int ohci_hcd_sa1111_probe(struct sa1111_dev *dev)
{
	struct usb_hcd *hcd;
	int ret, irq;

	if (usb_disabled())
		return -ENODEV;

	/*
	 * We don't call dma_set_mask_and_coherent() here because the
	 * DMA mask has already been appropraitely setup by the core
	 * SA-1111 bus code (which includes bug workarounds.)
	 */

	hcd = usb_create_hcd(&ohci_sa1111_hc_driver, &dev->dev, "sa1111");
	if (!hcd)
		return -ENOMEM;

	hcd->rsrc_start = dev->res.start;
	hcd->rsrc_len = resource_size(&dev->res);

	irq = sa1111_get_irq(dev, 1);
	if (irq <= 0) {
		ret = irq ? : -ENXIO;
		goto err1;
	}

	if (!request_mem_region(hcd->rsrc_start, hcd->rsrc_len, hcd_name)) {
		dev_dbg(&dev->dev, "request_mem_region failed\n");
		ret = -EBUSY;
		goto err1;
	}

	hcd->regs = dev->mapbase;

	ret = sa1111_start_hc(dev);
	if (ret)
		goto err2;

	ret = usb_add_hcd(hcd, irq, 0);
	if (ret == 0) {
		device_wakeup_enable(hcd->self.controller);
		return ret;
	}

	sa1111_stop_hc(dev);
 err2:
	release_mem_region(hcd->rsrc_start, hcd->rsrc_len);
 err1:
	usb_put_hcd(hcd);
	return ret;
}