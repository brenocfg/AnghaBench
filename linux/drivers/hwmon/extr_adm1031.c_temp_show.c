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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adm1031_data {int* ext_temp; int /*<<< orphan*/ * temp; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int TEMP_FROM_REG_EXT (int /*<<< orphan*/ ,int) ; 
 struct adm1031_data* adm1031_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t temp_show(struct device *dev, struct device_attribute *attr,
			 char *buf)
{
	int nr = to_sensor_dev_attr(attr)->index;
	struct adm1031_data *data = adm1031_update_device(dev);
	int ext;
	ext = nr == 0 ?
	    ((data->ext_temp[nr] >> 6) & 0x3) * 2 :
	    (((data->ext_temp[nr] >> ((nr - 1) * 3)) & 7));
	return sprintf(buf, "%d\n", TEMP_FROM_REG_EXT(data->temp[nr], ext));
}