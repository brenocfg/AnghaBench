#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  dma_mask; } ;
struct gb_interface {TYPE_3__ dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dma_mask; int /*<<< orphan*/  groups; int /*<<< orphan*/ * type; int /*<<< orphan*/ * bus; TYPE_3__* parent; } ;
struct gb_control {struct gb_connection* connection; TYPE_1__ dev; struct gb_interface* intf; } ;
struct gb_connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct gb_control* ERR_CAST (struct gb_connection*) ; 
 struct gb_control* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct gb_connection*) ; 
 int /*<<< orphan*/  PTR_ERR (struct gb_connection*) ; 
 int /*<<< orphan*/  control_groups ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 struct gb_connection* gb_connection_create_control (struct gb_interface*) ; 
 int /*<<< orphan*/  gb_connection_set_data (struct gb_connection*,struct gb_control*) ; 
 int /*<<< orphan*/  greybus_bus_type ; 
 int /*<<< orphan*/  greybus_control_type ; 
 int /*<<< orphan*/  kfree (struct gb_control*) ; 
 struct gb_control* kzalloc (int,int /*<<< orphan*/ ) ; 

struct gb_control *gb_control_create(struct gb_interface *intf)
{
	struct gb_connection *connection;
	struct gb_control *control;

	control = kzalloc(sizeof(*control), GFP_KERNEL);
	if (!control)
		return ERR_PTR(-ENOMEM);

	control->intf = intf;

	connection = gb_connection_create_control(intf);
	if (IS_ERR(connection)) {
		dev_err(&intf->dev,
			"failed to create control connection: %ld\n",
			PTR_ERR(connection));
		kfree(control);
		return ERR_CAST(connection);
	}

	control->connection = connection;

	control->dev.parent = &intf->dev;
	control->dev.bus = &greybus_bus_type;
	control->dev.type = &greybus_control_type;
	control->dev.groups = control_groups;
	control->dev.dma_mask = intf->dev.dma_mask;
	device_initialize(&control->dev);
	dev_set_name(&control->dev, "%s.ctrl", dev_name(&intf->dev));

	gb_connection_set_data(control->connection, control);

	return control;
}