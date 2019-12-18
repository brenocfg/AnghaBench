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
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pm_runtime_allow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync_suspend (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int isp_probe(struct pci_dev *dev, const struct pci_device_id *id)
{
	pm_runtime_allow(&dev->dev);
	pm_runtime_put_sync_suspend(&dev->dev);

	return 0;
}