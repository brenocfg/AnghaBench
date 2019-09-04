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
struct venc_state {int dummy; } ;
struct platform_device {int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct venc_state* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/ ,char*) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int venc_device_get(struct device *dev, void *data)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct venc_state **venc = data;

	if (strstr(pdev->name, "vpbe-venc") != NULL)
		*venc = platform_get_drvdata(pdev);

	return 0;
}