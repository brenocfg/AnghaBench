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
struct typec_port {int /*<<< orphan*/  dev; } ;
struct typec_partner_desc {scalar_t__ identity; int /*<<< orphan*/  accessory; int /*<<< orphan*/  usb_pd; } ;
struct TYPE_4__ {int /*<<< orphan*/ * type; int /*<<< orphan*/ * parent; int /*<<< orphan*/  class; int /*<<< orphan*/  groups; } ;
struct typec_partner {TYPE_1__ dev; scalar_t__ identity; int /*<<< orphan*/  accessory; int /*<<< orphan*/  usb_pd; int /*<<< orphan*/  mode_ids; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct typec_partner* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  ida_init (int /*<<< orphan*/ *) ; 
 struct typec_partner* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int /*<<< orphan*/  typec_class ; 
 int /*<<< orphan*/  typec_partner_dev_type ; 
 int /*<<< orphan*/  usb_pd_id_groups ; 

struct typec_partner *typec_register_partner(struct typec_port *port,
					     struct typec_partner_desc *desc)
{
	struct typec_partner *partner;
	int ret;

	partner = kzalloc(sizeof(*partner), GFP_KERNEL);
	if (!partner)
		return ERR_PTR(-ENOMEM);

	ida_init(&partner->mode_ids);
	partner->usb_pd = desc->usb_pd;
	partner->accessory = desc->accessory;

	if (desc->identity) {
		/*
		 * Creating directory for the identity only if the driver is
		 * able to provide data to it.
		 */
		partner->dev.groups = usb_pd_id_groups;
		partner->identity = desc->identity;
	}

	partner->dev.class = typec_class;
	partner->dev.parent = &port->dev;
	partner->dev.type = &typec_partner_dev_type;
	dev_set_name(&partner->dev, "%s-partner", dev_name(&port->dev));

	ret = device_register(&partner->dev);
	if (ret) {
		dev_err(&port->dev, "failed to register partner (%d)\n", ret);
		put_device(&partner->dev);
		return ERR_PTR(ret);
	}

	return partner;
}