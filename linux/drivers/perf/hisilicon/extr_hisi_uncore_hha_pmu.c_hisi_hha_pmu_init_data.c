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
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct hisi_pmu {unsigned long long index_id; int ccl_id; int /*<<< orphan*/  base; int /*<<< orphan*/  sccl_id; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_HANDLE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ device_property_read_u32 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hisi_hha_pmu_init_data(struct platform_device *pdev,
				  struct hisi_pmu *hha_pmu)
{
	unsigned long long id;
	struct resource *res;
	acpi_status status;

	status = acpi_evaluate_integer(ACPI_HANDLE(&pdev->dev),
				       "_UID", NULL, &id);
	if (ACPI_FAILURE(status))
		return -EINVAL;

	hha_pmu->index_id = id;

	/*
	 * Use SCCL_ID and UID to identify the HHA PMU, while
	 * SCCL_ID is in MPIDR[aff2].
	 */
	if (device_property_read_u32(&pdev->dev, "hisilicon,scl-id",
				     &hha_pmu->sccl_id)) {
		dev_err(&pdev->dev, "Can not read hha sccl-id!\n");
		return -EINVAL;
	}
	/* HHA PMUs only share the same SCCL */
	hha_pmu->ccl_id = -1;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	hha_pmu->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(hha_pmu->base)) {
		dev_err(&pdev->dev, "ioremap failed for hha_pmu resource\n");
		return PTR_ERR(hha_pmu->base);
	}

	return 0;
}