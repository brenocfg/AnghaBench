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
struct aspeed_wdt {scalar_t__ base; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  WDT_CLEAR_TIMEOUT_AND_BOOT_CODE_SELECTION ; 
 scalar_t__ WDT_CLEAR_TIMEOUT_STATUS ; 
 struct aspeed_wdt* dev_get_drvdata (struct device*) ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static ssize_t access_cs0_store(struct device *dev,
				struct device_attribute *attr, const char *buf,
				size_t size)
{
	struct aspeed_wdt *wdt = dev_get_drvdata(dev);
	unsigned long val;

	if (kstrtoul(buf, 10, &val))
		return -EINVAL;

	if (val)
		writel(WDT_CLEAR_TIMEOUT_AND_BOOT_CODE_SELECTION,
		       wdt->base + WDT_CLEAR_TIMEOUT_STATUS);

	return size;
}