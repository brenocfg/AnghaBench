#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * type; int /*<<< orphan*/  fwnode; struct device* parent; int /*<<< orphan*/  class; } ;
struct typec_port {void* pwr_role; int id; int port_type; void* prefer_role; TYPE_1__ dev; int /*<<< orphan*/  mux; int /*<<< orphan*/  sw; struct typec_capability const* cap; int /*<<< orphan*/  port_type_lock; int /*<<< orphan*/  mode_ids; void* data_role; void* vconn_role; } ;
struct typec_capability {int type; void* prefer_role; int data; int /*<<< orphan*/  fwnode; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct typec_port* ERR_CAST (int /*<<< orphan*/ ) ; 
 struct typec_port* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 void* TYPEC_DEVICE ; 
 void* TYPEC_HOST ; 
 void* TYPEC_NO_PREFERRED_ROLE ; 
#define  TYPEC_PORT_DFP 133 
#define  TYPEC_PORT_DRD 132 
#define  TYPEC_PORT_DRP 131 
#define  TYPEC_PORT_SNK 130 
#define  TYPEC_PORT_SRC 129 
#define  TYPEC_PORT_UFP 128 
 void* TYPEC_SINK ; 
 void* TYPEC_SOURCE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int) ; 
 int device_add (TYPE_1__*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  ida_init (int /*<<< orphan*/ *) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct typec_port*) ; 
 struct typec_port* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int /*<<< orphan*/  typec_class ; 
 int /*<<< orphan*/  typec_index_ida ; 
 int /*<<< orphan*/  typec_mux_get (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  typec_port_dev_type ; 
 int /*<<< orphan*/  typec_switch_get (TYPE_1__*) ; 

struct typec_port *typec_register_port(struct device *parent,
				       const struct typec_capability *cap)
{
	struct typec_port *port;
	int ret;
	int id;

	port = kzalloc(sizeof(*port), GFP_KERNEL);
	if (!port)
		return ERR_PTR(-ENOMEM);

	id = ida_simple_get(&typec_index_ida, 0, 0, GFP_KERNEL);
	if (id < 0) {
		kfree(port);
		return ERR_PTR(id);
	}

	switch (cap->type) {
	case TYPEC_PORT_SRC:
		port->pwr_role = TYPEC_SOURCE;
		port->vconn_role = TYPEC_SOURCE;
		break;
	case TYPEC_PORT_SNK:
		port->pwr_role = TYPEC_SINK;
		port->vconn_role = TYPEC_SINK;
		break;
	case TYPEC_PORT_DRP:
		if (cap->prefer_role != TYPEC_NO_PREFERRED_ROLE)
			port->pwr_role = cap->prefer_role;
		else
			port->pwr_role = TYPEC_SINK;
		break;
	}

	switch (cap->data) {
	case TYPEC_PORT_DFP:
		port->data_role = TYPEC_HOST;
		break;
	case TYPEC_PORT_UFP:
		port->data_role = TYPEC_DEVICE;
		break;
	case TYPEC_PORT_DRD:
		if (cap->prefer_role == TYPEC_SOURCE)
			port->data_role = TYPEC_HOST;
		else
			port->data_role = TYPEC_DEVICE;
		break;
	}

	ida_init(&port->mode_ids);
	mutex_init(&port->port_type_lock);

	port->id = id;
	port->cap = cap;
	port->port_type = cap->type;
	port->prefer_role = cap->prefer_role;

	device_initialize(&port->dev);
	port->dev.class = typec_class;
	port->dev.parent = parent;
	port->dev.fwnode = cap->fwnode;
	port->dev.type = &typec_port_dev_type;
	dev_set_name(&port->dev, "port%d", id);

	port->sw = typec_switch_get(&port->dev);
	if (IS_ERR(port->sw)) {
		put_device(&port->dev);
		return ERR_CAST(port->sw);
	}

	port->mux = typec_mux_get(&port->dev, NULL);
	if (IS_ERR(port->mux)) {
		put_device(&port->dev);
		return ERR_CAST(port->mux);
	}

	ret = device_add(&port->dev);
	if (ret) {
		dev_err(parent, "failed to register port (%d)\n", ret);
		put_device(&port->dev);
		return ERR_PTR(ret);
	}

	return port;
}