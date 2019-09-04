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
struct mtd_info {unsigned int bitflip_threshold; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct mtd_info* dev_get_drvdata (struct device*) ; 
 int kstrtouint (char const*,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static ssize_t mtd_bitflip_threshold_store(struct device *dev,
					   struct device_attribute *attr,
					   const char *buf, size_t count)
{
	struct mtd_info *mtd = dev_get_drvdata(dev);
	unsigned int bitflip_threshold;
	int retval;

	retval = kstrtouint(buf, 0, &bitflip_threshold);
	if (retval)
		return retval;

	mtd->bitflip_threshold = bitflip_threshold;
	return count;
}