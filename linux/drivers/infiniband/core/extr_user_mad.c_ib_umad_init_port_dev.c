#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ib_umad_port {int /*<<< orphan*/  umad_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct ib_device {TYPE_1__ dev; } ;
struct device {int /*<<< orphan*/  release; int /*<<< orphan*/  parent; int /*<<< orphan*/ * class; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct ib_umad_port*) ; 
 int /*<<< orphan*/  device_initialize (struct device*) ; 
 int /*<<< orphan*/  ib_umad_dev_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_umad_release_port ; 
 int /*<<< orphan*/  umad_class ; 

__attribute__((used)) static void ib_umad_init_port_dev(struct device *dev,
				  struct ib_umad_port *port,
				  const struct ib_device *device)
{
	device_initialize(dev);
	ib_umad_dev_get(port->umad_dev);
	dev->class = &umad_class;
	dev->parent = device->dev.parent;
	dev_set_drvdata(dev, port);
	dev->release = ib_umad_release_port;
}