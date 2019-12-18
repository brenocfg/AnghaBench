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
struct sensor_device_attribute_2 {int index; int nr; } ;
struct TYPE_2__ {scalar_t__ data; } ;
struct occ_sensors {TYPE_1__ extended; } ;
struct occ {struct occ_sensors sensors; } ;
struct extended_sensor {int flags; int* name; int* data; int /*<<< orphan*/  sensor_id; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int EXTN_FLAG_SENSOR_ID ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct occ* dev_get_drvdata (struct device*) ; 
 int get_unaligned_be32 (int /*<<< orphan*/ *) ; 
 int occ_update_response (struct occ*) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,int,...) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t occ_show_extended(struct device *dev,
				 struct device_attribute *attr, char *buf)
{
	int rc;
	struct extended_sensor *extn;
	struct occ *occ = dev_get_drvdata(dev);
	struct occ_sensors *sensors = &occ->sensors;
	struct sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);

	rc = occ_update_response(occ);
	if (rc)
		return rc;

	extn = ((struct extended_sensor *)sensors->extended.data) +
		sattr->index;

	switch (sattr->nr) {
	case 0:
		if (extn->flags & EXTN_FLAG_SENSOR_ID)
			rc = snprintf(buf, PAGE_SIZE - 1, "%u",
				      get_unaligned_be32(&extn->sensor_id));
		else
			rc = snprintf(buf, PAGE_SIZE - 1, "%02x%02x%02x%02x\n",
				      extn->name[0], extn->name[1],
				      extn->name[2], extn->name[3]);
		break;
	case 1:
		rc = snprintf(buf, PAGE_SIZE - 1, "%02x\n", extn->flags);
		break;
	case 2:
		rc = snprintf(buf, PAGE_SIZE - 1, "%02x%02x%02x%02x%02x%02x\n",
			      extn->data[0], extn->data[1], extn->data[2],
			      extn->data[3], extn->data[4], extn->data[5]);
		break;
	default:
		return -EINVAL;
	}

	return rc;
}