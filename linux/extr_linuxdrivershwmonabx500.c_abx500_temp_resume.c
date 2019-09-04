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
struct abx500_temp {scalar_t__ work_active; } ;

/* Variables and functions */
 struct abx500_temp* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  schedule_monitor (struct abx500_temp*) ; 

__attribute__((used)) static int abx500_temp_resume(struct platform_device *pdev)
{
	struct abx500_temp *data = platform_get_drvdata(pdev);

	if (data->work_active)
		schedule_monitor(data);

	return 0;
}