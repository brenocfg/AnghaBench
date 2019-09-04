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
struct vt1211_data {int alarms; int /*<<< orphan*/ * temp_hyst; int /*<<< orphan*/ * temp_max; int /*<<< orphan*/ * temp; } ;
struct sensor_device_attribute_2 {int index; int nr; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
#define  SHOW_SET_TEMP_MAX 131 
#define  SHOW_SET_TEMP_MAX_HYST 130 
#define  SHOW_TEMP_ALARM 129 
#define  SHOW_TEMP_INPUT 128 
 int TEMP_FROM_REG (int,int /*<<< orphan*/ ) ; 
 int* bitalarmtemp ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 
 struct vt1211_data* vt1211_update_device (struct device*) ; 

__attribute__((used)) static ssize_t show_temp(struct device *dev, struct device_attribute *attr,
			 char *buf)
{
	struct vt1211_data *data = vt1211_update_device(dev);
	struct sensor_device_attribute_2 *sensor_attr_2 =
						to_sensor_dev_attr_2(attr);
	int ix = sensor_attr_2->index;
	int fn = sensor_attr_2->nr;
	int res;

	switch (fn) {
	case SHOW_TEMP_INPUT:
		res = TEMP_FROM_REG(ix, data->temp[ix]);
		break;
	case SHOW_SET_TEMP_MAX:
		res = TEMP_FROM_REG(ix, data->temp_max[ix]);
		break;
	case SHOW_SET_TEMP_MAX_HYST:
		res = TEMP_FROM_REG(ix, data->temp_hyst[ix]);
		break;
	case SHOW_TEMP_ALARM:
		res = (data->alarms >> bitalarmtemp[ix]) & 1;
		break;
	default:
		res = 0;
		dev_dbg(dev, "Unknown attr fetch (%d)\n", fn);
	}

	return sprintf(buf, "%d\n", res);
}