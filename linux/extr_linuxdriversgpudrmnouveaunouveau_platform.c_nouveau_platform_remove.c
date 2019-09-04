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
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_drm_device_remove (struct drm_device*) ; 
 struct drm_device* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int nouveau_platform_remove(struct platform_device *pdev)
{
	struct drm_device *dev = platform_get_drvdata(pdev);
	nouveau_drm_device_remove(dev);
	return 0;
}