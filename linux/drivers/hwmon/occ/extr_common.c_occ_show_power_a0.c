#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct sensor_device_attribute_2 {int index; int nr; } ;
struct TYPE_10__ {int /*<<< orphan*/  value; int /*<<< orphan*/  update_tag; int /*<<< orphan*/  accumulator; } ;
struct TYPE_9__ {int /*<<< orphan*/  value; int /*<<< orphan*/  update_tag; int /*<<< orphan*/  accumulator; } ;
struct TYPE_8__ {int /*<<< orphan*/  value; int /*<<< orphan*/  update_tag; int /*<<< orphan*/  accumulator; } ;
struct TYPE_7__ {int /*<<< orphan*/  value; int /*<<< orphan*/  update_tag; int /*<<< orphan*/  accumulator; } ;
struct power_sensor_a0 {TYPE_5__ vdn; int /*<<< orphan*/  sensor_id; TYPE_4__ vdd; TYPE_3__ proc; TYPE_2__ system; } ;
struct TYPE_6__ {scalar_t__ data; } ;
struct occ_sensors {TYPE_1__ power; } ;
struct occ {int powr_sample_time_us; struct occ_sensors sensors; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PAGE_SIZE ; 
 struct occ* dev_get_drvdata (struct device*) ; 
 unsigned long long get_unaligned_be16 (int /*<<< orphan*/ *) ; 
 int get_unaligned_be32 (int /*<<< orphan*/ *) ; 
 int occ_get_powr_avg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int occ_update_response (struct occ*) ; 
 int snprintf (char*,scalar_t__,char*,int) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t occ_show_power_a0(struct device *dev,
				 struct device_attribute *attr, char *buf)
{
	int rc;
	u64 val = 0;
	struct power_sensor_a0 *power;
	struct occ *occ = dev_get_drvdata(dev);
	struct occ_sensors *sensors = &occ->sensors;
	struct sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);

	rc = occ_update_response(occ);
	if (rc)
		return rc;

	power = ((struct power_sensor_a0 *)sensors->power.data) + sattr->index;

	switch (sattr->nr) {
	case 0:
		return snprintf(buf, PAGE_SIZE - 1, "%u_system\n",
				get_unaligned_be32(&power->sensor_id));
	case 1:
		val = occ_get_powr_avg(&power->system.accumulator,
				       &power->system.update_tag);
		break;
	case 2:
		val = (u64)get_unaligned_be32(&power->system.update_tag) *
			   occ->powr_sample_time_us;
		break;
	case 3:
		val = get_unaligned_be16(&power->system.value) * 1000000ULL;
		break;
	case 4:
		return snprintf(buf, PAGE_SIZE - 1, "%u_proc\n",
				get_unaligned_be32(&power->sensor_id));
	case 5:
		val = occ_get_powr_avg(&power->proc.accumulator,
				       &power->proc.update_tag);
		break;
	case 6:
		val = (u64)get_unaligned_be32(&power->proc.update_tag) *
			   occ->powr_sample_time_us;
		break;
	case 7:
		val = get_unaligned_be16(&power->proc.value) * 1000000ULL;
		break;
	case 8:
		return snprintf(buf, PAGE_SIZE - 1, "%u_vdd\n",
				get_unaligned_be32(&power->sensor_id));
	case 9:
		val = occ_get_powr_avg(&power->vdd.accumulator,
				       &power->vdd.update_tag);
		break;
	case 10:
		val = (u64)get_unaligned_be32(&power->vdd.update_tag) *
			   occ->powr_sample_time_us;
		break;
	case 11:
		val = get_unaligned_be16(&power->vdd.value) * 1000000ULL;
		break;
	case 12:
		return snprintf(buf, PAGE_SIZE - 1, "%u_vdn\n",
				get_unaligned_be32(&power->sensor_id));
	case 13:
		val = occ_get_powr_avg(&power->vdn.accumulator,
				       &power->vdn.update_tag);
		break;
	case 14:
		val = (u64)get_unaligned_be32(&power->vdn.update_tag) *
			   occ->powr_sample_time_us;
		break;
	case 15:
		val = get_unaligned_be16(&power->vdn.value) * 1000000ULL;
		break;
	default:
		return -EINVAL;
	}

	return snprintf(buf, PAGE_SIZE - 1, "%llu\n", val);
}