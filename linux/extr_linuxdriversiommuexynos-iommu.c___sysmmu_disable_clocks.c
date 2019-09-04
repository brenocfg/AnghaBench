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
struct sysmmu_drvdata {int /*<<< orphan*/  clk_master; int /*<<< orphan*/  clk; int /*<<< orphan*/  pclk; int /*<<< orphan*/  aclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __sysmmu_disable_clocks(struct sysmmu_drvdata *data)
{
	clk_disable_unprepare(data->aclk);
	clk_disable_unprepare(data->pclk);
	clk_disable_unprepare(data->clk);
	clk_disable_unprepare(data->clk_master);
}