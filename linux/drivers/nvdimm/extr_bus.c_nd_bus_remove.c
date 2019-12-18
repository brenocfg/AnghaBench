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
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
struct nvdimm_bus {TYPE_1__ badrange; int /*<<< orphan*/  dev; int /*<<< orphan*/  ioctl_active; int /*<<< orphan*/  wait; int /*<<< orphan*/  list; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  child_unregister ; 
 int /*<<< orphan*/  device_for_each_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_badrange_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nd_synchronize () ; 
 int /*<<< orphan*/  nvdimm_bus_destroy_ndctl (struct nvdimm_bus*) ; 
 int /*<<< orphan*/  nvdimm_bus_list_mutex ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct nvdimm_bus* to_nvdimm_bus (struct device*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int nd_bus_remove(struct device *dev)
{
	struct nvdimm_bus *nvdimm_bus = to_nvdimm_bus(dev);

	mutex_lock(&nvdimm_bus_list_mutex);
	list_del_init(&nvdimm_bus->list);
	mutex_unlock(&nvdimm_bus_list_mutex);

	wait_event(nvdimm_bus->wait,
			atomic_read(&nvdimm_bus->ioctl_active) == 0);

	nd_synchronize();
	device_for_each_child(&nvdimm_bus->dev, NULL, child_unregister);

	spin_lock(&nvdimm_bus->badrange.lock);
	free_badrange_list(&nvdimm_bus->badrange.list);
	spin_unlock(&nvdimm_bus->badrange.lock);

	nvdimm_bus_destroy_ndctl(nvdimm_bus);

	return 0;
}