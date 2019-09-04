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
struct bh1770_chip {unsigned long prox_persistence; } ;
typedef  int ssize_t ;

/* Variables and functions */
 unsigned long BH1770_PROX_MAX_PERSISTENCE ; 
 int EINVAL ; 
 struct bh1770_chip* dev_get_drvdata (struct device*) ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static ssize_t bh1770_prox_persistence_store(struct device *dev,
				struct device_attribute *attr,
				const char *buf, size_t len)
{
	struct bh1770_chip *chip = dev_get_drvdata(dev);
	unsigned long value;
	int ret;

	ret = kstrtoul(buf, 0, &value);
	if (ret)
		return ret;

	if (value > BH1770_PROX_MAX_PERSISTENCE)
		return -EINVAL;

	chip->prox_persistence = value;

	return len;
}