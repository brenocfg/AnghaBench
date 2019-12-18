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
struct mxc_nand_host {int /*<<< orphan*/  clk; scalar_t__ clk_act; int /*<<< orphan*/  nand; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_release (int /*<<< orphan*/ *) ; 
 struct mxc_nand_host* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int mxcnd_remove(struct platform_device *pdev)
{
	struct mxc_nand_host *host = platform_get_drvdata(pdev);

	nand_release(&host->nand);
	if (host->clk_act)
		clk_disable_unprepare(host->clk);

	return 0;
}