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
struct td043mtea1_panel {long mode; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 long TPO_R02_NCLK_RISING ; 
 struct td043mtea1_panel* dev_get_drvdata (struct device*) ; 
 int kstrtol (char const*,int /*<<< orphan*/ ,long*) ; 
 int /*<<< orphan*/  td043mtea1_write (struct td043mtea1_panel*,int,long) ; 

__attribute__((used)) static ssize_t mode_store(struct device *dev, struct device_attribute *attr,
			  const char *buf, size_t count)
{
	struct td043mtea1_panel *lcd = dev_get_drvdata(dev);
	long val;
	int ret;

	ret = kstrtol(buf, 0, &val);
	if (ret != 0 || val & ~7)
		return -EINVAL;

	lcd->mode = val;

	val |= TPO_R02_NCLK_RISING;
	td043mtea1_write(lcd, 2, val);

	return count;
}