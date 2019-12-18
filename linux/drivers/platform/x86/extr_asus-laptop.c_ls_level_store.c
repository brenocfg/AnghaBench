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
struct asus_laptop {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  asus_als_level (struct asus_laptop*,int) ; 
 struct asus_laptop* dev_get_drvdata (struct device*) ; 
 int kstrtoint (char const*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static ssize_t ls_level_store(struct device *dev, struct device_attribute *attr,
			      const char *buf, size_t count)
{
	struct asus_laptop *asus = dev_get_drvdata(dev);
	int rv, value;

	rv = kstrtoint(buf, 0, &value);
	if (rv < 0)
		return rv;

	value = (0 < value) ? ((15 < value) ? 15 : value) : 0;
	/* 0 <= value <= 15 */
	asus_als_level(asus, value);

	return count;
}