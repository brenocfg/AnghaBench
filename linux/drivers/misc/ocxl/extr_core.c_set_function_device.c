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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  release; int /*<<< orphan*/ * parent; } ;
struct ocxl_fn {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int dev_set_name (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_function_dev ; 

__attribute__((used)) static int set_function_device(struct ocxl_fn *fn, struct pci_dev *dev)
{
	int rc;

	fn->dev.parent = &dev->dev;
	fn->dev.release = free_function_dev;
	rc = dev_set_name(&fn->dev, "ocxlfn.%s", dev_name(&dev->dev));
	if (rc)
		return rc;
	return 0;
}