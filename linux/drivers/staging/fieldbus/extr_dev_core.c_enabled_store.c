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
struct fieldbus_dev {int (* simple_enable_set ) (struct fieldbus_dev*,int) ;} ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ENOTSUPP ; 
 struct fieldbus_dev* dev_get_drvdata (struct device*) ; 
 int kstrtobool (char const*,int*) ; 
 int stub1 (struct fieldbus_dev*,int) ; 

__attribute__((used)) static ssize_t enabled_store(struct device *dev, struct device_attribute *attr,
			     const char *buf, size_t n)
{
	struct fieldbus_dev *fb = dev_get_drvdata(dev);
	bool value;
	int ret;

	if (!fb->simple_enable_set)
		return -ENOTSUPP;
	ret = kstrtobool(buf, &value);
	if (ret)
		return ret;
	ret = fb->simple_enable_set(fb, value);
	if (ret < 0)
		return ret;
	return n;
}