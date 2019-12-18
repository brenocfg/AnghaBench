#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ti_st_plat_data {int (* suspend ) (struct platform_device*,int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {struct ti_st_plat_data* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int stub1 (struct platform_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kim_suspend(struct platform_device *pdev, pm_message_t state)
{
	struct ti_st_plat_data	*pdata = pdev->dev.platform_data;

	if (pdata->suspend)
		return pdata->suspend(pdev, state);

	return 0;
}