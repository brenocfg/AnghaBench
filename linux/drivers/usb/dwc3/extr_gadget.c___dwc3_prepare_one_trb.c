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
struct usb_gadget {int speed; } ;
struct usb_ep {int /*<<< orphan*/  desc; } ;
struct dwc3_trb {int /*<<< orphan*/  ctrl; int /*<<< orphan*/  size; int /*<<< orphan*/  bph; int /*<<< orphan*/  bpl; } ;
struct dwc3_ep {scalar_t__ stream_capable; struct usb_ep endpoint; struct dwc3* dwc; } ;
struct dwc3 {int /*<<< orphan*/  dev; struct usb_gadget gadget; } ;
typedef  enum usb_device_speed { ____Placeholder_usb_device_speed } usb_device_speed ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_TRBCTL_CONTROL_SETUP ; 
 int /*<<< orphan*/  DWC3_TRBCTL_ISOCHRONOUS ; 
 int /*<<< orphan*/  DWC3_TRBCTL_ISOCHRONOUS_FIRST ; 
 int /*<<< orphan*/  DWC3_TRBCTL_NORMAL ; 
 int /*<<< orphan*/  DWC3_TRB_CTRL_CHN ; 
 int /*<<< orphan*/  DWC3_TRB_CTRL_CSP ; 
 int /*<<< orphan*/  DWC3_TRB_CTRL_HWO ; 
 int /*<<< orphan*/  DWC3_TRB_CTRL_IOC ; 
 int /*<<< orphan*/  DWC3_TRB_CTRL_ISP_IMI ; 
 int /*<<< orphan*/  DWC3_TRB_CTRL_SID_SOFN (unsigned int) ; 
 int /*<<< orphan*/  DWC3_TRB_SIZE_LENGTH (unsigned int) ; 
 int /*<<< orphan*/  DWC3_TRB_SIZE_PCM1 (unsigned int) ; 
#define  USB_ENDPOINT_XFER_BULK 131 
#define  USB_ENDPOINT_XFER_CONTROL 130 
#define  USB_ENDPOINT_XFER_INT 129 
#define  USB_ENDPOINT_XFER_ISOC 128 
 int USB_SPEED_HIGH ; 
 int /*<<< orphan*/  dev_WARN (int /*<<< orphan*/ ,char*,int) ; 
 int dwc3_calc_trbs_left (struct dwc3_ep*) ; 
 int /*<<< orphan*/  dwc3_ep_inc_enq (struct dwc3_ep*) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_dwc3_prepare_trb (struct dwc3_ep*,struct dwc3_trb*) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 
 scalar_t__ usb_endpoint_dir_out (int /*<<< orphan*/ ) ; 
 unsigned int usb_endpoint_maxp (int /*<<< orphan*/ ) ; 
 int usb_endpoint_type (int /*<<< orphan*/ ) ; 
 scalar_t__ usb_endpoint_xfer_bulk (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __dwc3_prepare_one_trb(struct dwc3_ep *dep, struct dwc3_trb *trb,
		dma_addr_t dma, unsigned length, unsigned chain, unsigned node,
		unsigned stream_id, unsigned short_not_ok, unsigned no_interrupt)
{
	struct dwc3		*dwc = dep->dwc;
	struct usb_gadget	*gadget = &dwc->gadget;
	enum usb_device_speed	speed = gadget->speed;

	trb->size = DWC3_TRB_SIZE_LENGTH(length);
	trb->bpl = lower_32_bits(dma);
	trb->bph = upper_32_bits(dma);

	switch (usb_endpoint_type(dep->endpoint.desc)) {
	case USB_ENDPOINT_XFER_CONTROL:
		trb->ctrl = DWC3_TRBCTL_CONTROL_SETUP;
		break;

	case USB_ENDPOINT_XFER_ISOC:
		if (!node) {
			trb->ctrl = DWC3_TRBCTL_ISOCHRONOUS_FIRST;

			/*
			 * USB Specification 2.0 Section 5.9.2 states that: "If
			 * there is only a single transaction in the microframe,
			 * only a DATA0 data packet PID is used.  If there are
			 * two transactions per microframe, DATA1 is used for
			 * the first transaction data packet and DATA0 is used
			 * for the second transaction data packet.  If there are
			 * three transactions per microframe, DATA2 is used for
			 * the first transaction data packet, DATA1 is used for
			 * the second, and DATA0 is used for the third."
			 *
			 * IOW, we should satisfy the following cases:
			 *
			 * 1) length <= maxpacket
			 *	- DATA0
			 *
			 * 2) maxpacket < length <= (2 * maxpacket)
			 *	- DATA1, DATA0
			 *
			 * 3) (2 * maxpacket) < length <= (3 * maxpacket)
			 *	- DATA2, DATA1, DATA0
			 */
			if (speed == USB_SPEED_HIGH) {
				struct usb_ep *ep = &dep->endpoint;
				unsigned int mult = 2;
				unsigned int maxp = usb_endpoint_maxp(ep->desc);

				if (length <= (2 * maxp))
					mult--;

				if (length <= maxp)
					mult--;

				trb->size |= DWC3_TRB_SIZE_PCM1(mult);
			}
		} else {
			trb->ctrl = DWC3_TRBCTL_ISOCHRONOUS;
		}

		/* always enable Interrupt on Missed ISOC */
		trb->ctrl |= DWC3_TRB_CTRL_ISP_IMI;
		break;

	case USB_ENDPOINT_XFER_BULK:
	case USB_ENDPOINT_XFER_INT:
		trb->ctrl = DWC3_TRBCTL_NORMAL;
		break;
	default:
		/*
		 * This is only possible with faulty memory because we
		 * checked it already :)
		 */
		dev_WARN(dwc->dev, "Unknown endpoint type %d\n",
				usb_endpoint_type(dep->endpoint.desc));
	}

	/*
	 * Enable Continue on Short Packet
	 * when endpoint is not a stream capable
	 */
	if (usb_endpoint_dir_out(dep->endpoint.desc)) {
		if (!dep->stream_capable)
			trb->ctrl |= DWC3_TRB_CTRL_CSP;

		if (short_not_ok)
			trb->ctrl |= DWC3_TRB_CTRL_ISP_IMI;
	}

	if ((!no_interrupt && !chain) ||
			(dwc3_calc_trbs_left(dep) == 1))
		trb->ctrl |= DWC3_TRB_CTRL_IOC;

	if (chain)
		trb->ctrl |= DWC3_TRB_CTRL_CHN;

	if (usb_endpoint_xfer_bulk(dep->endpoint.desc) && dep->stream_capable)
		trb->ctrl |= DWC3_TRB_CTRL_SID_SOFN(stream_id);

	trb->ctrl |= DWC3_TRB_CTRL_HWO;

	dwc3_ep_inc_enq(dep);

	trace_dwc3_prepare_trb(dep, trb);
}