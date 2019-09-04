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
struct abx500_temp {int /*<<< orphan*/  work; scalar_t__ work_active; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct abx500_temp* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int abx500_temp_suspend(struct platform_device *pdev,
			       pm_message_t state)
{
	struct abx500_temp *data = platform_get_drvdata(pdev);

	if (data->work_active)
		cancel_delayed_work_sync(&data->work);

	return 0;
}