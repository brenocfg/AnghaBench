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
typedef  union acpi_object {int dummy; } acpi_object ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  WM_READER_MODE ; 
 int /*<<< orphan*/  WM_SET ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 
 int kstrtobool (char const*,int*) ; 
 union acpi_object* lg_wmab (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t reader_mode_store(struct device *dev,
				 struct device_attribute *attr,
				 const char *buffer, size_t count)
{
	bool value;
	union acpi_object *r;
	int ret;

	ret = kstrtobool(buffer, &value);
	if (ret)
		return ret;

	r = lg_wmab(WM_READER_MODE, WM_SET, value);
	if (!r)
		return -EIO;

	kfree(r);
	return count;
}