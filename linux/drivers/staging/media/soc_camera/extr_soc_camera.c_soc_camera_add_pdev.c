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
struct soc_camera_device {int dummy; } ;
struct soc_camera_async_client {struct platform_device* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  driver; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int platform_device_add (struct platform_device*) ; 
 struct soc_camera_device* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static struct soc_camera_device *soc_camera_add_pdev(struct soc_camera_async_client *sasc)
{
	struct platform_device *pdev = sasc->pdev;
	int ret;

	ret = platform_device_add(pdev);
	if (ret < 0 || !pdev->dev.driver)
		return NULL;

	return platform_get_drvdata(pdev);
}