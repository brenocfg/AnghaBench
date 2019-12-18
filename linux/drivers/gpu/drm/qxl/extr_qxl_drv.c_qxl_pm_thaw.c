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
struct drm_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct drm_device* dev_get_drvdata (struct device*) ; 
 int qxl_drm_resume (struct drm_device*,int) ; 

__attribute__((used)) static int qxl_pm_thaw(struct device *dev)
{
	struct drm_device *drm_dev = dev_get_drvdata(dev);

	return qxl_drm_resume(drm_dev, true);
}