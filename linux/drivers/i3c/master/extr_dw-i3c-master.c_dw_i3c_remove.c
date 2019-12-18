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
struct dw_i3c_master {int /*<<< orphan*/  core_clk; int /*<<< orphan*/  core_rst; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int i3c_master_unregister (int /*<<< orphan*/ *) ; 
 struct dw_i3c_master* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dw_i3c_remove(struct platform_device *pdev)
{
	struct dw_i3c_master *master = platform_get_drvdata(pdev);
	int ret;

	ret = i3c_master_unregister(&master->base);
	if (ret)
		return ret;

	reset_control_assert(master->core_rst);

	clk_disable_unprepare(master->core_clk);

	return 0;
}