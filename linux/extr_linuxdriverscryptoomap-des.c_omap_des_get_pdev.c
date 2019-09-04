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
struct TYPE_2__ {int /*<<< orphan*/  platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct omap_des_dev {int /*<<< orphan*/  pdata; } ;

/* Variables and functions */

__attribute__((used)) static int omap_des_get_pdev(struct omap_des_dev *dd,
		struct platform_device *pdev)
{
	/* non-DT devices get pdata from pdev */
	dd->pdata = pdev->dev.platform_data;

	return 0;
}