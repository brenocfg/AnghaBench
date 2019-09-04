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
struct qcom_rpm {int /*<<< orphan*/  ramclk; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct qcom_rpm* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_platform_depopulate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qcom_rpm_remove(struct platform_device *pdev)
{
	struct qcom_rpm *rpm = dev_get_drvdata(&pdev->dev);

	of_platform_depopulate(&pdev->dev);
	clk_disable_unprepare(rpm->ramclk);

	return 0;
}