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
struct p2wi {int /*<<< orphan*/  adapter; int /*<<< orphan*/  clk; int /*<<< orphan*/  rstc; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 struct p2wi* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int p2wi_remove(struct platform_device *dev)
{
	struct p2wi *p2wi = platform_get_drvdata(dev);

	reset_control_assert(p2wi->rstc);
	clk_disable_unprepare(p2wi->clk);
	i2c_del_adapter(&p2wi->adapter);

	return 0;
}