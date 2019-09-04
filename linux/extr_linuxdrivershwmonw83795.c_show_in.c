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
typedef  size_t u8 ;
typedef  int u16 ;
struct w83795_data {int** in; int has_gain; int** in_lsb; } ;
struct sensor_device_attribute_2 {int nr; int index; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
#define  IN_LOW 130 
 size_t IN_LSB_IDX ; 
 size_t IN_LSB_SHIFT ; 
 int** IN_LSB_SHIFT_IDX ; 
#define  IN_MAX 129 
#define  IN_READ 128 
 int in_from_reg (int,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 
 struct w83795_data* w83795_update_device (struct device*) ; 

__attribute__((used)) static ssize_t
show_in(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	int nr = sensor_attr->nr;
	int index = sensor_attr->index;
	struct w83795_data *data = w83795_update_device(dev);
	u16 val = data->in[index][nr];
	u8 lsb_idx;

	switch (nr) {
	case IN_READ:
		/* calculate this value again by sensors as sensors3.conf */
		if ((index >= 17) &&
		    !((data->has_gain >> (index - 17)) & 1))
			val *= 8;
		break;
	case IN_MAX:
	case IN_LOW:
		lsb_idx = IN_LSB_SHIFT_IDX[index][IN_LSB_IDX];
		val <<= 2;
		val |= (data->in_lsb[lsb_idx][nr] >>
			IN_LSB_SHIFT_IDX[index][IN_LSB_SHIFT]) & 0x03;
		if ((index >= 17) &&
		    !((data->has_gain >> (index - 17)) & 1))
			val *= 8;
		break;
	}
	val = in_from_reg(index, val);

	return sprintf(buf, "%d\n", val);
}