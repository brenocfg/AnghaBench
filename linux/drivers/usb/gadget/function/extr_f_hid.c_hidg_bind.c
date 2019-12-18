#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_14__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct usb_string {int /*<<< orphan*/  id; } ;
struct usb_function {TYPE_2__* config; } ;
struct usb_ep {int dummy; } ;
struct usb_configuration {TYPE_3__* cdev; } ;
struct f_hidg {int write_pending; int /*<<< orphan*/ * req; struct usb_ep* in_ep; int /*<<< orphan*/  cdev; int /*<<< orphan*/  minor; int /*<<< orphan*/  completed_out_req; int /*<<< orphan*/  read_queue; int /*<<< orphan*/  write_queue; int /*<<< orphan*/  read_spinlock; int /*<<< orphan*/  write_spinlock; int /*<<< orphan*/  report_desc_length; int /*<<< orphan*/  report_length; int /*<<< orphan*/  protocol; int /*<<< orphan*/  bInterfaceProtocol; int /*<<< orphan*/  bInterfaceSubClass; struct usb_ep* out_ep; } ;
struct device {int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_26__ {int bInterfaceNumber; int /*<<< orphan*/  bInterfaceProtocol; int /*<<< orphan*/  bInterfaceSubClass; int /*<<< orphan*/  iInterface; } ;
struct TYPE_25__ {void* wBytesPerInterval; } ;
struct TYPE_24__ {int /*<<< orphan*/  bEndpointAddress; void* wMaxPacketSize; } ;
struct TYPE_23__ {void* wBytesPerInterval; } ;
struct TYPE_22__ {int /*<<< orphan*/  bEndpointAddress; void* wMaxPacketSize; } ;
struct TYPE_21__ {int /*<<< orphan*/  bEndpointAddress; void* wMaxPacketSize; } ;
struct TYPE_20__ {int /*<<< orphan*/  gadget; } ;
struct TYPE_19__ {int /*<<< orphan*/  cdev; } ;
struct TYPE_18__ {void* wDescriptorLength; int /*<<< orphan*/  bDescriptorType; } ;
struct TYPE_17__ {TYPE_1__* desc; } ;
struct TYPE_16__ {int /*<<< orphan*/  bEndpointAddress; void* wMaxPacketSize; } ;
struct TYPE_15__ {int /*<<< orphan*/  bEndpointAddress; void* wMaxPacketSize; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 size_t CT_FUNC_HID_IDX ; 
 int ENODEV ; 
 int /*<<< orphan*/  ERROR (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  HID_DT_REPORT ; 
 int /*<<< orphan*/  HID_REPORT_PROTOCOL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct usb_string*) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct usb_string*) ; 
 int cdev_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cdev_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ct_func_string_defs ; 
 int /*<<< orphan*/  ct_func_strings ; 
 struct usb_string* device_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f_hidg_fops ; 
 int /*<<< orphan*/  free_ep_req (struct usb_ep*,int /*<<< orphan*/ *) ; 
 struct f_hidg* func_to_hidg (struct usb_function*) ; 
 int /*<<< orphan*/  hidg_class ; 
 TYPE_14__ hidg_desc ; 
 int /*<<< orphan*/  hidg_fs_descriptors ; 
 TYPE_4__ hidg_fs_in_ep_desc ; 
 TYPE_4__ hidg_fs_out_ep_desc ; 
 int /*<<< orphan*/  hidg_hs_descriptors ; 
 TYPE_11__ hidg_hs_in_ep_desc ; 
 TYPE_10__ hidg_hs_out_ep_desc ; 
 TYPE_9__ hidg_interface_desc ; 
 int /*<<< orphan*/  hidg_ss_descriptors ; 
 TYPE_8__ hidg_ss_in_comp_desc ; 
 TYPE_7__ hidg_ss_in_ep_desc ; 
 TYPE_6__ hidg_ss_out_comp_desc ; 
 TYPE_5__ hidg_ss_out_ep_desc ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  major ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int usb_assign_descriptors (struct usb_function*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct usb_ep* usb_ep_autoconfig (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  usb_free_all_descriptors (struct usb_function*) ; 
 struct usb_string* usb_gstrings_attach (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_interface_id (struct usb_configuration*,struct usb_function*) ; 

__attribute__((used)) static int hidg_bind(struct usb_configuration *c, struct usb_function *f)
{
	struct usb_ep		*ep;
	struct f_hidg		*hidg = func_to_hidg(f);
	struct usb_string	*us;
	struct device		*device;
	int			status;
	dev_t			dev;

	/* maybe allocate device-global string IDs, and patch descriptors */
	us = usb_gstrings_attach(c->cdev, ct_func_strings,
				 ARRAY_SIZE(ct_func_string_defs));
	if (IS_ERR(us))
		return PTR_ERR(us);
	hidg_interface_desc.iInterface = us[CT_FUNC_HID_IDX].id;

	/* allocate instance-specific interface IDs, and patch descriptors */
	status = usb_interface_id(c, f);
	if (status < 0)
		goto fail;
	hidg_interface_desc.bInterfaceNumber = status;

	/* allocate instance-specific endpoints */
	status = -ENODEV;
	ep = usb_ep_autoconfig(c->cdev->gadget, &hidg_fs_in_ep_desc);
	if (!ep)
		goto fail;
	hidg->in_ep = ep;

	ep = usb_ep_autoconfig(c->cdev->gadget, &hidg_fs_out_ep_desc);
	if (!ep)
		goto fail;
	hidg->out_ep = ep;

	/* set descriptor dynamic values */
	hidg_interface_desc.bInterfaceSubClass = hidg->bInterfaceSubClass;
	hidg_interface_desc.bInterfaceProtocol = hidg->bInterfaceProtocol;
	hidg->protocol = HID_REPORT_PROTOCOL;
	hidg_ss_in_ep_desc.wMaxPacketSize = cpu_to_le16(hidg->report_length);
	hidg_ss_in_comp_desc.wBytesPerInterval =
				cpu_to_le16(hidg->report_length);
	hidg_hs_in_ep_desc.wMaxPacketSize = cpu_to_le16(hidg->report_length);
	hidg_fs_in_ep_desc.wMaxPacketSize = cpu_to_le16(hidg->report_length);
	hidg_ss_out_ep_desc.wMaxPacketSize = cpu_to_le16(hidg->report_length);
	hidg_ss_out_comp_desc.wBytesPerInterval =
				cpu_to_le16(hidg->report_length);
	hidg_hs_out_ep_desc.wMaxPacketSize = cpu_to_le16(hidg->report_length);
	hidg_fs_out_ep_desc.wMaxPacketSize = cpu_to_le16(hidg->report_length);
	/*
	 * We can use hidg_desc struct here but we should not relay
	 * that its content won't change after returning from this function.
	 */
	hidg_desc.desc[0].bDescriptorType = HID_DT_REPORT;
	hidg_desc.desc[0].wDescriptorLength =
		cpu_to_le16(hidg->report_desc_length);

	hidg_hs_in_ep_desc.bEndpointAddress =
		hidg_fs_in_ep_desc.bEndpointAddress;
	hidg_hs_out_ep_desc.bEndpointAddress =
		hidg_fs_out_ep_desc.bEndpointAddress;

	hidg_ss_in_ep_desc.bEndpointAddress =
		hidg_fs_in_ep_desc.bEndpointAddress;
	hidg_ss_out_ep_desc.bEndpointAddress =
		hidg_fs_out_ep_desc.bEndpointAddress;

	status = usb_assign_descriptors(f, hidg_fs_descriptors,
			hidg_hs_descriptors, hidg_ss_descriptors, NULL);
	if (status)
		goto fail;

	spin_lock_init(&hidg->write_spinlock);
	hidg->write_pending = 1;
	hidg->req = NULL;
	spin_lock_init(&hidg->read_spinlock);
	init_waitqueue_head(&hidg->write_queue);
	init_waitqueue_head(&hidg->read_queue);
	INIT_LIST_HEAD(&hidg->completed_out_req);

	/* create char device */
	cdev_init(&hidg->cdev, &f_hidg_fops);
	dev = MKDEV(major, hidg->minor);
	status = cdev_add(&hidg->cdev, dev, 1);
	if (status)
		goto fail_free_descs;

	device = device_create(hidg_class, NULL, dev, NULL,
			       "%s%d", "hidg", hidg->minor);
	if (IS_ERR(device)) {
		status = PTR_ERR(device);
		goto del;
	}

	return 0;
del:
	cdev_del(&hidg->cdev);
fail_free_descs:
	usb_free_all_descriptors(f);
fail:
	ERROR(f->config->cdev, "hidg_bind FAILED\n");
	if (hidg->req != NULL)
		free_ep_req(hidg->in_ep, hidg->req);

	return status;
}