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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct of_serial_info {int /*<<< orphan*/  clk; int /*<<< orphan*/  rst; int /*<<< orphan*/  line; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct of_serial_info*) ; 
 struct of_serial_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial8250_unregister_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int of_platform_serial_remove(struct platform_device *ofdev)
{
	struct of_serial_info *info = platform_get_drvdata(ofdev);

	serial8250_unregister_port(info->line);

	reset_control_assert(info->rst);
	pm_runtime_put_sync(&ofdev->dev);
	pm_runtime_disable(&ofdev->dev);
	clk_disable_unprepare(info->clk);
	kfree(info);
	return 0;
}