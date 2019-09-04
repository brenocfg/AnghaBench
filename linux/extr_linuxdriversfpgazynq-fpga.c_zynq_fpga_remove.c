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
struct zynq_fpga_priv {int /*<<< orphan*/  clk; } ;
struct platform_device {int dummy; } ;
struct fpga_manager {struct zynq_fpga_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpga_mgr_unregister (struct fpga_manager*) ; 
 struct fpga_manager* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int zynq_fpga_remove(struct platform_device *pdev)
{
	struct zynq_fpga_priv *priv;
	struct fpga_manager *mgr;

	mgr = platform_get_drvdata(pdev);
	priv = mgr->priv;

	fpga_mgr_unregister(mgr);

	clk_unprepare(priv->clk);

	return 0;
}