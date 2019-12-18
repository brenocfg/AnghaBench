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
struct qcom_ipq806x_sata_phy {int /*<<< orphan*/  cfg_clk; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct qcom_ipq806x_sata_phy* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int qcom_ipq806x_sata_phy_remove(struct platform_device *pdev)
{
	struct qcom_ipq806x_sata_phy *phy = platform_get_drvdata(pdev);

	clk_disable_unprepare(phy->cfg_clk);

	return 0;
}