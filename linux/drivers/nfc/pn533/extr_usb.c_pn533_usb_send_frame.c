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
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct pn533_usb_phy {TYPE_1__* out_urb; struct pn533* priv; } ;
struct pn533 {scalar_t__ protocol_type; struct pn533_usb_phy* phy; } ;
struct TYPE_3__ {int /*<<< orphan*/  transfer_buffer_length; int /*<<< orphan*/  transfer_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_NONE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ PN533_PROTO_REQ_ACK_RESP ; 
 scalar_t__ PN533_PROTO_REQ_RESP ; 
 int pn533_submit_urb_for_ack (struct pn533_usb_phy*,int /*<<< orphan*/ ) ; 
 int pn533_submit_urb_for_response (struct pn533_usb_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_hex_dump_debug (char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int usb_submit_urb (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unlink_urb (TYPE_1__*) ; 

__attribute__((used)) static int pn533_usb_send_frame(struct pn533 *dev,
				struct sk_buff *out)
{
	struct pn533_usb_phy *phy = dev->phy;
	int rc;

	if (phy->priv == NULL)
		phy->priv = dev;

	phy->out_urb->transfer_buffer = out->data;
	phy->out_urb->transfer_buffer_length = out->len;

	print_hex_dump_debug("PN533 TX: ", DUMP_PREFIX_NONE, 16, 1,
			     out->data, out->len, false);

	rc = usb_submit_urb(phy->out_urb, GFP_KERNEL);
	if (rc)
		return rc;

	if (dev->protocol_type == PN533_PROTO_REQ_RESP) {
		/* request for response for sent packet directly */
		rc = pn533_submit_urb_for_response(phy, GFP_KERNEL);
		if (rc)
			goto error;
	} else if (dev->protocol_type == PN533_PROTO_REQ_ACK_RESP) {
		/* request for ACK if that's the case */
		rc = pn533_submit_urb_for_ack(phy, GFP_KERNEL);
		if (rc)
			goto error;
	}

	return 0;

error:
	usb_unlink_urb(phy->out_urb);
	return rc;
}