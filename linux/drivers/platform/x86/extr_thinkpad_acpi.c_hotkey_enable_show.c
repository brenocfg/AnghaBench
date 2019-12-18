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
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int hotkey_status_get (int*) ; 
 int /*<<< orphan*/  printk_deprecated_attribute (char*,char*) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ssize_t hotkey_enable_show(struct device *dev,
			   struct device_attribute *attr,
			   char *buf)
{
	int res, status;

	printk_deprecated_attribute("hotkey_enable",
			"Hotkey reporting is always enabled");

	res = hotkey_status_get(&status);
	if (res)
		return res;

	return snprintf(buf, PAGE_SIZE, "%d\n", status);
}