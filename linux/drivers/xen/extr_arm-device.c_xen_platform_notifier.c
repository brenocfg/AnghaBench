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
struct platform_device {scalar_t__ num_resources; int /*<<< orphan*/  name; int /*<<< orphan*/  dev; int /*<<< orphan*/ * resource; } ;
struct notifier_block {int dummy; } ;

/* Variables and functions */
#define  BUS_NOTIFY_ADD_DEVICE 129 
#define  BUS_NOTIFY_DEL_DEVICE 128 
 int NOTIFY_DONE ; 
 int NOTIFY_OK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 struct platform_device* to_platform_device (void*) ; 
 int xen_map_device_mmio (int /*<<< orphan*/ *,scalar_t__) ; 
 int xen_unmap_device_mmio (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int xen_platform_notifier(struct notifier_block *nb,
				 unsigned long action, void *data)
{
	struct platform_device *pdev = to_platform_device(data);
	int r = 0;

	if (pdev->num_resources == 0 || pdev->resource == NULL)
		return NOTIFY_OK;

	switch (action) {
	case BUS_NOTIFY_ADD_DEVICE:
		r = xen_map_device_mmio(pdev->resource, pdev->num_resources);
		break;
	case BUS_NOTIFY_DEL_DEVICE:
		r = xen_unmap_device_mmio(pdev->resource, pdev->num_resources);
		break;
	default:
		return NOTIFY_DONE;
	}
	if (r)
		dev_err(&pdev->dev, "Platform: Failed to %s device %s MMIO!\n",
			action == BUS_NOTIFY_ADD_DEVICE ? "map" :
			(action == BUS_NOTIFY_DEL_DEVICE ? "unmap" : "?"),
			pdev->name);

	return NOTIFY_OK;
}