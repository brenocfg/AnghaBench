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
struct qcom_iommu_dev {int /*<<< orphan*/  iface_clk; int /*<<< orphan*/  dev; int /*<<< orphan*/  bus_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int qcom_iommu_enable_clocks(struct qcom_iommu_dev *qcom_iommu)
{
	int ret;

	ret = clk_prepare_enable(qcom_iommu->iface_clk);
	if (ret) {
		dev_err(qcom_iommu->dev, "Couldn't enable iface_clk\n");
		return ret;
	}

	ret = clk_prepare_enable(qcom_iommu->bus_clk);
	if (ret) {
		dev_err(qcom_iommu->dev, "Couldn't enable bus_clk\n");
		clk_disable_unprepare(qcom_iommu->iface_clk);
		return ret;
	}

	return 0;
}