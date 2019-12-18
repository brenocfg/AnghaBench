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
struct TYPE_4__ {int /*<<< orphan*/  controller; } ;
struct usb_hcd {int /*<<< orphan*/  rsrc_len; scalar_t__ rsrc_start; int /*<<< orphan*/ * regs; TYPE_2__ self; } ;
struct resource {scalar_t__ start; TYPE_1__* parent; } ;
struct device {int /*<<< orphan*/  parent; } ;
struct platform_device {int /*<<< orphan*/  name; struct device dev; } ;
struct hc_driver {int dummy; } ;
struct TYPE_3__ {scalar_t__ start; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  SM501_GATE_USB_HOST ; 
 int /*<<< orphan*/  SM501_IRQ_MASK ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  device_wakeup_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hcd_to_ohci (struct usb_hcd*) ; 
 int /*<<< orphan*/ * ioremap (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ohci_hcd_init (int /*<<< orphan*/ ) ; 
 struct hc_driver ohci_sm501_hc_driver ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_mem_region (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_mem_region (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  sm501_modify_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sm501_unit_power (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int usb_add_hcd (struct usb_hcd*,int,int /*<<< orphan*/ ) ; 
 struct usb_hcd* usb_create_hcd (struct hc_driver const*,struct device*,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_hcd_setup_local_mem (struct usb_hcd*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int ohci_hcd_sm501_drv_probe(struct platform_device *pdev)
{
	const struct hc_driver *driver = &ohci_sm501_hc_driver;
	struct device *dev = &pdev->dev;
	struct resource	*res, *mem;
	int retval, irq;
	struct usb_hcd *hcd = NULL;

	irq = retval = platform_get_irq(pdev, 0);
	if (retval < 0)
		goto err0;

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	if (mem == NULL) {
		dev_err(dev, "no resource definition for memory\n");
		retval = -ENOENT;
		goto err0;
	}

	if (!request_mem_region(mem->start, resource_size(mem), pdev->name)) {
		dev_err(dev, "request_mem_region failed\n");
		retval = -EBUSY;
		goto err0;
	}

	/* allocate, reserve and remap resources for registers */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (res == NULL) {
		dev_err(dev, "no resource definition for registers\n");
		retval = -ENOENT;
		goto err1;
	}

	hcd = usb_create_hcd(driver, &pdev->dev, dev_name(&pdev->dev));
	if (!hcd) {
		retval = -ENOMEM;
		goto err1;
	}

	hcd->rsrc_start = res->start;
	hcd->rsrc_len = resource_size(res);

	if (!request_mem_region(hcd->rsrc_start, hcd->rsrc_len,	pdev->name)) {
		dev_err(dev, "request_mem_region failed\n");
		retval = -EBUSY;
		goto err3;
	}

	hcd->regs = ioremap(hcd->rsrc_start, hcd->rsrc_len);
	if (hcd->regs == NULL) {
		dev_err(dev, "cannot remap registers\n");
		retval = -ENXIO;
		goto err4;
	}

	ohci_hcd_init(hcd_to_ohci(hcd));

	/* The sm501 chip is equipped with local memory that may be used
	 * by on-chip devices such as the video controller and the usb host.
	 * This driver uses genalloc so that usb allocations with
	 * gen_pool_dma_alloc() allocate from this local memory. The dma_handle
	 * returned by gen_pool_dma_alloc() will be an offset starting from 0
	 * for the first local memory byte.
	 *
	 * So as long as data is allocated using gen_pool_dma_alloc() all is
	 * fine. This is however not always the case - buffers may be allocated
	 * using kmalloc() - so the usb core needs to be told that it must copy
	 * data into our local memory if the buffers happen to be placed in
	 * regular memory. A non-null hcd->localmem_pool initialized by the
	 * the call to usb_hcd_setup_local_mem() below does just that.
	 */

	if (usb_hcd_setup_local_mem(hcd, mem->start,
				    mem->start - mem->parent->start,
				    resource_size(mem)) < 0)
		goto err5;
	retval = usb_add_hcd(hcd, irq, IRQF_SHARED);
	if (retval)
		goto err5;
	device_wakeup_enable(hcd->self.controller);

	/* enable power and unmask interrupts */

	sm501_unit_power(dev->parent, SM501_GATE_USB_HOST, 1);
	sm501_modify_reg(dev->parent, SM501_IRQ_MASK, 1 << 6, 0);

	return 0;
err5:
	iounmap(hcd->regs);
err4:
	release_mem_region(hcd->rsrc_start, hcd->rsrc_len);
err3:
	usb_put_hcd(hcd);
err1:
	release_mem_region(mem->start, resource_size(mem));
err0:
	return retval;
}