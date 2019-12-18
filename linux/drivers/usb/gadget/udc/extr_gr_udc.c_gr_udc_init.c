#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_8__ {int /*<<< orphan*/ * ep0; int /*<<< orphan*/  speed; int /*<<< orphan*/  ep_list; } ;
struct gr_udc {int nepo; int nepi; TYPE_6__* epi; TYPE_4__* epo; scalar_t__ remote_wakeup; int /*<<< orphan*/  ep_list; TYPE_2__ gadget; TYPE_1__* dev; } ;
struct device_node {int dummy; } ;
struct TYPE_12__ {TYPE_5__* regs; int /*<<< orphan*/  ep; } ;
struct TYPE_11__ {int /*<<< orphan*/  dmactrl; int /*<<< orphan*/  epctrl; } ;
struct TYPE_10__ {TYPE_3__* regs; } ;
struct TYPE_9__ {int /*<<< orphan*/  dmactrl; int /*<<< orphan*/  epctrl; } ;
struct TYPE_7__ {struct device_node* of_node; } ;

/* Variables and functions */
 int GR_DMACTRL_AI ; 
 int GR_DMACTRL_IE ; 
 int /*<<< orphan*/  GR_EP0_DISCONNECT ; 
 int GR_EPCTRL_EV ; 
 int GR_EPCTRL_MAXPL_POS ; 
 int GR_EPCTRL_PI ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int MAX_CTRL_PL_SIZE ; 
 int /*<<< orphan*/  USB_SPEED_UNKNOWN ; 
 int gr_ep_init (struct gr_udc*,int,int,int) ; 
 int /*<<< orphan*/  gr_set_address (struct gr_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gr_set_ep0state (struct gr_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gr_write32 (int /*<<< orphan*/ *,int) ; 
 scalar_t__ of_property_read_u32_index (struct device_node*,char*,int,int*) ; 

__attribute__((used)) static int gr_udc_init(struct gr_udc *dev)
{
	struct device_node *np = dev->dev->of_node;
	u32 epctrl_val;
	u32 dmactrl_val;
	int i;
	int ret = 0;
	u32 bufsize;

	gr_set_address(dev, 0);

	INIT_LIST_HEAD(&dev->gadget.ep_list);
	dev->gadget.speed = USB_SPEED_UNKNOWN;
	dev->gadget.ep0 = &dev->epi[0].ep;

	INIT_LIST_HEAD(&dev->ep_list);
	gr_set_ep0state(dev, GR_EP0_DISCONNECT);

	for (i = 0; i < dev->nepo; i++) {
		if (of_property_read_u32_index(np, "epobufsizes", i, &bufsize))
			bufsize = 1024;
		ret = gr_ep_init(dev, i, 0, bufsize);
		if (ret)
			return ret;
	}

	for (i = 0; i < dev->nepi; i++) {
		if (of_property_read_u32_index(np, "epibufsizes", i, &bufsize))
			bufsize = 1024;
		ret = gr_ep_init(dev, i, 1, bufsize);
		if (ret)
			return ret;
	}

	/* Must be disabled by default */
	dev->remote_wakeup = 0;

	/* Enable ep0out and ep0in */
	epctrl_val = (MAX_CTRL_PL_SIZE << GR_EPCTRL_MAXPL_POS) | GR_EPCTRL_EV;
	dmactrl_val = GR_DMACTRL_IE | GR_DMACTRL_AI;
	gr_write32(&dev->epo[0].regs->epctrl, epctrl_val);
	gr_write32(&dev->epi[0].regs->epctrl, epctrl_val | GR_EPCTRL_PI);
	gr_write32(&dev->epo[0].regs->dmactrl, dmactrl_val);
	gr_write32(&dev->epi[0].regs->dmactrl, dmactrl_val);

	return 0;
}