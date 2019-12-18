#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct resource {struct resource* sibling; } ;
struct acpi_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  __release_region (struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* fb_mmio ; 
 struct resource* hyperv_mmio ; 
 int /*<<< orphan*/  kfree (struct resource*) ; 
 int /*<<< orphan*/  resource_size (TYPE_1__*) ; 

__attribute__((used)) static int vmbus_acpi_remove(struct acpi_device *device)
{
	struct resource *cur_res;
	struct resource *next_res;

	if (hyperv_mmio) {
		if (fb_mmio) {
			__release_region(hyperv_mmio, fb_mmio->start,
					 resource_size(fb_mmio));
			fb_mmio = NULL;
		}

		for (cur_res = hyperv_mmio; cur_res; cur_res = next_res) {
			next_res = cur_res->sibling;
			kfree(cur_res);
		}
	}

	return 0;
}