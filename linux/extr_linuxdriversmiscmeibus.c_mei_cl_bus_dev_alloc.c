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
struct mei_me_client {int dummy; } ;
struct mei_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * type; int /*<<< orphan*/ * bus; int /*<<< orphan*/  parent; } ;
struct mei_cl_device {int /*<<< orphan*/  bus_list; scalar_t__ is_added; struct mei_cl* cl; int /*<<< orphan*/  me_cl; int /*<<< orphan*/  bus; TYPE_1__ dev; } ;
struct mei_cl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct mei_cl_device*) ; 
 struct mei_cl_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct mei_cl* mei_cl_allocate (struct mei_device*) ; 
 int /*<<< orphan*/  mei_cl_bus_set_name (struct mei_cl_device*) ; 
 int /*<<< orphan*/  mei_cl_bus_type ; 
 int /*<<< orphan*/  mei_cl_device_type ; 
 int /*<<< orphan*/  mei_dev_bus_get (struct mei_device*) ; 
 int /*<<< orphan*/  mei_me_cl_get (struct mei_me_client*) ; 

__attribute__((used)) static struct mei_cl_device *mei_cl_bus_dev_alloc(struct mei_device *bus,
						  struct mei_me_client *me_cl)
{
	struct mei_cl_device *cldev;
	struct mei_cl *cl;

	cldev = kzalloc(sizeof(struct mei_cl_device), GFP_KERNEL);
	if (!cldev)
		return NULL;

	cl = mei_cl_allocate(bus);
	if (!cl) {
		kfree(cldev);
		return NULL;
	}

	device_initialize(&cldev->dev);
	cldev->dev.parent = bus->dev;
	cldev->dev.bus    = &mei_cl_bus_type;
	cldev->dev.type   = &mei_cl_device_type;
	cldev->bus        = mei_dev_bus_get(bus);
	cldev->me_cl      = mei_me_cl_get(me_cl);
	cldev->cl         = cl;
	mei_cl_bus_set_name(cldev);
	cldev->is_added   = 0;
	INIT_LIST_HEAD(&cldev->bus_list);

	return cldev;
}