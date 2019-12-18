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
struct db8500_thermal_zone {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRCMU_DEFAULT_LOW_TEMP ; 
 int /*<<< orphan*/  THERMAL_TREND_STABLE ; 
 int /*<<< orphan*/ * db8500_thermal_points ; 
 int /*<<< orphan*/  db8500_thermal_update_config (struct db8500_thermal_zone*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct db8500_thermal_zone* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int db8500_thermal_resume(struct platform_device *pdev)
{
	struct db8500_thermal_zone *th = platform_get_drvdata(pdev);

	/* Resume and start measuring at the lowest point */
	db8500_thermal_update_config(th, 0, THERMAL_TREND_STABLE,
				     PRCMU_DEFAULT_LOW_TEMP,
				     db8500_thermal_points[0]);

	return 0;
}