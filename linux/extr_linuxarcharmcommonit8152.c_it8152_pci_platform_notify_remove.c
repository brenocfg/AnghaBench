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
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ dev_is_pci (struct device*) ; 
 int /*<<< orphan*/  dmabounce_unregister_dev (struct device*) ; 

__attribute__((used)) static int it8152_pci_platform_notify_remove(struct device *dev)
{
	if (dev_is_pci(dev))
		dmabounce_unregister_dev(dev);

	return 0;
}