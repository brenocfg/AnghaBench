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
struct qcom_wcnss {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 struct qcom_wcnss* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcom_wcnss_assign_iris (struct qcom_wcnss*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int qcom_iris_remove(struct platform_device *pdev)
{
	struct qcom_wcnss *wcnss = dev_get_drvdata(pdev->dev.parent);

	qcom_wcnss_assign_iris(wcnss, NULL, false);

	return 0;
}