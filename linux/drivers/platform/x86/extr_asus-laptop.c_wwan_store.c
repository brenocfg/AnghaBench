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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  METHOD_WWAN ; 
 struct asus_laptop* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sysfs_acpi_set (struct asus_laptop*,char const*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t wwan_store(struct device *dev, struct device_attribute *attr,
			  const char *buf, size_t count)
{
	struct asus_laptop *asus = dev_get_drvdata(dev);

	return sysfs_acpi_set(asus, buf, count, METHOD_WWAN);
}