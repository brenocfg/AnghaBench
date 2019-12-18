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
struct led_classdev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct led_classdev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  pattern_trig_store_patterns (struct led_classdev*,char const*,int /*<<< orphan*/ *,size_t,int) ; 

__attribute__((used)) static ssize_t hw_pattern_store(struct device *dev,
				struct device_attribute *attr,
				const char *buf, size_t count)
{
	struct led_classdev *led_cdev = dev_get_drvdata(dev);

	return pattern_trig_store_patterns(led_cdev, buf, NULL, count, true);
}