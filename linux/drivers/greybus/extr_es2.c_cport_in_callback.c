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
typedef  int u16 ;
struct urb {int actual_length; struct gb_operation_msg_hdr* transfer_buffer; TYPE_1__* dev; struct gb_host_device* context; } ;
struct gb_operation_msg_hdr {int dummy; } ;
struct gb_host_device {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOENT ; 
 int EPROTO ; 
 int ESHUTDOWN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int check_urb_status (struct urb*) ; 
 scalar_t__ cport_id_valid (struct gb_host_device*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int gb_message_cport_unpack (struct gb_operation_msg_hdr*) ; 
 int /*<<< orphan*/  greybus_data_rcvd (struct gb_host_device*,int,struct gb_operation_msg_hdr*,int) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cport_in_callback(struct urb *urb)
{
	struct gb_host_device *hd = urb->context;
	struct device *dev = &urb->dev->dev;
	struct gb_operation_msg_hdr *header;
	int status = check_urb_status(urb);
	int retval;
	u16 cport_id;

	if (status) {
		if ((status == -EAGAIN) || (status == -EPROTO))
			goto exit;

		/* The urb is being unlinked */
		if (status == -ENOENT || status == -ESHUTDOWN)
			return;

		dev_err(dev, "urb cport in error %d (dropped)\n", status);
		return;
	}

	if (urb->actual_length < sizeof(*header)) {
		dev_err(dev, "short message received\n");
		goto exit;
	}

	/* Extract the CPort id, which is packed in the message header */
	header = urb->transfer_buffer;
	cport_id = gb_message_cport_unpack(header);

	if (cport_id_valid(hd, cport_id)) {
		greybus_data_rcvd(hd, cport_id, urb->transfer_buffer,
				  urb->actual_length);
	} else {
		dev_err(dev, "invalid cport id %u received\n", cport_id);
	}
exit:
	/* put our urb back in the request pool */
	retval = usb_submit_urb(urb, GFP_ATOMIC);
	if (retval)
		dev_err(dev, "failed to resubmit in-urb: %d\n", retval);
}