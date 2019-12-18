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
struct platform_device {struct device dev; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_HANDLE (struct device*) ; 
 int /*<<< orphan*/  ACPI_TYPE_DEVICE ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  acpi_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_walk_namespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_to_node (struct device*) ; 
 int /*<<< orphan*/  has_acpi_companion (struct device*) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dev_node (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tx2_uncore_pmu_add ; 

__attribute__((used)) static int tx2_uncore_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	acpi_handle handle;
	acpi_status status;

	set_dev_node(dev, acpi_get_node(ACPI_HANDLE(dev)));

	if (!has_acpi_companion(dev))
		return -ENODEV;

	handle = ACPI_HANDLE(dev);
	if (!handle)
		return -EINVAL;

	/* Walk through the tree for all PMU UNCORE devices */
	status = acpi_walk_namespace(ACPI_TYPE_DEVICE, handle, 1,
				     tx2_uncore_pmu_add,
				     NULL, dev, NULL);
	if (ACPI_FAILURE(status)) {
		dev_err(dev, "failed to probe PMU devices\n");
		return_ACPI_STATUS(status);
	}

	dev_info(dev, "node%d: pmu uncore registered\n", dev_to_node(dev));
	return 0;
}