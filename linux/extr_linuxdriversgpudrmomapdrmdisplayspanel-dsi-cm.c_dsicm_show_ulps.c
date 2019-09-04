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
struct panel_drv_data {unsigned int ulps_enabled; int /*<<< orphan*/  lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct panel_drv_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,unsigned int) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static ssize_t dsicm_show_ulps(struct device *dev,
		struct device_attribute *attr,
		char *buf)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct panel_drv_data *ddata = platform_get_drvdata(pdev);
	unsigned int t;

	mutex_lock(&ddata->lock);
	t = ddata->ulps_enabled;
	mutex_unlock(&ddata->lock);

	return snprintf(buf, PAGE_SIZE, "%u\n", t);
}