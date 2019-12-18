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
struct domain_device {struct domain_device* parent; TYPE_1__* port; } ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */

__attribute__((used)) static int sas_find_local_port_id(struct domain_device *dev)
{
	struct domain_device *pdev = dev->parent;

	/* Directly attached device */
	if (!pdev)
		return dev->port->id;
	while (pdev) {
		struct domain_device *pdev_p = pdev->parent;
		if (!pdev_p)
			return pdev->port->id;
		pdev = pdev->parent;
	}
	return 0;
}