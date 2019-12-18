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
typedef  int u16 ;
struct w83795_data {int tol_speed; int /*<<< orphan*/ * target_speed; } ;
struct sensor_device_attribute_2 {int nr; int index; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
#define  FANIN_TARGET 129 
#define  FANIN_TOL 128 
 int fan_from_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 
 struct w83795_data* w83795_update_pwm_config (struct device*) ; 

__attribute__((used)) static ssize_t
show_fanin(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct w83795_data *data = w83795_update_pwm_config(dev);
	struct sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	int nr = sensor_attr->nr;
	int index = sensor_attr->index;
	u16 tmp = 0;

	switch (nr) {
	case FANIN_TARGET:
		tmp = fan_from_reg(data->target_speed[index]);
		break;
	case FANIN_TOL:
		tmp = data->tol_speed;
		break;
	}

	return sprintf(buf, "%u\n", tmp);
}