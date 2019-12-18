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
struct pmbus_label {char* label; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 
 struct pmbus_label* to_pmbus_label (struct device_attribute*) ; 

__attribute__((used)) static ssize_t pmbus_show_label(struct device *dev,
				struct device_attribute *da, char *buf)
{
	struct pmbus_label *label = to_pmbus_label(da);

	return snprintf(buf, PAGE_SIZE, "%s\n", label->label);
}