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
struct hisi_pmu {int ccl_id; int /*<<< orphan*/  base; int /*<<< orphan*/  sccl_id; int /*<<< orphan*/  index_id; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ device_property_read_u32 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hisi_ddrc_pmu_init_data(struct platform_device *pdev,
				   struct hisi_pmu *ddrc_pmu)
{
	struct resource *res;

	/*
	 * Use the SCCL_ID and DDRC channel ID to identify the
	 * DDRC PMU, while SCCL_ID is in MPIDR[aff2].
	 */
	if (device_property_read_u32(&pdev->dev, "hisilicon,ch-id",
				     &ddrc_pmu->index_id)) {
		dev_err(&pdev->dev, "Can not read ddrc channel-id!\n");
		return -EINVAL;
	}

	if (device_property_read_u32(&pdev->dev, "hisilicon,scl-id",
				     &ddrc_pmu->sccl_id)) {
		dev_err(&pdev->dev, "Can not read ddrc sccl-id!\n");
		return -EINVAL;
	}
	/* DDRC PMUs only share the same SCCL */
	ddrc_pmu->ccl_id = -1;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	ddrc_pmu->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(ddrc_pmu->base)) {
		dev_err(&pdev->dev, "ioremap failed for ddrc_pmu resource\n");
		return PTR_ERR(ddrc_pmu->base);
	}

	return 0;
}