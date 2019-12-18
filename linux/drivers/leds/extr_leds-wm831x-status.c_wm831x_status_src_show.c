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
 int ARRAY_SIZE (char**) ; 
 struct led_classdev* dev_get_drvdata (struct device*) ; 
 char** led_src_texts ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ sprintf (char*,char*,...) ; 
 struct wm831x_status* to_wm831x_status (struct led_classdev*) ; 

__attribute__((used)) static ssize_t wm831x_status_src_show(struct device *dev,
				      struct device_attribute *attr, char *buf)
{
	struct led_classdev *led_cdev = dev_get_drvdata(dev);
	struct wm831x_status *led = to_wm831x_status(led_cdev);
	int i;
	ssize_t ret = 0;

	mutex_lock(&led->mutex);

	for (i = 0; i < ARRAY_SIZE(led_src_texts); i++)
		if (i == led->src)
			ret += sprintf(&buf[ret], "[%s] ", led_src_texts[i]);
		else
			ret += sprintf(&buf[ret], "%s ", led_src_texts[i]);

	mutex_unlock(&led->mutex);

	ret += sprintf(&buf[ret], "\n");

	return ret;
}