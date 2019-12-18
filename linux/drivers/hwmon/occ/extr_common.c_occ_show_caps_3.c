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
typedef  unsigned long long u64 ;
struct sensor_device_attribute_2 {int index; int nr; } ;
struct TYPE_2__ {scalar_t__ data; } ;
struct occ_sensors {TYPE_1__ caps; } ;
struct occ {struct occ_sensors sensors; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct caps_sensor_3 {unsigned long long user_source; int /*<<< orphan*/  user; int /*<<< orphan*/  hard_min; int /*<<< orphan*/  max; int /*<<< orphan*/  n_cap; int /*<<< orphan*/  system_power; int /*<<< orphan*/  cap; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PAGE_SIZE ; 
 struct occ* dev_get_drvdata (struct device*) ; 
 unsigned long long get_unaligned_be16 (int /*<<< orphan*/ *) ; 
 int occ_update_response (struct occ*) ; 
 int snprintf (char*,scalar_t__,char*,...) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t occ_show_caps_3(struct device *dev,
			       struct device_attribute *attr, char *buf)
{
	int rc;
	u64 val = 0;
	struct caps_sensor_3 *caps;
	struct occ *occ = dev_get_drvdata(dev);
	struct occ_sensors *sensors = &occ->sensors;
	struct sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);

	rc = occ_update_response(occ);
	if (rc)
		return rc;

	caps = ((struct caps_sensor_3 *)sensors->caps.data) + sattr->index;

	switch (sattr->nr) {
	case 0:
		return snprintf(buf, PAGE_SIZE - 1, "system\n");
	case 1:
		val = get_unaligned_be16(&caps->cap) * 1000000ULL;
		break;
	case 2:
		val = get_unaligned_be16(&caps->system_power) * 1000000ULL;
		break;
	case 3:
		val = get_unaligned_be16(&caps->n_cap) * 1000000ULL;
		break;
	case 4:
		val = get_unaligned_be16(&caps->max) * 1000000ULL;
		break;
	case 5:
		val = get_unaligned_be16(&caps->hard_min) * 1000000ULL;
		break;
	case 6:
		val = get_unaligned_be16(&caps->user) * 1000000ULL;
		break;
	case 7:
		val = caps->user_source;
		break;
	default:
		return -EINVAL;
	}

	return snprintf(buf, PAGE_SIZE - 1, "%llu\n", val);
}