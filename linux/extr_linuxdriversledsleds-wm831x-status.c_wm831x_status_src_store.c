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
struct wm831x_status {int src; int /*<<< orphan*/  mutex; } ;
struct led_classdev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 struct led_classdev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  led_src_texts ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sysfs_match_string (int /*<<< orphan*/ ,char const*) ; 
 struct wm831x_status* to_wm831x_status (struct led_classdev*) ; 
 int /*<<< orphan*/  wm831x_status_set (struct wm831x_status*) ; 

__attribute__((used)) static ssize_t wm831x_status_src_store(struct device *dev,
				       struct device_attribute *attr,
				       const char *buf, size_t size)
{
	struct led_classdev *led_cdev = dev_get_drvdata(dev);
	struct wm831x_status *led = to_wm831x_status(led_cdev);
	int i;

	i = sysfs_match_string(led_src_texts, buf);
	if (i >= 0) {
		mutex_lock(&led->mutex);
		led->src = i;
		mutex_unlock(&led->mutex);
		wm831x_status_set(led);
	}

	return size;
}