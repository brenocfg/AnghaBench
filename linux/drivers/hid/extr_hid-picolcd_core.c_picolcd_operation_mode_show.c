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
struct picolcd_data {int status; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PICOLCD_BOOTLOADER ; 
 struct picolcd_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t picolcd_operation_mode_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct picolcd_data *data = dev_get_drvdata(dev);

	if (data->status & PICOLCD_BOOTLOADER)
		return snprintf(buf, PAGE_SIZE, "[bootloader] lcd\n");
	else
		return snprintf(buf, PAGE_SIZE, "bootloader [lcd]\n");
}