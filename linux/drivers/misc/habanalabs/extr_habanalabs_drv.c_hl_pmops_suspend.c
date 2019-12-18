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
struct hl_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct hl_device* dev_get_drvdata (struct device*) ; 
 int hl_device_suspend (struct hl_device*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int hl_pmops_suspend(struct device *dev)
{
	struct hl_device *hdev = dev_get_drvdata(dev);

	pr_debug("Going to suspend PCI device\n");

	if (!hdev) {
		pr_err("device pointer is NULL in suspend\n");
		return 0;
	}

	return hl_device_suspend(hdev);
}