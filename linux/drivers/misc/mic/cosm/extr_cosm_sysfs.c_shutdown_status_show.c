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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct cosm_device {size_t shutdown_status; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 size_t MIC_STATUS_LAST ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/ * cosm_shutdown_status_string ; 
 struct cosm_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t shutdown_status_show(struct device *dev,
				    struct device_attribute *attr, char *buf)
{
	struct cosm_device *cdev = dev_get_drvdata(dev);

	if (!cdev || cdev->shutdown_status >= MIC_STATUS_LAST)
		return -EINVAL;

	return scnprintf(buf, PAGE_SIZE, "%s\n",
		cosm_shutdown_status_string[cdev->shutdown_status]);
}