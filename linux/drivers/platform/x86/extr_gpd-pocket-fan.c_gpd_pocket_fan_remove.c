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
struct gpd_pocket_fan_data {int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct gpd_pocket_fan_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int gpd_pocket_fan_remove(struct platform_device *pdev)
{
	struct gpd_pocket_fan_data *fan = platform_get_drvdata(pdev);

	cancel_delayed_work_sync(&fan->work);
	return 0;
}