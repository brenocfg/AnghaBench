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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int field; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dmi_get_system_info (int) ; 
 int scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* to_dmi_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t sys_dmi_field_show(struct device *dev,
				  struct device_attribute *attr,
				  char *page)
{
	int field = to_dmi_dev_attr(attr)->field;
	ssize_t len;
	len = scnprintf(page, PAGE_SIZE, "%s\n", dmi_get_system_info(field));
	page[len-1] = '\n';
	return len;
}