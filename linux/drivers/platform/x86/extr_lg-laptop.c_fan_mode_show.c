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
struct TYPE_2__ {int value; } ;
union acpi_object {scalar_t__ type; TYPE_1__ integer; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  WM_FAN_MODE ; 
 int /*<<< orphan*/  WM_GET ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 
 union acpi_object* lg_wmab (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,unsigned int) ; 

__attribute__((used)) static ssize_t fan_mode_show(struct device *dev,
			     struct device_attribute *attr, char *buffer)
{
	unsigned int status;
	union acpi_object *r;

	r = lg_wmab(WM_FAN_MODE, WM_GET, 0);
	if (!r)
		return -EIO;

	if (r->type != ACPI_TYPE_INTEGER) {
		kfree(r);
		return -EIO;
	}

	status = r->integer.value & 0x01;
	kfree(r);

	return snprintf(buffer, PAGE_SIZE, "%d\n", status);
}