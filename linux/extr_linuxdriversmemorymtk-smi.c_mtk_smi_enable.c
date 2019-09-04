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
struct mtk_smi {int /*<<< orphan*/  dev; int /*<<< orphan*/  clk_apb; int /*<<< orphan*/  clk_smi; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_smi_enable(const struct mtk_smi *smi)
{
	int ret;

	ret = pm_runtime_get_sync(smi->dev);
	if (ret < 0)
		return ret;

	ret = clk_prepare_enable(smi->clk_apb);
	if (ret)
		goto err_put_pm;

	ret = clk_prepare_enable(smi->clk_smi);
	if (ret)
		goto err_disable_apb;

	return 0;

err_disable_apb:
	clk_disable_unprepare(smi->clk_apb);
err_put_pm:
	pm_runtime_put_sync(smi->dev);
	return ret;
}