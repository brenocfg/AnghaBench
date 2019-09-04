#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct klist_iter {int dummy; } ;
struct device {unsigned int id; TYPE_1__* p; } ;
struct bus_type {TYPE_2__* p; } ;
struct TYPE_4__ {int /*<<< orphan*/  klist_devices; } ;
struct TYPE_3__ {int /*<<< orphan*/  knode_bus; } ;

/* Variables and functions */
 scalar_t__ get_device (struct device*) ; 
 int /*<<< orphan*/  klist_iter_exit (struct klist_iter*) ; 
 int /*<<< orphan*/  klist_iter_init_node (int /*<<< orphan*/ *,struct klist_iter*,int /*<<< orphan*/ *) ; 
 struct device* next_device (struct klist_iter*) ; 

struct device *subsys_find_device_by_id(struct bus_type *subsys, unsigned int id,
					struct device *hint)
{
	struct klist_iter i;
	struct device *dev;

	if (!subsys)
		return NULL;

	if (hint) {
		klist_iter_init_node(&subsys->p->klist_devices, &i, &hint->p->knode_bus);
		dev = next_device(&i);
		if (dev && dev->id == id && get_device(dev)) {
			klist_iter_exit(&i);
			return dev;
		}
		klist_iter_exit(&i);
	}

	klist_iter_init_node(&subsys->p->klist_devices, &i, NULL);
	while ((dev = next_device(&i))) {
		if (dev->id == id && get_device(dev)) {
			klist_iter_exit(&i);
			return dev;
		}
	}
	klist_iter_exit(&i);
	return NULL;
}