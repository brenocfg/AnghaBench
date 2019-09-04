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
struct tango_ir {int /*<<< orphan*/  clk; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct tango_ir* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int tango_ir_remove(struct platform_device *pdev)
{
	struct tango_ir *ir = platform_get_drvdata(pdev);

	clk_disable_unprepare(ir->clk);
	return 0;
}