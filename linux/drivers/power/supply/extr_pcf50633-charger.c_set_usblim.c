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
struct pcf50633_mbc {int /*<<< orphan*/  pcf; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct pcf50633_mbc* dev_get_drvdata (struct device*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  pcf50633_mbc_usb_curlim_set (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static ssize_t set_usblim(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct pcf50633_mbc *mbc = dev_get_drvdata(dev);
	unsigned long ma;
	int ret;

	ret = kstrtoul(buf, 10, &ma);
	if (ret)
		return ret;

	pcf50633_mbc_usb_curlim_set(mbc->pcf, ma);

	return count;
}