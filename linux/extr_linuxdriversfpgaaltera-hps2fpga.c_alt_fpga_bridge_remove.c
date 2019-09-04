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
struct platform_device {int dummy; } ;
struct fpga_bridge {struct altera_hps2fpga_data* priv; } ;
struct altera_hps2fpga_data {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpga_bridge_unregister (struct fpga_bridge*) ; 
 struct fpga_bridge* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int alt_fpga_bridge_remove(struct platform_device *pdev)
{
	struct fpga_bridge *bridge = platform_get_drvdata(pdev);
	struct altera_hps2fpga_data *priv = bridge->priv;

	fpga_bridge_unregister(bridge);

	clk_disable_unprepare(priv->clk);

	return 0;
}