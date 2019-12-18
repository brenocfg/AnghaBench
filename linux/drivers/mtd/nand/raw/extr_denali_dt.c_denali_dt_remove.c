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
struct denali_dt {int /*<<< orphan*/  clk; int /*<<< orphan*/  clk_x; int /*<<< orphan*/  clk_ecc; int /*<<< orphan*/  controller; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  denali_remove (int /*<<< orphan*/ *) ; 
 struct denali_dt* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int denali_dt_remove(struct platform_device *pdev)
{
	struct denali_dt *dt = platform_get_drvdata(pdev);

	denali_remove(&dt->controller);
	clk_disable_unprepare(dt->clk_ecc);
	clk_disable_unprepare(dt->clk_x);
	clk_disable_unprepare(dt->clk);

	return 0;
}