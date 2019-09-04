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
struct ti_st_plat_data {int (* resume ) (struct platform_device*) ;} ;
struct TYPE_2__ {struct ti_st_plat_data* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int stub1 (struct platform_device*) ; 

__attribute__((used)) static int kim_resume(struct platform_device *pdev)
{
	struct ti_st_plat_data	*pdata = pdev->dev.platform_data;

	if (pdata->resume)
		return pdata->resume(pdev);

	return 0;
}