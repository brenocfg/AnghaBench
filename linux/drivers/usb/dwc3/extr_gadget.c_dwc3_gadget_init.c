#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int sg_supported; char* name; int lpm_capable; int /*<<< orphan*/  max_speed; int /*<<< orphan*/  speed; int /*<<< orphan*/ * ops; } ;
struct dwc3 {int irq_gadget; scalar_t__ revision; int /*<<< orphan*/  ep0_trb_addr; void* ep0_trb; int /*<<< orphan*/  sysdev; int /*<<< orphan*/  setup_buf; int /*<<< orphan*/  bounce_addr; void* bounce; int /*<<< orphan*/  maximum_speed; TYPE_1__ gadget; int /*<<< orphan*/  dev; int /*<<< orphan*/  num_eps; int /*<<< orphan*/  dis_metastability_quirk; int /*<<< orphan*/  ep0_in_setup; } ;

/* Variables and functions */
 int DWC3_BOUNCE_SIZE ; 
 int /*<<< orphan*/  DWC3_EP0_SETUP_SIZE ; 
 scalar_t__ DWC3_REVISION_220A ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_gadget_free_endpoints (struct dwc3*) ; 
 int dwc3_gadget_get_irq (struct dwc3*) ; 
 int dwc3_gadget_init_endpoints (struct dwc3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_gadget_ops ; 
 int /*<<< orphan*/  dwc3_gadget_set_speed (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_add_gadget_udc (int /*<<< orphan*/ ,TYPE_1__*) ; 

int dwc3_gadget_init(struct dwc3 *dwc)
{
	int ret;
	int irq;

	irq = dwc3_gadget_get_irq(dwc);
	if (irq < 0) {
		ret = irq;
		goto err0;
	}

	dwc->irq_gadget = irq;

	dwc->ep0_trb = dma_alloc_coherent(dwc->sysdev,
					  sizeof(*dwc->ep0_trb) * 2,
					  &dwc->ep0_trb_addr, GFP_KERNEL);
	if (!dwc->ep0_trb) {
		dev_err(dwc->dev, "failed to allocate ep0 trb\n");
		ret = -ENOMEM;
		goto err0;
	}

	dwc->setup_buf = kzalloc(DWC3_EP0_SETUP_SIZE, GFP_KERNEL);
	if (!dwc->setup_buf) {
		ret = -ENOMEM;
		goto err1;
	}

	dwc->bounce = dma_alloc_coherent(dwc->sysdev, DWC3_BOUNCE_SIZE,
			&dwc->bounce_addr, GFP_KERNEL);
	if (!dwc->bounce) {
		ret = -ENOMEM;
		goto err2;
	}

	init_completion(&dwc->ep0_in_setup);

	dwc->gadget.ops			= &dwc3_gadget_ops;
	dwc->gadget.speed		= USB_SPEED_UNKNOWN;
	dwc->gadget.sg_supported	= true;
	dwc->gadget.name		= "dwc3-gadget";
	dwc->gadget.lpm_capable		= true;

	/*
	 * FIXME We might be setting max_speed to <SUPER, however versions
	 * <2.20a of dwc3 have an issue with metastability (documented
	 * elsewhere in this driver) which tells us we can't set max speed to
	 * anything lower than SUPER.
	 *
	 * Because gadget.max_speed is only used by composite.c and function
	 * drivers (i.e. it won't go into dwc3's registers) we are allowing this
	 * to happen so we avoid sending SuperSpeed Capability descriptor
	 * together with our BOS descriptor as that could confuse host into
	 * thinking we can handle super speed.
	 *
	 * Note that, in fact, we won't even support GetBOS requests when speed
	 * is less than super speed because we don't have means, yet, to tell
	 * composite.c that we are USB 2.0 + LPM ECN.
	 */
	if (dwc->revision < DWC3_REVISION_220A &&
	    !dwc->dis_metastability_quirk)
		dev_info(dwc->dev, "changing max_speed on rev %08x\n",
				dwc->revision);

	dwc->gadget.max_speed		= dwc->maximum_speed;

	/*
	 * REVISIT: Here we should clear all pending IRQs to be
	 * sure we're starting from a well known location.
	 */

	ret = dwc3_gadget_init_endpoints(dwc, dwc->num_eps);
	if (ret)
		goto err3;

	ret = usb_add_gadget_udc(dwc->dev, &dwc->gadget);
	if (ret) {
		dev_err(dwc->dev, "failed to register udc\n");
		goto err4;
	}

	dwc3_gadget_set_speed(&dwc->gadget, dwc->maximum_speed);

	return 0;

err4:
	dwc3_gadget_free_endpoints(dwc);

err3:
	dma_free_coherent(dwc->sysdev, DWC3_BOUNCE_SIZE, dwc->bounce,
			dwc->bounce_addr);

err2:
	kfree(dwc->setup_buf);

err1:
	dma_free_coherent(dwc->sysdev, sizeof(*dwc->ep0_trb) * 2,
			dwc->ep0_trb, dwc->ep0_trb_addr);

err0:
	return ret;
}