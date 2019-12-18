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
typedef  int u32 ;
struct sensor_device_attribute {int index; } ;
struct k10temp_data {int /*<<< orphan*/  pdev; int /*<<< orphan*/  (* read_htcreg ) (int /*<<< orphan*/ ,int*) ;} ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct k10temp_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int*) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t temp_crit_show(struct device *dev,
			      struct device_attribute *devattr, char *buf)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	struct k10temp_data *data = dev_get_drvdata(dev);
	int show_hyst = attr->index;
	u32 regval;
	int value;

	data->read_htcreg(data->pdev, &regval);
	value = ((regval >> 16) & 0x7f) * 500 + 52000;
	if (show_hyst)
		value -= ((regval >> 24) & 0xf) * 500;
	return sprintf(buf, "%d\n", value);
}