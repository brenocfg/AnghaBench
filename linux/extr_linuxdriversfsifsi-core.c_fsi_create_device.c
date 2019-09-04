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
struct fsi_slave {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  release; int /*<<< orphan*/ * bus; int /*<<< orphan*/ * parent; } ;
struct fsi_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  fsi_bus_type ; 
 int /*<<< orphan*/  fsi_device_release ; 
 struct fsi_device* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct fsi_device *fsi_create_device(struct fsi_slave *slave)
{
	struct fsi_device *dev;

	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return NULL;

	dev->dev.parent = &slave->dev;
	dev->dev.bus = &fsi_bus_type;
	dev->dev.release = fsi_device_release;

	return dev;
}