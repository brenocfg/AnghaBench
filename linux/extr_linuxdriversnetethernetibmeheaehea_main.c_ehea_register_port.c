#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct device {int /*<<< orphan*/  release; int /*<<< orphan*/ * bus; int /*<<< orphan*/ * parent; int /*<<< orphan*/  of_node; } ;
struct TYPE_7__ {struct device dev; } ;
struct ehea_port {TYPE_3__ ofdev; TYPE_2__* adapter; } ;
struct device_node {int dummy; } ;
struct TYPE_6__ {TYPE_1__* ofdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_log_port_id ; 
 int /*<<< orphan*/  dev_set_name (struct device*,char*,int /*<<< orphan*/ ) ; 
 int device_create_file (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ibmebus_bus_type ; 
 int /*<<< orphan*/  logical_port_release ; 
 int of_device_register (TYPE_3__*) ; 
 int /*<<< orphan*/  of_device_unregister (TYPE_3__*) ; 
 int /*<<< orphan*/  of_node_get (struct device_node*) ; 
 int /*<<< orphan*/  port_name_cnt ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static struct device *ehea_register_port(struct ehea_port *port,
					 struct device_node *dn)
{
	int ret;

	port->ofdev.dev.of_node = of_node_get(dn);
	port->ofdev.dev.parent = &port->adapter->ofdev->dev;
	port->ofdev.dev.bus = &ibmebus_bus_type;

	dev_set_name(&port->ofdev.dev, "port%d", port_name_cnt++);
	port->ofdev.dev.release = logical_port_release;

	ret = of_device_register(&port->ofdev);
	if (ret) {
		pr_err("failed to register device. ret=%d\n", ret);
		goto out;
	}

	ret = device_create_file(&port->ofdev.dev, &dev_attr_log_port_id);
	if (ret) {
		pr_err("failed to register attributes, ret=%d\n", ret);
		goto out_unreg_of_dev;
	}

	return &port->ofdev.dev;

out_unreg_of_dev:
	of_device_unregister(&port->ofdev);
out:
	return NULL;
}