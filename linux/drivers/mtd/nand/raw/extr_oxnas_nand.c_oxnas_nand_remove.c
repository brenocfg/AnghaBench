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
struct oxnas_nand_ctrl {int /*<<< orphan*/  clk; scalar_t__* chips; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_release (scalar_t__) ; 
 struct oxnas_nand_ctrl* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int oxnas_nand_remove(struct platform_device *pdev)
{
	struct oxnas_nand_ctrl *oxnas = platform_get_drvdata(pdev);

	if (oxnas->chips[0])
		nand_release(oxnas->chips[0]);

	clk_disable_unprepare(oxnas->clk);

	return 0;
}