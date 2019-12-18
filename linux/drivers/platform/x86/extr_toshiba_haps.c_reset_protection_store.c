#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct toshiba_haps_dev {TYPE_1__* acpi_dev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int EINVAL ; 
 struct toshiba_haps_dev* dev_get_drvdata (struct device*) ; 
 int kstrtoint (char const*,int /*<<< orphan*/ ,int*) ; 
 int toshiba_haps_reset_protection (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t reset_protection_store(struct device *dev,
				      struct device_attribute *attr,
				      const char *buf, size_t count)
{
	struct toshiba_haps_dev *haps = dev_get_drvdata(dev);
	int reset;
	int ret;

	ret = kstrtoint(buf, 0, &reset);
	if (ret)
		return ret;
	/* The only accepted value is 1 */
	if (reset != 1)
		return -EINVAL;

	/* Reset the protection interface */
	ret = toshiba_haps_reset_protection(haps->acpi_dev->handle);
	if (ret != 0)
		return ret;

	return count;
}