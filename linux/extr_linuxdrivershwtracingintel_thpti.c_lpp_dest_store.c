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
struct pti_device {int lpp_dest_mask; int lpp_dest; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int BIT (int) ; 
 size_t EINVAL ; 
 struct pti_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/ * lpp_dest_str ; 
 scalar_t__ sysfs_streq (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t lpp_dest_store(struct device *dev, struct device_attribute *attr,
			      const char *buf, size_t size)
{
	struct pti_device *pti = dev_get_drvdata(dev);
	ssize_t ret = -EINVAL;
	int i;

	for (i = 0; i < ARRAY_SIZE(lpp_dest_str); i++)
		if (sysfs_streq(buf, lpp_dest_str[i]))
			break;

	if (i < ARRAY_SIZE(lpp_dest_str) && pti->lpp_dest_mask & BIT(i)) {
		pti->lpp_dest = i;
		ret = size;
	}

	return ret;
}