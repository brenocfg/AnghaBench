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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/ * ops; } ;
struct net2272_ep {scalar_t__ num; TYPE_1__ ep; int /*<<< orphan*/  queue; int /*<<< orphan*/ * desc; } ;

/* Variables and functions */
 int ALT_NAK_OUT_PACKETS ; 
 int BUFFER_FLUSH ; 
 int DATA_IN_TOKEN_INTERRUPT ; 
 int DATA_OUT_TOKEN_INTERRUPT ; 
 int DATA_PACKET_RECEIVED_INTERRUPT ; 
 int DATA_PACKET_TRANSMITTED_INTERRUPT ; 
 int ENDPOINT_HALT ; 
 int ENDPOINT_TOGGLE ; 
 int /*<<< orphan*/  EP_IRQENB ; 
 int /*<<< orphan*/  EP_RSPCLR ; 
 int /*<<< orphan*/  EP_RSPSET ; 
 int /*<<< orphan*/  EP_STAT0 ; 
 int /*<<< orphan*/  EP_STAT1 ; 
 int HIDE_STATUS_PHASE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int INTERRUPT_MODE ; 
 int LOCAL_OUT_ZLP ; 
 int NAK_OUT_PACKETS_MODE ; 
 int SHORT_PACKET_TRANSFERRED_INTERRUPT ; 
 int TIMEOUT ; 
 int USB_IN_ACK_RCVD ; 
 int USB_IN_NAK_SENT ; 
 int USB_OUT_ACK_SENT ; 
 int USB_OUT_NAK_SENT ; 
 int USB_STALL_SENT ; 
 int /*<<< orphan*/  net2272_ep_ops ; 
 int /*<<< orphan*/  net2272_ep_write (struct net2272_ep*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_ep_set_maxpacket_limit (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void net2272_ep_reset(struct net2272_ep *ep)
{
	u8 tmp;

	ep->desc = NULL;
	INIT_LIST_HEAD(&ep->queue);

	usb_ep_set_maxpacket_limit(&ep->ep, ~0);
	ep->ep.ops = &net2272_ep_ops;

	/* disable irqs, endpoint */
	net2272_ep_write(ep, EP_IRQENB, 0);

	/* init to our chosen defaults, notably so that we NAK OUT
	 * packets until the driver queues a read.
	 */
	tmp = (1 << NAK_OUT_PACKETS_MODE) | (1 << ALT_NAK_OUT_PACKETS);
	net2272_ep_write(ep, EP_RSPSET, tmp);

	tmp = (1 << INTERRUPT_MODE) | (1 << HIDE_STATUS_PHASE);
	if (ep->num != 0)
		tmp |= (1 << ENDPOINT_TOGGLE) | (1 << ENDPOINT_HALT);

	net2272_ep_write(ep, EP_RSPCLR, tmp);

	/* scrub most status bits, and flush any fifo state */
	net2272_ep_write(ep, EP_STAT0,
			  (1 << DATA_IN_TOKEN_INTERRUPT)
			| (1 << DATA_OUT_TOKEN_INTERRUPT)
			| (1 << DATA_PACKET_TRANSMITTED_INTERRUPT)
			| (1 << DATA_PACKET_RECEIVED_INTERRUPT)
			| (1 << SHORT_PACKET_TRANSFERRED_INTERRUPT));

	net2272_ep_write(ep, EP_STAT1,
			    (1 << TIMEOUT)
			  | (1 << USB_OUT_ACK_SENT)
			  | (1 << USB_OUT_NAK_SENT)
			  | (1 << USB_IN_ACK_RCVD)
			  | (1 << USB_IN_NAK_SENT)
			  | (1 << USB_STALL_SENT)
			  | (1 << LOCAL_OUT_ZLP)
			  | (1 << BUFFER_FLUSH));

	/* fifo size is handled seperately */
}