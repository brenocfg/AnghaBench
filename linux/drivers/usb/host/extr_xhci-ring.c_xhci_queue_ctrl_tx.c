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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct xhci_td {TYPE_1__* last_trb; } ;
struct xhci_ring {int cycle_state; TYPE_1__* enqueue; } ;
struct xhci_hcd {int hci_version; int quirks; int /*<<< orphan*/ * devs; } ;
struct xhci_generic_trb {int dummy; } ;
struct usb_ctrlrequest {int bRequestType; int bRequest; int /*<<< orphan*/  wLength; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; } ;
struct urb_priv {struct xhci_td* td; } ;
struct urb {int transfer_buffer_length; scalar_t__ transfer_dma; int /*<<< orphan*/  transfer_buffer; scalar_t__ setup_packet; struct urb_priv* hcpriv; int /*<<< orphan*/  stream_id; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {struct xhci_generic_trb generic; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TRB_DATA ; 
 int /*<<< orphan*/  TRB_DATA_IN ; 
 int /*<<< orphan*/  TRB_DATA_OUT ; 
 int TRB_DIR_IN ; 
 int TRB_IDT ; 
 int TRB_INTR_TARGET (int /*<<< orphan*/ ) ; 
 int TRB_IOC ; 
 int TRB_ISP ; 
 int TRB_LEN (int) ; 
 int /*<<< orphan*/  TRB_SETUP ; 
 int /*<<< orphan*/  TRB_STATUS ; 
 int TRB_TD_SIZE (int) ; 
 int TRB_TX_TYPE (int /*<<< orphan*/ ) ; 
 int TRB_TYPE (int /*<<< orphan*/ ) ; 
 int USB_DIR_IN ; 
 int XHCI_MTK_HOST ; 
 int /*<<< orphan*/  giveback_first_trb (struct xhci_hcd*,int,unsigned int,int /*<<< orphan*/ ,int,struct xhci_generic_trb*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpus (scalar_t__*) ; 
 int lower_32_bits (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int prepare_transfer (struct xhci_hcd*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int,struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_trb (struct xhci_hcd*,struct xhci_ring*,int,int,int,int,int) ; 
 int upper_32_bits (scalar_t__) ; 
 scalar_t__ usb_urb_dir_in (struct urb*) ; 
 int xhci_td_remainder (struct xhci_hcd*,int /*<<< orphan*/ ,int,int,struct urb*,int) ; 
 scalar_t__ xhci_urb_suitable_for_idt (struct urb*) ; 
 struct xhci_ring* xhci_urb_to_transfer_ring (struct xhci_hcd*,struct urb*) ; 

int xhci_queue_ctrl_tx(struct xhci_hcd *xhci, gfp_t mem_flags,
		struct urb *urb, int slot_id, unsigned int ep_index)
{
	struct xhci_ring *ep_ring;
	int num_trbs;
	int ret;
	struct usb_ctrlrequest *setup;
	struct xhci_generic_trb *start_trb;
	int start_cycle;
	u32 field;
	struct urb_priv *urb_priv;
	struct xhci_td *td;

	ep_ring = xhci_urb_to_transfer_ring(xhci, urb);
	if (!ep_ring)
		return -EINVAL;

	/*
	 * Need to copy setup packet into setup TRB, so we can't use the setup
	 * DMA address.
	 */
	if (!urb->setup_packet)
		return -EINVAL;

	/* 1 TRB for setup, 1 for status */
	num_trbs = 2;
	/*
	 * Don't need to check if we need additional event data and normal TRBs,
	 * since data in control transfers will never get bigger than 16MB
	 * XXX: can we get a buffer that crosses 64KB boundaries?
	 */
	if (urb->transfer_buffer_length > 0)
		num_trbs++;
	ret = prepare_transfer(xhci, xhci->devs[slot_id],
			ep_index, urb->stream_id,
			num_trbs, urb, 0, mem_flags);
	if (ret < 0)
		return ret;

	urb_priv = urb->hcpriv;
	td = &urb_priv->td[0];

	/*
	 * Don't give the first TRB to the hardware (by toggling the cycle bit)
	 * until we've finished creating all the other TRBs.  The ring's cycle
	 * state may change as we enqueue the other TRBs, so save it too.
	 */
	start_trb = &ep_ring->enqueue->generic;
	start_cycle = ep_ring->cycle_state;

	/* Queue setup TRB - see section 6.4.1.2.1 */
	/* FIXME better way to translate setup_packet into two u32 fields? */
	setup = (struct usb_ctrlrequest *) urb->setup_packet;
	field = 0;
	field |= TRB_IDT | TRB_TYPE(TRB_SETUP);
	if (start_cycle == 0)
		field |= 0x1;

	/* xHCI 1.0/1.1 6.4.1.2.1: Transfer Type field */
	if ((xhci->hci_version >= 0x100) || (xhci->quirks & XHCI_MTK_HOST)) {
		if (urb->transfer_buffer_length > 0) {
			if (setup->bRequestType & USB_DIR_IN)
				field |= TRB_TX_TYPE(TRB_DATA_IN);
			else
				field |= TRB_TX_TYPE(TRB_DATA_OUT);
		}
	}

	queue_trb(xhci, ep_ring, true,
		  setup->bRequestType | setup->bRequest << 8 | le16_to_cpu(setup->wValue) << 16,
		  le16_to_cpu(setup->wIndex) | le16_to_cpu(setup->wLength) << 16,
		  TRB_LEN(8) | TRB_INTR_TARGET(0),
		  /* Immediate data in pointer */
		  field);

	/* If there's data, queue data TRBs */
	/* Only set interrupt on short packet for IN endpoints */
	if (usb_urb_dir_in(urb))
		field = TRB_ISP | TRB_TYPE(TRB_DATA);
	else
		field = TRB_TYPE(TRB_DATA);

	if (urb->transfer_buffer_length > 0) {
		u32 length_field, remainder;
		u64 addr;

		if (xhci_urb_suitable_for_idt(urb)) {
			memcpy(&addr, urb->transfer_buffer,
			       urb->transfer_buffer_length);
			le64_to_cpus(&addr);
			field |= TRB_IDT;
		} else {
			addr = (u64) urb->transfer_dma;
		}

		remainder = xhci_td_remainder(xhci, 0,
				urb->transfer_buffer_length,
				urb->transfer_buffer_length,
				urb, 1);
		length_field = TRB_LEN(urb->transfer_buffer_length) |
				TRB_TD_SIZE(remainder) |
				TRB_INTR_TARGET(0);
		if (setup->bRequestType & USB_DIR_IN)
			field |= TRB_DIR_IN;
		queue_trb(xhci, ep_ring, true,
				lower_32_bits(addr),
				upper_32_bits(addr),
				length_field,
				field | ep_ring->cycle_state);
	}

	/* Save the DMA address of the last TRB in the TD */
	td->last_trb = ep_ring->enqueue;

	/* Queue status TRB - see Table 7 and sections 4.11.2.2 and 6.4.1.2.3 */
	/* If the device sent data, the status stage is an OUT transfer */
	if (urb->transfer_buffer_length > 0 && setup->bRequestType & USB_DIR_IN)
		field = 0;
	else
		field = TRB_DIR_IN;
	queue_trb(xhci, ep_ring, false,
			0,
			0,
			TRB_INTR_TARGET(0),
			/* Event on completion */
			field | TRB_IOC | TRB_TYPE(TRB_STATUS) | ep_ring->cycle_state);

	giveback_first_trb(xhci, slot_id, ep_index, 0,
			start_cycle, start_trb);
	return 0;
}