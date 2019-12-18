#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  release; int /*<<< orphan*/ * bus; int /*<<< orphan*/ * parent; } ;
struct TYPE_7__ {int id; } ;
struct TYPE_8__ {int mod_id; } ;
struct superhyway_device {TYPE_4__ dev; TYPE_2__ id; int /*<<< orphan*/  name; TYPE_3__ vcr; TYPE_1__* resource; struct superhyway_bus* bus; } ;
struct superhyway_bus {int dummy; } ;
struct resource {int dummy; } ;
struct TYPE_6__ {unsigned long start; int end; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_set_name (TYPE_4__*,char*,int /*<<< orphan*/ ) ; 
 int device_register (TYPE_4__*) ; 
 int /*<<< orphan*/  kfree (struct superhyway_device*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  superhyway_bus_device ; 
 int /*<<< orphan*/  superhyway_bus_type ; 
 int /*<<< orphan*/  superhyway_device_release ; 
 int /*<<< orphan*/  superhyway_devices ; 
 int /*<<< orphan*/  superhyway_read_vcr (struct superhyway_device*,unsigned long,TYPE_3__*) ; 

int superhyway_add_device(unsigned long base, struct superhyway_device *sdev,
			  struct superhyway_bus *bus)
{
	struct superhyway_device *dev = sdev;

	if (!dev) {
		dev = kzalloc(sizeof(struct superhyway_device), GFP_KERNEL);
		if (!dev)
			return -ENOMEM;

	}

	dev->bus = bus;
	superhyway_read_vcr(dev, base, &dev->vcr);

	if (!dev->resource) {
		dev->resource = kzalloc(sizeof(struct resource), GFP_KERNEL);
		if (!dev->resource) {
			kfree(dev);
			return -ENOMEM;
		}

		dev->resource->name	= dev->name;
		dev->resource->start	= base;
		dev->resource->end	= dev->resource->start + 0x01000000;
	}

	dev->dev.parent		= &superhyway_bus_device;
	dev->dev.bus		= &superhyway_bus_type;
	dev->dev.release	= superhyway_device_release;
	dev->id.id		= dev->vcr.mod_id;

	sprintf(dev->name, "SuperHyway device %04x", dev->id.id);
	dev_set_name(&dev->dev, "%02x", superhyway_devices);

	superhyway_devices++;

	return device_register(&dev->dev);
}