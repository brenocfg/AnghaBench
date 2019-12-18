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
struct isc_device {int /*<<< orphan*/  hclock; int /*<<< orphan*/  ispck; int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isc_clk_cleanup (struct isc_device*) ; 
 int /*<<< orphan*/  isc_subdev_cleanup (struct isc_device*) ; 
 struct isc_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int atmel_isc_remove(struct platform_device *pdev)
{
	struct isc_device *isc = platform_get_drvdata(pdev);

	pm_runtime_disable(&pdev->dev);

	isc_subdev_cleanup(isc);

	v4l2_device_unregister(&isc->v4l2_dev);

	clk_disable_unprepare(isc->ispck);
	clk_disable_unprepare(isc->hclock);

	isc_clk_cleanup(isc);

	return 0;
}