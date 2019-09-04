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
struct qcom_iommu_dev {int /*<<< orphan*/  iface_clk; int /*<<< orphan*/  bus_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qcom_iommu_disable_clocks(struct qcom_iommu_dev *qcom_iommu)
{
	clk_disable_unprepare(qcom_iommu->bus_clk);
	clk_disable_unprepare(qcom_iommu->iface_clk);
}