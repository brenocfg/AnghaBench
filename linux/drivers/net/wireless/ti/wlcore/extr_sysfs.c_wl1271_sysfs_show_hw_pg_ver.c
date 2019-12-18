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
struct wl1271 {scalar_t__ hw_pg_ver; int /*<<< orphan*/  mutex; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct wl1271* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static ssize_t wl1271_sysfs_show_hw_pg_ver(struct device *dev,
					   struct device_attribute *attr,
					   char *buf)
{
	struct wl1271 *wl = dev_get_drvdata(dev);
	ssize_t len;

	len = PAGE_SIZE;

	mutex_lock(&wl->mutex);
	if (wl->hw_pg_ver >= 0)
		len = snprintf(buf, len, "%d\n", wl->hw_pg_ver);
	else
		len = snprintf(buf, len, "n/a\n");
	mutex_unlock(&wl->mutex);

	return len;
}