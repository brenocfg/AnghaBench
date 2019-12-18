#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int /*<<< orphan*/  dev; struct usb_host_interface* altsetting; } ;
struct TYPE_10__ {int bNumEndpoints; } ;
struct usb_host_interface {TYPE_2__* endpoint; TYPE_1__ desc; } ;
struct usb_device_id {int dummy; } ;
struct usb_device {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/ * parent; } ;
struct rc_dev {int min_timeout; int timeout; int max_timeout; int /*<<< orphan*/  rx_resolution; int /*<<< orphan*/  map_name; int /*<<< orphan*/  driver_name; int /*<<< orphan*/  tx_ir; int /*<<< orphan*/  (* s_tx_carrier ) (struct rc_dev*,int) ;int /*<<< orphan*/  (* s_tx_mask ) (struct rc_dev*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  close; int /*<<< orphan*/  open; struct iguanair* priv; int /*<<< orphan*/  allowed_protocols; TYPE_3__ dev; int /*<<< orphan*/  input_id; int /*<<< orphan*/  input_phys; int /*<<< orphan*/  device_name; } ;
struct iguanair {int version; int /*<<< orphan*/  dma_out; void* packet; int /*<<< orphan*/  dma_in; void* buf_in; TYPE_4__* urb_out; TYPE_4__* urb_in; struct usb_device* udev; int /*<<< orphan*/  phys; int /*<<< orphan*/  name; int /*<<< orphan*/  completion; int /*<<< orphan*/  lock; int /*<<< orphan*/ * dev; struct rc_dev* rc; } ;
struct TYPE_14__ {int /*<<< orphan*/  bEndpointAddress; } ;
struct TYPE_13__ {int /*<<< orphan*/  transfer_flags; int /*<<< orphan*/  transfer_dma; } ;
struct TYPE_11__ {TYPE_8__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IR_DEFAULT_TIMEOUT ; 
 int /*<<< orphan*/  MAX_IN_PACKET ; 
 int /*<<< orphan*/  MAX_OUT_PACKET ; 
 int /*<<< orphan*/  RC_DRIVER_IR_RAW ; 
 int /*<<< orphan*/  RC_MAP_RC6_MCE ; 
 int /*<<< orphan*/  RC_PROTO_BIT_ALL_IR_DECODER ; 
 int /*<<< orphan*/  RX_RESOLUTION ; 
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  iguanair_close ; 
 int iguanair_get_features (struct iguanair*) ; 
 int /*<<< orphan*/  iguanair_irq_out ; 
 int /*<<< orphan*/  iguanair_open ; 
 int /*<<< orphan*/  iguanair_rx ; 
 int /*<<< orphan*/  iguanair_set_tx_carrier (struct rc_dev*,int) ; 
 int /*<<< orphan*/  iguanair_set_tx_mask (struct rc_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iguanair_tx ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct iguanair*) ; 
 struct iguanair* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct rc_dev* rc_allocate_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_free_device (struct rc_dev*) ; 
 int rc_register_device (struct rc_dev*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 void* usb_alloc_coherent (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_endpoint_is_int_in (TYPE_8__*) ; 
 int /*<<< orphan*/  usb_endpoint_is_int_out (TYPE_8__*) ; 
 int /*<<< orphan*/  usb_fill_int_urb (TYPE_4__*,struct usb_device*,int,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iguanair*,int) ; 
 int /*<<< orphan*/  usb_free_coherent (struct usb_device*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (TYPE_4__*) ; 
 int /*<<< orphan*/  usb_kill_urb (TYPE_4__*) ; 
 int /*<<< orphan*/  usb_make_path (struct usb_device*,int /*<<< orphan*/ ,int) ; 
 int usb_rcvintpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct iguanair*) ; 
 int usb_sndintpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_to_input_id (struct usb_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iguanair_probe(struct usb_interface *intf,
			  const struct usb_device_id *id)
{
	struct usb_device *udev = interface_to_usbdev(intf);
	struct iguanair *ir;
	struct rc_dev *rc;
	int ret, pipein, pipeout;
	struct usb_host_interface *idesc;

	idesc = intf->altsetting;
	if (idesc->desc.bNumEndpoints < 2)
		return -ENODEV;

	ir = kzalloc(sizeof(*ir), GFP_KERNEL);
	rc = rc_allocate_device(RC_DRIVER_IR_RAW);
	if (!ir || !rc) {
		ret = -ENOMEM;
		goto out;
	}

	ir->buf_in = usb_alloc_coherent(udev, MAX_IN_PACKET, GFP_KERNEL,
								&ir->dma_in);
	ir->packet = usb_alloc_coherent(udev, MAX_OUT_PACKET, GFP_KERNEL,
								&ir->dma_out);
	ir->urb_in = usb_alloc_urb(0, GFP_KERNEL);
	ir->urb_out = usb_alloc_urb(0, GFP_KERNEL);

	if (!ir->buf_in || !ir->packet || !ir->urb_in || !ir->urb_out ||
	    !usb_endpoint_is_int_in(&idesc->endpoint[0].desc) ||
	    !usb_endpoint_is_int_out(&idesc->endpoint[1].desc)) {
		ret = -ENOMEM;
		goto out;
	}

	ir->rc = rc;
	ir->dev = &intf->dev;
	ir->udev = udev;
	mutex_init(&ir->lock);

	init_completion(&ir->completion);
	pipeout = usb_sndintpipe(udev,
				idesc->endpoint[1].desc.bEndpointAddress);
	usb_fill_int_urb(ir->urb_out, udev, pipeout, ir->packet, MAX_OUT_PACKET,
						iguanair_irq_out, ir, 1);
	ir->urb_out->transfer_dma = ir->dma_out;
	ir->urb_out->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	pipein = usb_rcvintpipe(udev, idesc->endpoint[0].desc.bEndpointAddress);
	usb_fill_int_urb(ir->urb_in, udev, pipein, ir->buf_in, MAX_IN_PACKET,
							 iguanair_rx, ir, 1);
	ir->urb_in->transfer_dma = ir->dma_in;
	ir->urb_in->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	ret = usb_submit_urb(ir->urb_in, GFP_KERNEL);
	if (ret) {
		dev_warn(&intf->dev, "failed to submit urb: %d\n", ret);
		goto out;
	}

	ret = iguanair_get_features(ir);
	if (ret)
		goto out2;

	snprintf(ir->name, sizeof(ir->name),
		"IguanaWorks USB IR Transceiver version 0x%04x", ir->version);

	usb_make_path(ir->udev, ir->phys, sizeof(ir->phys));

	rc->device_name = ir->name;
	rc->input_phys = ir->phys;
	usb_to_input_id(ir->udev, &rc->input_id);
	rc->dev.parent = &intf->dev;
	rc->allowed_protocols = RC_PROTO_BIT_ALL_IR_DECODER;
	rc->priv = ir;
	rc->open = iguanair_open;
	rc->close = iguanair_close;
	rc->s_tx_mask = iguanair_set_tx_mask;
	rc->s_tx_carrier = iguanair_set_tx_carrier;
	rc->tx_ir = iguanair_tx;
	rc->driver_name = DRIVER_NAME;
	rc->map_name = RC_MAP_RC6_MCE;
	rc->min_timeout = 1;
	rc->timeout = IR_DEFAULT_TIMEOUT;
	rc->max_timeout = 10 * IR_DEFAULT_TIMEOUT;
	rc->rx_resolution = RX_RESOLUTION;

	iguanair_set_tx_carrier(rc, 38000);
	iguanair_set_tx_mask(rc, 0);

	ret = rc_register_device(rc);
	if (ret < 0) {
		dev_err(&intf->dev, "failed to register rc device %d", ret);
		goto out2;
	}

	usb_set_intfdata(intf, ir);

	return 0;
out2:
	usb_kill_urb(ir->urb_in);
	usb_kill_urb(ir->urb_out);
out:
	if (ir) {
		usb_free_urb(ir->urb_in);
		usb_free_urb(ir->urb_out);
		usb_free_coherent(udev, MAX_IN_PACKET, ir->buf_in, ir->dma_in);
		usb_free_coherent(udev, MAX_OUT_PACKET, ir->packet,
								ir->dma_out);
	}
	rc_free_device(rc);
	kfree(ir);
	return ret;
}