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
struct k10temp_data {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct k10temp_data* dev_get_drvdata (struct device*) ; 
 unsigned int get_raw_temp (struct k10temp_data*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 

__attribute__((used)) static ssize_t temp2_input_show(struct device *dev,
				struct device_attribute *devattr, char *buf)
{
	struct k10temp_data *data = dev_get_drvdata(dev);
	unsigned int temp = get_raw_temp(data);

	return sprintf(buf, "%u\n", temp);
}