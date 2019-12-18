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
struct td043mtea1_panel {int vmirror; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct td043mtea1_panel* dev_get_drvdata (struct device*) ; 
 int kstrtoint (char const*,int /*<<< orphan*/ ,int*) ; 
 int td043mtea1_write_mirror (struct td043mtea1_panel*) ; 

__attribute__((used)) static ssize_t vmirror_store(struct device *dev, struct device_attribute *attr,
			     const char *buf, size_t count)
{
	struct td043mtea1_panel *lcd = dev_get_drvdata(dev);
	int val;
	int ret;

	ret = kstrtoint(buf, 0, &val);
	if (ret < 0)
		return ret;

	lcd->vmirror = !!val;

	ret = td043mtea1_write_mirror(lcd);
	if (ret < 0)
		return ret;

	return count;
}