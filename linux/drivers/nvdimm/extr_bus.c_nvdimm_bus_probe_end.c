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
struct nvdimm_bus {scalar_t__ probe_active; int /*<<< orphan*/  dev; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvdimm_bus_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvdimm_bus_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nvdimm_bus_probe_end(struct nvdimm_bus *nvdimm_bus)
{
	nvdimm_bus_lock(&nvdimm_bus->dev);
	if (--nvdimm_bus->probe_active == 0)
		wake_up(&nvdimm_bus->wait);
	nvdimm_bus_unlock(&nvdimm_bus->dev);
}