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
struct sensor_device_attribute_2 {int index; int nr; } ;
struct dme1737_data {int alarms; int /*<<< orphan*/ * in_nominal; int /*<<< orphan*/ * in_max; int /*<<< orphan*/ * in_min; int /*<<< orphan*/ * in; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int* DME1737_BIT_ALARM_IN ; 
 int IN_FROM_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
#define  SYS_IN_ALARM 131 
#define  SYS_IN_INPUT 130 
#define  SYS_IN_MAX 129 
#define  SYS_IN_MIN 128 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 struct dme1737_data* dme1737_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t show_in(struct device *dev, struct device_attribute *attr,
		       char *buf)
{
	struct dme1737_data *data = dme1737_update_device(dev);
	struct sensor_device_attribute_2
		*sensor_attr_2 = to_sensor_dev_attr_2(attr);
	int ix = sensor_attr_2->index;
	int fn = sensor_attr_2->nr;
	int res;

	switch (fn) {
	case SYS_IN_INPUT:
		res = IN_FROM_REG(data->in[ix], data->in_nominal[ix], 16);
		break;
	case SYS_IN_MIN:
		res = IN_FROM_REG(data->in_min[ix], data->in_nominal[ix], 8);
		break;
	case SYS_IN_MAX:
		res = IN_FROM_REG(data->in_max[ix], data->in_nominal[ix], 8);
		break;
	case SYS_IN_ALARM:
		res = (data->alarms >> DME1737_BIT_ALARM_IN[ix]) & 0x01;
		break;
	default:
		res = 0;
		dev_dbg(dev, "Unknown function %d.\n", fn);
	}

	return sprintf(buf, "%d\n", res);
}