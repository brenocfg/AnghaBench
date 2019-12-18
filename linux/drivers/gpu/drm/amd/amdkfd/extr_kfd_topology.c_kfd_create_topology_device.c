#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct list_head {int dummy; } ;
struct kfd_topology_device {int /*<<< orphan*/  list; int /*<<< orphan*/  perf_props; int /*<<< orphan*/  io_link_props; int /*<<< orphan*/  cache_props; int /*<<< orphan*/  mem_props; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct kfd_topology_device* kfd_alloc_struct (struct kfd_topology_device*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

struct kfd_topology_device *kfd_create_topology_device(
				struct list_head *device_list)
{
	struct kfd_topology_device *dev;

	dev = kfd_alloc_struct(dev);
	if (!dev) {
		pr_err("No memory to allocate a topology device");
		return NULL;
	}

	INIT_LIST_HEAD(&dev->mem_props);
	INIT_LIST_HEAD(&dev->cache_props);
	INIT_LIST_HEAD(&dev->io_link_props);
	INIT_LIST_HEAD(&dev->perf_props);

	list_add_tail(&dev->list, device_list);

	return dev;
}