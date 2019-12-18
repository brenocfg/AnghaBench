#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * bus; int /*<<< orphan*/ * type; struct TYPE_10__* parent; } ;
struct TYPE_9__ {int /*<<< orphan*/  function_number; } ;
struct rmi_function {TYPE_2__ dev; TYPE_1__ fd; struct rmi_device* rmi_dev; } ;
struct rmi_device {TYPE_2__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RMI_DEBUG_CORE ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int device_add (TYPE_2__*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_2__*) ; 
 int /*<<< orphan*/  put_device (TYPE_2__*) ; 
 int /*<<< orphan*/  rmi_bus_type ; 
 int /*<<< orphan*/  rmi_dbg (int /*<<< orphan*/ ,TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmi_function_type ; 

int rmi_register_function(struct rmi_function *fn)
{
	struct rmi_device *rmi_dev = fn->rmi_dev;
	int error;

	device_initialize(&fn->dev);

	dev_set_name(&fn->dev, "%s.fn%02x",
		     dev_name(&rmi_dev->dev), fn->fd.function_number);

	fn->dev.parent = &rmi_dev->dev;
	fn->dev.type = &rmi_function_type;
	fn->dev.bus = &rmi_bus_type;

	error = device_add(&fn->dev);
	if (error) {
		dev_err(&rmi_dev->dev,
			"Failed device_register function device %s\n",
			dev_name(&fn->dev));
		goto err_put_device;
	}

	rmi_dbg(RMI_DEBUG_CORE, &rmi_dev->dev, "Registered F%02X.\n",
			fn->fd.function_number);

	return 0;

err_put_device:
	put_device(&fn->dev);
	return error;
}