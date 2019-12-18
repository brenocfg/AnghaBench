#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_role_switch_desc {int /*<<< orphan*/  fwnode; int /*<<< orphan*/  get; scalar_t__ set; int /*<<< orphan*/  udc; int /*<<< orphan*/  usb3_port; int /*<<< orphan*/  usb2_port; int /*<<< orphan*/  allow_userspace_control; } ;
struct TYPE_4__ {int /*<<< orphan*/ * type; int /*<<< orphan*/  class; int /*<<< orphan*/  fwnode; struct device* parent; } ;
struct usb_role_switch {TYPE_1__ dev; int /*<<< orphan*/  get; scalar_t__ set; int /*<<< orphan*/  udc; int /*<<< orphan*/  usb3_port; int /*<<< orphan*/  usb2_port; int /*<<< orphan*/  allow_userspace_control; int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct usb_role_switch* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int device_register (TYPE_1__*) ; 
 struct usb_role_switch* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int /*<<< orphan*/  role_class ; 
 int /*<<< orphan*/  usb_role_dev_type ; 

struct usb_role_switch *
usb_role_switch_register(struct device *parent,
			 const struct usb_role_switch_desc *desc)
{
	struct usb_role_switch *sw;
	int ret;

	if (!desc || !desc->set)
		return ERR_PTR(-EINVAL);

	sw = kzalloc(sizeof(*sw), GFP_KERNEL);
	if (!sw)
		return ERR_PTR(-ENOMEM);

	mutex_init(&sw->lock);

	sw->allow_userspace_control = desc->allow_userspace_control;
	sw->usb2_port = desc->usb2_port;
	sw->usb3_port = desc->usb3_port;
	sw->udc = desc->udc;
	sw->set = desc->set;
	sw->get = desc->get;

	sw->dev.parent = parent;
	sw->dev.fwnode = desc->fwnode;
	sw->dev.class = role_class;
	sw->dev.type = &usb_role_dev_type;
	dev_set_name(&sw->dev, "%s-role-switch", dev_name(parent));

	ret = device_register(&sw->dev);
	if (ret) {
		put_device(&sw->dev);
		return ERR_PTR(ret);
	}

	/* TODO: Symlinks for the host port and the device controller. */

	return sw;
}