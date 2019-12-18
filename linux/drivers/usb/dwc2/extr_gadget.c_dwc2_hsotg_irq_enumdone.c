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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  speed; } ;
struct dwc2_hsotg {int num_of_eps; int /*<<< orphan*/  dev; scalar_t__* eps_out; scalar_t__* eps_in; TYPE_1__ gadget; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIEPCTL0 ; 
 int /*<<< orphan*/  DOEPCTL0 ; 
 int /*<<< orphan*/  DSTS ; 
#define  DSTS_ENUMSPD_FS 131 
#define  DSTS_ENUMSPD_FS48 130 
#define  DSTS_ENUMSPD_HS 129 
#define  DSTS_ENUMSPD_LS 128 
 int DSTS_ENUMSPD_MASK ; 
 int DSTS_ENUMSPD_SHIFT ; 
 int EP0_MPS_LIMIT ; 
 int /*<<< orphan*/  USB_SPEED_FULL ; 
 int /*<<< orphan*/  USB_SPEED_HIGH ; 
 int /*<<< orphan*/  USB_SPEED_LOW ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_hsotg_enqueue_setup (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_hsotg_set_ep_maxpacket (struct dwc2_hsotg*,int,int,int /*<<< orphan*/ ,int) ; 
 int dwc2_readl (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_speed_string (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dwc2_hsotg_irq_enumdone(struct dwc2_hsotg *hsotg)
{
	u32 dsts = dwc2_readl(hsotg, DSTS);
	int ep0_mps = 0, ep_mps = 8;

	/*
	 * This should signal the finish of the enumeration phase
	 * of the USB handshaking, so we should now know what rate
	 * we connected at.
	 */

	dev_dbg(hsotg->dev, "EnumDone (DSTS=0x%08x)\n", dsts);

	/*
	 * note, since we're limited by the size of transfer on EP0, and
	 * it seems IN transfers must be a even number of packets we do
	 * not advertise a 64byte MPS on EP0.
	 */

	/* catch both EnumSpd_FS and EnumSpd_FS48 */
	switch ((dsts & DSTS_ENUMSPD_MASK) >> DSTS_ENUMSPD_SHIFT) {
	case DSTS_ENUMSPD_FS:
	case DSTS_ENUMSPD_FS48:
		hsotg->gadget.speed = USB_SPEED_FULL;
		ep0_mps = EP0_MPS_LIMIT;
		ep_mps = 1023;
		break;

	case DSTS_ENUMSPD_HS:
		hsotg->gadget.speed = USB_SPEED_HIGH;
		ep0_mps = EP0_MPS_LIMIT;
		ep_mps = 1024;
		break;

	case DSTS_ENUMSPD_LS:
		hsotg->gadget.speed = USB_SPEED_LOW;
		ep0_mps = 8;
		ep_mps = 8;
		/*
		 * note, we don't actually support LS in this driver at the
		 * moment, and the documentation seems to imply that it isn't
		 * supported by the PHYs on some of the devices.
		 */
		break;
	}
	dev_info(hsotg->dev, "new device is %s\n",
		 usb_speed_string(hsotg->gadget.speed));

	/*
	 * we should now know the maximum packet size for an
	 * endpoint, so set the endpoints to a default value.
	 */

	if (ep0_mps) {
		int i;
		/* Initialize ep0 for both in and out directions */
		dwc2_hsotg_set_ep_maxpacket(hsotg, 0, ep0_mps, 0, 1);
		dwc2_hsotg_set_ep_maxpacket(hsotg, 0, ep0_mps, 0, 0);
		for (i = 1; i < hsotg->num_of_eps; i++) {
			if (hsotg->eps_in[i])
				dwc2_hsotg_set_ep_maxpacket(hsotg, i, ep_mps,
							    0, 1);
			if (hsotg->eps_out[i])
				dwc2_hsotg_set_ep_maxpacket(hsotg, i, ep_mps,
							    0, 0);
		}
	}

	/* ensure after enumeration our EP0 is active */

	dwc2_hsotg_enqueue_setup(hsotg);

	dev_dbg(hsotg->dev, "EP0: DIEPCTL0=0x%08x, DOEPCTL0=0x%08x\n",
		dwc2_readl(hsotg, DIEPCTL0),
		dwc2_readl(hsotg, DOEPCTL0));
}