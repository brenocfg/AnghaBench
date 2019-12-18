#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct usb_interface {int /*<<< orphan*/  dev; struct usb_host_interface* cur_altsetting; } ;
struct TYPE_8__ {int bNumEndpoints; } ;
struct usb_host_interface {TYPE_2__* endpoint; TYPE_1__ desc; } ;
struct usb_endpoint_descriptor {int bEndpointAddress; } ;
struct usb_device_id {int driver_info; } ;
struct pn533_usb_phy {unsigned char* ack_buffer; TYPE_3__* udev; void* ack_urb; void* out_urb; void* in_urb; struct pn533* priv; struct usb_interface* interface; } ;
struct pn533_frame_ops {int dummy; } ;
struct pn533 {int dummy; } ;
typedef  enum pn533_protocol_type { ____Placeholder_pn533_protocol_type } pn533_protocol_type ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {struct usb_endpoint_descriptor desc; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct pn533*) ; 
 int /*<<< orphan*/  PN533_ALL_PROTOCOLS ; 
#define  PN533_DEVICE_ACR122U 130 
#define  PN533_DEVICE_PASORI 129 
#define  PN533_DEVICE_STD 128 
 int PN533_EXT_FRAME_HEADER_LEN ; 
 int /*<<< orphan*/  PN533_NO_TYPE_B_PROTOCOLS ; 
 int PN533_PROTO_REQ_ACK_RESP ; 
 int PN533_PROTO_REQ_RESP ; 
 int PN533_STD_FRAME_MAX_PAYLOAD_LEN ; 
 int PN533_STD_FRAME_TAIL_LEN ; 
 int PTR_ERR (struct pn533*) ; 
 struct pn533_usb_phy* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_err (int /*<<< orphan*/ *,char*,...) ; 
 struct pn533_frame_ops pn533_acr122_frame_ops ; 
 int pn533_acr122_poweron_rdr (struct pn533_usb_phy*) ; 
 int pn533_finalize_setup (struct pn533*) ; 
 struct pn533* pn533_register_device (int,int /*<<< orphan*/ ,int,struct pn533_usb_phy*,int /*<<< orphan*/ *,struct pn533_frame_ops*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pn533_send_complete ; 
 int /*<<< orphan*/  pn533_unregister_device (struct pn533*) ; 
 void* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_endpoint_is_bulk_in (struct usb_endpoint_descriptor*) ; 
 scalar_t__ usb_endpoint_is_bulk_out (struct usb_endpoint_descriptor*) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (void*,TYPE_3__*,int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ *,struct pn533_usb_phy*) ; 
 int /*<<< orphan*/  usb_free_urb (void*) ; 
 TYPE_3__* usb_get_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_kill_urb (void*) ; 
 int /*<<< orphan*/  usb_phy_ops ; 
 int /*<<< orphan*/  usb_put_dev (TYPE_3__*) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (TYPE_3__*,int) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct pn533_usb_phy*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (TYPE_3__*,int) ; 

__attribute__((used)) static int pn533_usb_probe(struct usb_interface *interface,
			const struct usb_device_id *id)
{
	struct pn533 *priv;
	struct pn533_usb_phy *phy;
	struct usb_host_interface *iface_desc;
	struct usb_endpoint_descriptor *endpoint;
	int in_endpoint = 0;
	int out_endpoint = 0;
	int rc = -ENOMEM;
	int i;
	u32 protocols;
	enum pn533_protocol_type protocol_type = PN533_PROTO_REQ_ACK_RESP;
	struct pn533_frame_ops *fops = NULL;
	unsigned char *in_buf;
	int in_buf_len = PN533_EXT_FRAME_HEADER_LEN +
			 PN533_STD_FRAME_MAX_PAYLOAD_LEN +
			 PN533_STD_FRAME_TAIL_LEN;

	phy = devm_kzalloc(&interface->dev, sizeof(*phy), GFP_KERNEL);
	if (!phy)
		return -ENOMEM;

	in_buf = kzalloc(in_buf_len, GFP_KERNEL);
	if (!in_buf)
		return -ENOMEM;

	phy->udev = usb_get_dev(interface_to_usbdev(interface));
	phy->interface = interface;

	iface_desc = interface->cur_altsetting;
	for (i = 0; i < iface_desc->desc.bNumEndpoints; ++i) {
		endpoint = &iface_desc->endpoint[i].desc;

		if (!in_endpoint && usb_endpoint_is_bulk_in(endpoint))
			in_endpoint = endpoint->bEndpointAddress;

		if (!out_endpoint && usb_endpoint_is_bulk_out(endpoint))
			out_endpoint = endpoint->bEndpointAddress;
	}

	if (!in_endpoint || !out_endpoint) {
		nfc_err(&interface->dev,
			"Could not find bulk-in or bulk-out endpoint\n");
		rc = -ENODEV;
		goto error;
	}

	phy->in_urb = usb_alloc_urb(0, GFP_KERNEL);
	phy->out_urb = usb_alloc_urb(0, GFP_KERNEL);
	phy->ack_urb = usb_alloc_urb(0, GFP_KERNEL);

	if (!phy->in_urb || !phy->out_urb || !phy->ack_urb)
		goto error;

	usb_fill_bulk_urb(phy->in_urb, phy->udev,
			  usb_rcvbulkpipe(phy->udev, in_endpoint),
			  in_buf, in_buf_len, NULL, phy);

	usb_fill_bulk_urb(phy->out_urb, phy->udev,
			  usb_sndbulkpipe(phy->udev, out_endpoint),
			  NULL, 0, pn533_send_complete, phy);
	usb_fill_bulk_urb(phy->ack_urb, phy->udev,
			  usb_sndbulkpipe(phy->udev, out_endpoint),
			  NULL, 0, pn533_send_complete, phy);

	switch (id->driver_info) {
	case PN533_DEVICE_STD:
		protocols = PN533_ALL_PROTOCOLS;
		break;

	case PN533_DEVICE_PASORI:
		protocols = PN533_NO_TYPE_B_PROTOCOLS;
		break;

	case PN533_DEVICE_ACR122U:
		protocols = PN533_NO_TYPE_B_PROTOCOLS;
		fops = &pn533_acr122_frame_ops;
		protocol_type = PN533_PROTO_REQ_RESP,

		rc = pn533_acr122_poweron_rdr(phy);
		if (rc < 0) {
			nfc_err(&interface->dev,
				"Couldn't poweron the reader (error %d)\n", rc);
			goto error;
		}
		break;

	default:
		nfc_err(&interface->dev, "Unknown device type %lu\n",
			id->driver_info);
		rc = -EINVAL;
		goto error;
	}

	priv = pn533_register_device(id->driver_info, protocols, protocol_type,
					phy, &usb_phy_ops, fops,
					&phy->udev->dev, &interface->dev);

	if (IS_ERR(priv)) {
		rc = PTR_ERR(priv);
		goto error;
	}

	phy->priv = priv;

	rc = pn533_finalize_setup(priv);
	if (rc)
		goto err_deregister;

	usb_set_intfdata(interface, phy);

	return 0;

err_deregister:
	pn533_unregister_device(phy->priv);
error:
	usb_kill_urb(phy->in_urb);
	usb_kill_urb(phy->out_urb);
	usb_kill_urb(phy->ack_urb);

	usb_free_urb(phy->in_urb);
	usb_free_urb(phy->out_urb);
	usb_free_urb(phy->ack_urb);
	usb_put_dev(phy->udev);
	kfree(in_buf);
	kfree(phy->ack_buffer);

	return rc;
}