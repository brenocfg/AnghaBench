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
struct qcom_ethqos {int /*<<< orphan*/  rgmii_clk; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct qcom_ethqos* get_stmmac_bsp_priv (int /*<<< orphan*/ *) ; 
 int stmmac_pltfr_remove (struct platform_device*) ; 

__attribute__((used)) static int qcom_ethqos_remove(struct platform_device *pdev)
{
	struct qcom_ethqos *ethqos;
	int ret;

	ethqos = get_stmmac_bsp_priv(&pdev->dev);
	if (!ethqos)
		return -ENODEV;

	ret = stmmac_pltfr_remove(pdev);
	clk_disable_unprepare(ethqos->rgmii_clk);

	return ret;
}