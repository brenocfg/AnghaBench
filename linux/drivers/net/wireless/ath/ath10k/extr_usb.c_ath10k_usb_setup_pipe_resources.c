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
typedef  size_t u8 ;
struct usb_interface {struct usb_host_interface* cur_altsetting; } ;
struct TYPE_3__ {int bNumEndpoints; } ;
struct usb_host_interface {TYPE_2__* endpoint; TYPE_1__ desc; } ;
struct usb_endpoint_descriptor {int /*<<< orphan*/  bmAttributes; int /*<<< orphan*/  wMaxPacketSize; int /*<<< orphan*/  bEndpointAddress; int /*<<< orphan*/  bInterval; } ;
struct ath10k_usb_pipe {size_t logical_pipe_num; int /*<<< orphan*/  flags; int /*<<< orphan*/  ep_address; struct usb_endpoint_descriptor* ep_desc; int /*<<< orphan*/  usb_pipe_handle; int /*<<< orphan*/  max_packet_size; struct ath10k_usb* ar_usb; } ;
struct ath10k_usb {int /*<<< orphan*/  udev; struct ath10k_usb_pipe* pipes; } ;
struct ath10k {int dummy; } ;
struct TYPE_4__ {struct usb_endpoint_descriptor desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_USB ; 
 scalar_t__ ATH10K_USB_IS_BULK_EP (int /*<<< orphan*/ ) ; 
 scalar_t__ ATH10K_USB_IS_DIR_IN (int /*<<< orphan*/ ) ; 
 scalar_t__ ATH10K_USB_IS_INT_EP (int /*<<< orphan*/ ) ; 
 scalar_t__ ATH10K_USB_IS_ISOC_EP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATH10K_USB_PIPE_FLAG_TX ; 
 size_t ATH10K_USB_PIPE_INVALID ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,...) ; 
 int ath10k_usb_alloc_pipe_resources (struct ath10k*,struct ath10k_usb_pipe*,int) ; 
 size_t ath10k_usb_get_logical_pipe_num (int /*<<< orphan*/ ,int*) ; 
 struct ath10k_usb* ath10k_usb_priv (struct ath10k*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvintpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvisocpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndintpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndisocpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath10k_usb_setup_pipe_resources(struct ath10k *ar,
					   struct usb_interface *interface)
{
	struct ath10k_usb *ar_usb = ath10k_usb_priv(ar);
	struct usb_host_interface *iface_desc = interface->cur_altsetting;
	struct usb_endpoint_descriptor *endpoint;
	struct ath10k_usb_pipe *pipe;
	int ret, i, urbcount;
	u8 pipe_num;

	ath10k_dbg(ar, ATH10K_DBG_USB, "usb setting up pipes using interface\n");

	/* walk decriptors and setup pipes */
	for (i = 0; i < iface_desc->desc.bNumEndpoints; ++i) {
		endpoint = &iface_desc->endpoint[i].desc;

		if (ATH10K_USB_IS_BULK_EP(endpoint->bmAttributes)) {
			ath10k_dbg(ar, ATH10K_DBG_USB,
				   "usb %s bulk ep 0x%2.2x maxpktsz %d\n",
				   ATH10K_USB_IS_DIR_IN
				   (endpoint->bEndpointAddress) ?
				   "rx" : "tx", endpoint->bEndpointAddress,
				   le16_to_cpu(endpoint->wMaxPacketSize));
		} else if (ATH10K_USB_IS_INT_EP(endpoint->bmAttributes)) {
			ath10k_dbg(ar, ATH10K_DBG_USB,
				   "usb %s int ep 0x%2.2x maxpktsz %d interval %d\n",
				   ATH10K_USB_IS_DIR_IN
				   (endpoint->bEndpointAddress) ?
				   "rx" : "tx", endpoint->bEndpointAddress,
				   le16_to_cpu(endpoint->wMaxPacketSize),
				   endpoint->bInterval);
		} else if (ATH10K_USB_IS_ISOC_EP(endpoint->bmAttributes)) {
			/* TODO for ISO */
			ath10k_dbg(ar, ATH10K_DBG_USB,
				   "usb %s isoc ep 0x%2.2x maxpktsz %d interval %d\n",
				   ATH10K_USB_IS_DIR_IN
				   (endpoint->bEndpointAddress) ?
				   "rx" : "tx", endpoint->bEndpointAddress,
				   le16_to_cpu(endpoint->wMaxPacketSize),
				   endpoint->bInterval);
		}
		urbcount = 0;

		pipe_num =
		    ath10k_usb_get_logical_pipe_num(endpoint->bEndpointAddress,
						    &urbcount);
		if (pipe_num == ATH10K_USB_PIPE_INVALID)
			continue;

		pipe = &ar_usb->pipes[pipe_num];
		if (pipe->ar_usb)
			/* hmmm..pipe was already setup */
			continue;

		pipe->ar_usb = ar_usb;
		pipe->logical_pipe_num = pipe_num;
		pipe->ep_address = endpoint->bEndpointAddress;
		pipe->max_packet_size = le16_to_cpu(endpoint->wMaxPacketSize);

		if (ATH10K_USB_IS_BULK_EP(endpoint->bmAttributes)) {
			if (ATH10K_USB_IS_DIR_IN(pipe->ep_address)) {
				pipe->usb_pipe_handle =
				    usb_rcvbulkpipe(ar_usb->udev,
						    pipe->ep_address);
			} else {
				pipe->usb_pipe_handle =
				    usb_sndbulkpipe(ar_usb->udev,
						    pipe->ep_address);
			}
		} else if (ATH10K_USB_IS_INT_EP(endpoint->bmAttributes)) {
			if (ATH10K_USB_IS_DIR_IN(pipe->ep_address)) {
				pipe->usb_pipe_handle =
				    usb_rcvintpipe(ar_usb->udev,
						   pipe->ep_address);
			} else {
				pipe->usb_pipe_handle =
				    usb_sndintpipe(ar_usb->udev,
						   pipe->ep_address);
			}
		} else if (ATH10K_USB_IS_ISOC_EP(endpoint->bmAttributes)) {
			/* TODO for ISO */
			if (ATH10K_USB_IS_DIR_IN(pipe->ep_address)) {
				pipe->usb_pipe_handle =
				    usb_rcvisocpipe(ar_usb->udev,
						    pipe->ep_address);
			} else {
				pipe->usb_pipe_handle =
				    usb_sndisocpipe(ar_usb->udev,
						    pipe->ep_address);
			}
		}

		pipe->ep_desc = endpoint;

		if (!ATH10K_USB_IS_DIR_IN(pipe->ep_address))
			pipe->flags |= ATH10K_USB_PIPE_FLAG_TX;

		ret = ath10k_usb_alloc_pipe_resources(ar, pipe, urbcount);
		if (ret)
			return ret;
	}

	return 0;
}