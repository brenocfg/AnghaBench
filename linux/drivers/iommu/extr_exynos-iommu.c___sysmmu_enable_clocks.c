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
struct sysmmu_drvdata {int /*<<< orphan*/  aclk; int /*<<< orphan*/  pclk; int /*<<< orphan*/  clk; int /*<<< orphan*/  clk_master; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __sysmmu_enable_clocks(struct sysmmu_drvdata *data)
{
	BUG_ON(clk_prepare_enable(data->clk_master));
	BUG_ON(clk_prepare_enable(data->clk));
	BUG_ON(clk_prepare_enable(data->pclk));
	BUG_ON(clk_prepare_enable(data->aclk));
}