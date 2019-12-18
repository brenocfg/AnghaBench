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
struct typec_cable_desc {scalar_t__ identity; int /*<<< orphan*/  active; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {int /*<<< orphan*/ * type; int /*<<< orphan*/ * parent; int /*<<< orphan*/  class; int /*<<< orphan*/  groups; } ;
struct typec_cable {TYPE_1__ dev; scalar_t__ identity; int /*<<< orphan*/  active; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct typec_cable* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int device_register (TYPE_1__*) ; 
 struct typec_cable* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int /*<<< orphan*/  typec_cable_dev_type ; 
 int /*<<< orphan*/  typec_class ; 
 int /*<<< orphan*/  usb_pd_id_groups ; 

struct typec_cable *typec_register_cable(struct typec_port *port,
					 struct typec_cable_desc *desc)
{
	struct typec_cable *cable;
	int ret;

	cable = kzalloc(sizeof(*cable), GFP_KERNEL);
	if (!cable)
		return ERR_PTR(-ENOMEM);

	cable->type = desc->type;
	cable->active = desc->active;

	if (desc->identity) {
		/*
		 * Creating directory for the identity only if the driver is
		 * able to provide data to it.
		 */
		cable->dev.groups = usb_pd_id_groups;
		cable->identity = desc->identity;
	}

	cable->dev.class = typec_class;
	cable->dev.parent = &port->dev;
	cable->dev.type = &typec_cable_dev_type;
	dev_set_name(&cable->dev, "%s-cable", dev_name(&port->dev));

	ret = device_register(&cable->dev);
	if (ret) {
		dev_err(&port->dev, "failed to register cable (%d)\n", ret);
		put_device(&cable->dev);
		return ERR_PTR(ret);
	}

	return cable;
}