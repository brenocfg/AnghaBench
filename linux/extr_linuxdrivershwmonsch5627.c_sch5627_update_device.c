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
struct sch5627_data {int control; int valid; int* temp; int* fan; int* in; int /*<<< orphan*/  update_lock; void* last_updated; int /*<<< orphan*/  addr; void* last_battery; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct sch5627_data* ERR_PTR (int) ; 
 int HZ ; 
 int SCH5627_NO_FANS ; 
 int SCH5627_NO_IN ; 
 int SCH5627_NO_TEMPS ; 
 int /*<<< orphan*/  SCH5627_REG_CTRL ; 
 int /*<<< orphan*/ * SCH5627_REG_FAN ; 
 int /*<<< orphan*/ * SCH5627_REG_IN_HIGH_NIBBLE ; 
 int /*<<< orphan*/ * SCH5627_REG_IN_LSN ; 
 int /*<<< orphan*/ * SCH5627_REG_IN_MSB ; 
 int /*<<< orphan*/ * SCH5627_REG_TEMP_HIGH_NIBBLE ; 
 int /*<<< orphan*/ * SCH5627_REG_TEMP_LSN ; 
 int /*<<< orphan*/ * SCH5627_REG_TEMP_MSB ; 
 struct sch5627_data* dev_get_drvdata (struct device*) ; 
 void* jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sch56xx_read_virtual_reg12 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sch56xx_read_virtual_reg16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sch56xx_write_virtual_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ time_after (void*,void*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sch5627_data *sch5627_update_device(struct device *dev)
{
	struct sch5627_data *data = dev_get_drvdata(dev);
	struct sch5627_data *ret = data;
	int i, val;

	mutex_lock(&data->update_lock);

	/* Trigger a Vbat voltage measurement every 5 minutes */
	if (time_after(jiffies, data->last_battery + 300 * HZ)) {
		sch56xx_write_virtual_reg(data->addr, SCH5627_REG_CTRL,
					  data->control | 0x10);
		data->last_battery = jiffies;
	}

	/* Cache the values for 1 second */
	if (time_after(jiffies, data->last_updated + HZ) || !data->valid) {
		for (i = 0; i < SCH5627_NO_TEMPS; i++) {
			val = sch56xx_read_virtual_reg12(data->addr,
				SCH5627_REG_TEMP_MSB[i],
				SCH5627_REG_TEMP_LSN[i],
				SCH5627_REG_TEMP_HIGH_NIBBLE[i]);
			if (unlikely(val < 0)) {
				ret = ERR_PTR(val);
				goto abort;
			}
			data->temp[i] = val;
		}

		for (i = 0; i < SCH5627_NO_FANS; i++) {
			val = sch56xx_read_virtual_reg16(data->addr,
							 SCH5627_REG_FAN[i]);
			if (unlikely(val < 0)) {
				ret = ERR_PTR(val);
				goto abort;
			}
			data->fan[i] = val;
		}

		for (i = 0; i < SCH5627_NO_IN; i++) {
			val = sch56xx_read_virtual_reg12(data->addr,
				SCH5627_REG_IN_MSB[i],
				SCH5627_REG_IN_LSN[i],
				SCH5627_REG_IN_HIGH_NIBBLE[i]);
			if (unlikely(val < 0)) {
				ret = ERR_PTR(val);
				goto abort;
			}
			data->in[i] = val;
		}

		data->last_updated = jiffies;
		data->valid = 1;
	}
abort:
	mutex_unlock(&data->update_lock);
	return ret;
}