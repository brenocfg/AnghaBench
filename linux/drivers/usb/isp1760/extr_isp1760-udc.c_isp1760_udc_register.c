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
struct TYPE_2__ {char* name; int /*<<< orphan*/  max_speed; int /*<<< orphan*/  speed; int /*<<< orphan*/ * ops; } ;
struct isp1760_udc {int irq; int /*<<< orphan*/  irqname; TYPE_1__ gadget; int /*<<< orphan*/  vbus_timer; int /*<<< orphan*/  lock; int /*<<< orphan*/  regs; struct isp1760_device* isp; } ;
struct isp1760_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  regs; struct isp1760_udc udc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long IRQF_SHARED ; 
 int /*<<< orphan*/  USB_SPEED_HIGH ; 
 int /*<<< orphan*/  USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int,struct isp1760_udc*) ; 
 int isp1760_udc_init (struct isp1760_udc*) ; 
 int /*<<< orphan*/  isp1760_udc_init_eps (struct isp1760_udc*) ; 
 int /*<<< orphan*/  isp1760_udc_irq ; 
 int /*<<< orphan*/  isp1760_udc_ops ; 
 int /*<<< orphan*/  isp1760_udc_vbus_poll ; 
 int /*<<< orphan*/  kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int request_irq (int,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,struct isp1760_udc*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_add_gadget_udc (int /*<<< orphan*/ ,TYPE_1__*) ; 

int isp1760_udc_register(struct isp1760_device *isp, int irq,
			 unsigned long irqflags)
{
	struct isp1760_udc *udc = &isp->udc;
	int ret;

	udc->irq = -1;
	udc->isp = isp;
	udc->regs = isp->regs;

	spin_lock_init(&udc->lock);
	timer_setup(&udc->vbus_timer, isp1760_udc_vbus_poll, 0);

	ret = isp1760_udc_init(udc);
	if (ret < 0)
		return ret;

	udc->irqname = kasprintf(GFP_KERNEL, "%s (udc)", dev_name(isp->dev));
	if (!udc->irqname)
		return -ENOMEM;

	ret = request_irq(irq, isp1760_udc_irq, IRQF_SHARED | irqflags,
			  udc->irqname, udc);
	if (ret < 0)
		goto error;

	udc->irq = irq;

	/*
	 * Initialize the gadget static fields and register its device. Gadget
	 * fields that vary during the life time of the gadget are initialized
	 * by the UDC core.
	 */
	udc->gadget.ops = &isp1760_udc_ops;
	udc->gadget.speed = USB_SPEED_UNKNOWN;
	udc->gadget.max_speed = USB_SPEED_HIGH;
	udc->gadget.name = "isp1761_udc";

	isp1760_udc_init_eps(udc);

	ret = usb_add_gadget_udc(isp->dev, &udc->gadget);
	if (ret < 0)
		goto error;

	return 0;

error:
	if (udc->irq >= 0)
		free_irq(udc->irq, udc);
	kfree(udc->irqname);

	return ret;
}