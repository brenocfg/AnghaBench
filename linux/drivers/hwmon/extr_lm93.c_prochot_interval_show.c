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
typedef  int u8 ;
struct lm93_data {int prochot_interval; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int LM93_INTERVAL_FROM_REG (int) ; 
 struct lm93_data* lm93_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t prochot_interval_show(struct device *dev,
				     struct device_attribute *attr, char *buf)
{
	int nr = (to_sensor_dev_attr(attr))->index;
	struct lm93_data *data = lm93_update_device(dev);
	u8 tmp;
	if (nr == 1)
		tmp = (data->prochot_interval & 0xf0) >> 4;
	else
		tmp = data->prochot_interval & 0x0f;
	return sprintf(buf, "%d\n", LM93_INTERVAL_FROM_REG(tmp));
}