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
struct mlxreg_fan {int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_THERMAL ; 
 scalar_t__ IS_REACHABLE (int /*<<< orphan*/ ) ; 
 struct mlxreg_fan* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  thermal_cooling_device_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxreg_fan_remove(struct platform_device *pdev)
{
	struct mlxreg_fan *fan = platform_get_drvdata(pdev);

	if (IS_REACHABLE(CONFIG_THERMAL))
		thermal_cooling_device_unregister(fan->cdev);

	return 0;
}