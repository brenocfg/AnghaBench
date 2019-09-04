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
struct vt8231_data {int valid; int* in; int* in_min; int* in_max; int* fan; int* fan_min; int* temp; int* temp_max; int* temp_min; int* fan_div; int alarms; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; int /*<<< orphan*/  uch_config; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ ISTEMP (int,int /*<<< orphan*/ ) ; 
 scalar_t__ ISVOLT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VT8231_REG_ALARM1 ; 
 int /*<<< orphan*/  VT8231_REG_ALARM2 ; 
 int /*<<< orphan*/  VT8231_REG_FAN (int) ; 
 int /*<<< orphan*/  VT8231_REG_FANDIV ; 
 int /*<<< orphan*/  VT8231_REG_FAN_MIN (int) ; 
 int /*<<< orphan*/  VT8231_REG_TEMP_LOW01 ; 
 int /*<<< orphan*/  VT8231_REG_TEMP_LOW25 ; 
 struct vt8231_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * regtemp ; 
 int /*<<< orphan*/ * regtempmax ; 
 int /*<<< orphan*/ * regtempmin ; 
 int /*<<< orphan*/ * regvolt ; 
 int /*<<< orphan*/ * regvoltmax ; 
 int /*<<< orphan*/ * regvoltmin ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 int vt8231_read_value (struct vt8231_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct vt8231_data *vt8231_update_device(struct device *dev)
{
	struct vt8231_data *data = dev_get_drvdata(dev);
	int i;
	u16 low;

	mutex_lock(&data->update_lock);

	if (time_after(jiffies, data->last_updated + HZ + HZ / 2)
	    || !data->valid) {
		for (i = 0; i < 6; i++) {
			if (ISVOLT(i, data->uch_config)) {
				data->in[i] = vt8231_read_value(data,
						regvolt[i]);
				data->in_min[i] = vt8231_read_value(data,
						regvoltmin[i]);
				data->in_max[i] = vt8231_read_value(data,
						regvoltmax[i]);
			}
		}
		for (i = 0; i < 2; i++) {
			data->fan[i] = vt8231_read_value(data,
						VT8231_REG_FAN(i));
			data->fan_min[i] = vt8231_read_value(data,
						VT8231_REG_FAN_MIN(i));
		}

		low = vt8231_read_value(data, VT8231_REG_TEMP_LOW01);
		low = (low >> 6) | ((low & 0x30) >> 2)
		    | (vt8231_read_value(data, VT8231_REG_TEMP_LOW25) << 4);
		for (i = 0; i < 6; i++) {
			if (ISTEMP(i, data->uch_config)) {
				data->temp[i] = (vt8231_read_value(data,
						       regtemp[i]) << 2)
						| ((low >> (2 * i)) & 0x03);
				data->temp_max[i] = vt8231_read_value(data,
						      regtempmax[i]);
				data->temp_min[i] = vt8231_read_value(data,
						      regtempmin[i]);
			}
		}

		i = vt8231_read_value(data, VT8231_REG_FANDIV);
		data->fan_div[0] = (i >> 4) & 0x03;
		data->fan_div[1] = i >> 6;
		data->alarms = vt8231_read_value(data, VT8231_REG_ALARM1) |
			(vt8231_read_value(data, VT8231_REG_ALARM2) << 8);

		/* Set alarm flags correctly */
		if (!data->fan[0] && data->fan_min[0])
			data->alarms |= 0x40;
		else if (data->fan[0] && !data->fan_min[0])
			data->alarms &= ~0x40;

		if (!data->fan[1] && data->fan_min[1])
			data->alarms |= 0x80;
		else if (data->fan[1] && !data->fan_min[1])
			data->alarms &= ~0x80;

		data->last_updated = jiffies;
		data->valid = 1;
	}

	mutex_unlock(&data->update_lock);

	return data;
}