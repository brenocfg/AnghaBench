#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int /*<<< orphan*/  dev; int /*<<< orphan*/  cur_altsetting; } ;
struct usb_endpoint_descriptor {int /*<<< orphan*/  bEndpointAddress; } ;
struct usb_device_id {int dummy; } ;
struct usb_device {int dummy; } ;
struct pxrc {TYPE_1__* input; int /*<<< orphan*/  phys; int /*<<< orphan*/  urb; struct usb_interface* intf; int /*<<< orphan*/  pm_mutex; } ;
struct TYPE_6__ {char* name; int /*<<< orphan*/  close; int /*<<< orphan*/  open; int /*<<< orphan*/  id; int /*<<< orphan*/  phys; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MISC ; 
 int /*<<< orphan*/  ABS_RUDDER ; 
 int /*<<< orphan*/  ABS_RX ; 
 int /*<<< orphan*/  ABS_RY ; 
 int /*<<< orphan*/  ABS_THROTTLE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_A ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int devm_add_action_or_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct pxrc*) ; 
 TYPE_1__* devm_input_allocate_device (int /*<<< orphan*/ *) ; 
 void* devm_kmalloc (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 struct pxrc* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int input_register_device (TYPE_1__*) ; 
 int /*<<< orphan*/  input_set_abs_params (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_capability (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (TYPE_1__*,struct pxrc*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pxrc_close ; 
 int /*<<< orphan*/  pxrc_free_urb ; 
 int /*<<< orphan*/  pxrc_open ; 
 int /*<<< orphan*/  pxrc_usb_irq ; 
 int /*<<< orphan*/  strlcat (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t usb_endpoint_maxp (struct usb_endpoint_descriptor*) ; 
 int /*<<< orphan*/  usb_fill_int_urb (int /*<<< orphan*/ ,struct usb_device*,int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ,struct pxrc*,int) ; 
 int usb_find_common_endpoints (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct usb_endpoint_descriptor**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_make_path (struct usb_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_rcvintpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct pxrc*) ; 
 int /*<<< orphan*/  usb_to_input_id (struct usb_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pxrc_probe(struct usb_interface *intf,
		      const struct usb_device_id *id)
{
	struct usb_device *udev = interface_to_usbdev(intf);
	struct pxrc *pxrc;
	struct usb_endpoint_descriptor *epirq;
	size_t xfer_size;
	void *xfer_buf;
	int error;

	/*
	 * Locate the endpoint information. This device only has an
	 * interrupt endpoint.
	 */
	error = usb_find_common_endpoints(intf->cur_altsetting,
					  NULL, NULL, &epirq, NULL);
	if (error) {
		dev_err(&intf->dev, "Could not find endpoint\n");
		return error;
	}

	pxrc = devm_kzalloc(&intf->dev, sizeof(*pxrc), GFP_KERNEL);
	if (!pxrc)
		return -ENOMEM;

	mutex_init(&pxrc->pm_mutex);
	pxrc->intf = intf;

	usb_set_intfdata(pxrc->intf, pxrc);

	xfer_size = usb_endpoint_maxp(epirq);
	xfer_buf = devm_kmalloc(&intf->dev, xfer_size, GFP_KERNEL);
	if (!xfer_buf)
		return -ENOMEM;

	pxrc->urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!pxrc->urb)
		return -ENOMEM;

	error = devm_add_action_or_reset(&intf->dev, pxrc_free_urb, pxrc);
	if (error)
		return error;

	usb_fill_int_urb(pxrc->urb, udev,
			 usb_rcvintpipe(udev, epirq->bEndpointAddress),
			 xfer_buf, xfer_size, pxrc_usb_irq, pxrc, 1);

	pxrc->input = devm_input_allocate_device(&intf->dev);
	if (!pxrc->input) {
		dev_err(&intf->dev, "couldn't allocate input device\n");
		return -ENOMEM;
	}

	pxrc->input->name = "PXRC Flight Controller Adapter";

	usb_make_path(udev, pxrc->phys, sizeof(pxrc->phys));
	strlcat(pxrc->phys, "/input0", sizeof(pxrc->phys));
	pxrc->input->phys = pxrc->phys;

	usb_to_input_id(udev, &pxrc->input->id);

	pxrc->input->open = pxrc_open;
	pxrc->input->close = pxrc_close;

	input_set_capability(pxrc->input, EV_KEY, BTN_A);
	input_set_abs_params(pxrc->input, ABS_X, 0, 255, 0, 0);
	input_set_abs_params(pxrc->input, ABS_Y, 0, 255, 0, 0);
	input_set_abs_params(pxrc->input, ABS_RX, 0, 255, 0, 0);
	input_set_abs_params(pxrc->input, ABS_RY, 0, 255, 0, 0);
	input_set_abs_params(pxrc->input, ABS_RUDDER, 0, 255, 0, 0);
	input_set_abs_params(pxrc->input, ABS_THROTTLE, 0, 255, 0, 0);
	input_set_abs_params(pxrc->input, ABS_MISC, 0, 255, 0, 0);

	input_set_drvdata(pxrc->input, pxrc);

	error = input_register_device(pxrc->input);
	if (error)
		return error;

	return 0;
}