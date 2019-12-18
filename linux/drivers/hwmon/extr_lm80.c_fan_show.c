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
struct lm80_data {int /*<<< orphan*/ * fan_div; int /*<<< orphan*/ ** fan; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int index; int nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_FROM_REG (int /*<<< orphan*/ ) ; 
 int FAN_FROM_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct lm80_data*) ; 
 int /*<<< orphan*/  PTR_ERR (struct lm80_data*) ; 
 struct lm80_data* lm80_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 TYPE_1__* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t fan_show(struct device *dev, struct device_attribute *attr,
			char *buf)
{
	int index = to_sensor_dev_attr_2(attr)->index;
	int nr = to_sensor_dev_attr_2(attr)->nr;
	struct lm80_data *data = lm80_update_device(dev);
	if (IS_ERR(data))
		return PTR_ERR(data);
	return sprintf(buf, "%d\n", FAN_FROM_REG(data->fan[nr][index],
		       DIV_FROM_REG(data->fan_div[index])));
}