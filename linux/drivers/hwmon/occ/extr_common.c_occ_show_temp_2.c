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
typedef  int u32 ;
struct temp_sensor_2 {int value; int fru_type; int /*<<< orphan*/  sensor_id; } ;
struct sensor_device_attribute_2 {int index; int nr; } ;
struct TYPE_2__ {scalar_t__ data; } ;
struct occ_sensors {TYPE_1__ temp; } ;
struct occ {struct occ_sensors sensors; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int EREMOTEIO ; 
 int OCC_FRU_TYPE_VRM ; 
 int OCC_TEMP_SENSOR_FAULT ; 
 scalar_t__ PAGE_SIZE ; 
 struct occ* dev_get_drvdata (struct device*) ; 
 int get_unaligned_be32 (int /*<<< orphan*/ *) ; 
 int occ_update_response (struct occ*) ; 
 int snprintf (char*,scalar_t__,char*,int) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t occ_show_temp_2(struct device *dev,
			       struct device_attribute *attr, char *buf)
{
	int rc;
	u32 val = 0;
	struct temp_sensor_2 *temp;
	struct occ *occ = dev_get_drvdata(dev);
	struct occ_sensors *sensors = &occ->sensors;
	struct sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);

	rc = occ_update_response(occ);
	if (rc)
		return rc;

	temp = ((struct temp_sensor_2 *)sensors->temp.data) + sattr->index;

	switch (sattr->nr) {
	case 0:
		val = get_unaligned_be32(&temp->sensor_id);
		break;
	case 1:
		val = temp->value;
		if (val == OCC_TEMP_SENSOR_FAULT)
			return -EREMOTEIO;

		/*
		 * VRM doesn't return temperature, only alarm bit. This
		 * attribute maps to tempX_alarm instead of tempX_input for
		 * VRM
		 */
		if (temp->fru_type != OCC_FRU_TYPE_VRM) {
			/* sensor not ready */
			if (val == 0)
				return -EAGAIN;

			val *= 1000;
		}
		break;
	case 2:
		val = temp->fru_type;
		break;
	case 3:
		val = temp->value == OCC_TEMP_SENSOR_FAULT;
		break;
	default:
		return -EINVAL;
	}

	return snprintf(buf, PAGE_SIZE - 1, "%u\n", val);
}