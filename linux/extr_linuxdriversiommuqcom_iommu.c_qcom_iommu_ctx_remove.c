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
struct qcom_iommu_dev {int /*<<< orphan*/ ** ctxs; } ;
struct qcom_iommu_ctx {int asid; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 struct qcom_iommu_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct qcom_iommu_ctx* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qcom_iommu_ctx_remove(struct platform_device *pdev)
{
	struct qcom_iommu_dev *qcom_iommu = dev_get_drvdata(pdev->dev.parent);
	struct qcom_iommu_ctx *ctx = platform_get_drvdata(pdev);

	platform_set_drvdata(pdev, NULL);

	qcom_iommu->ctxs[ctx->asid - 1] = NULL;

	return 0;
}