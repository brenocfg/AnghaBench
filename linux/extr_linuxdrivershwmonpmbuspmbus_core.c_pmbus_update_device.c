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
struct pmbus_sensor {int /*<<< orphan*/  reg; int /*<<< orphan*/  page; int /*<<< orphan*/  data; scalar_t__ update; struct pmbus_sensor* next; } ;
struct pmbus_driver_info {int pages; int* func; } ;
struct pmbus_data {int valid; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; struct pmbus_sensor* sensors; void** status; void* (* read_status ) (struct i2c_client*,int) ;struct pmbus_driver_info* info; } ;
struct i2c_client {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
struct _pmbus_status {int func; int base; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct _pmbus_status*) ; 
 scalar_t__ HZ ; 
 int PB_STATUS_BASE ; 
 size_t PB_STATUS_INPUT_BASE ; 
 size_t PB_STATUS_VMON_BASE ; 
 int PMBUS_HAVE_STATUS_INPUT ; 
 int PMBUS_HAVE_STATUS_VMON ; 
 int /*<<< orphan*/  PMBUS_STATUS_INPUT ; 
 int /*<<< orphan*/  PMBUS_VIRT_STATUS_VMON ; 
 void* _pmbus_read_byte_data (struct i2c_client*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _pmbus_read_word_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pmbus_data* i2c_get_clientdata (struct i2c_client*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmbus_clear_faults (struct i2c_client*) ; 
 struct _pmbus_status* pmbus_status ; 
 void* stub1 (struct i2c_client*,int) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct pmbus_data *pmbus_update_device(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev->parent);
	struct pmbus_data *data = i2c_get_clientdata(client);
	const struct pmbus_driver_info *info = data->info;
	struct pmbus_sensor *sensor;

	mutex_lock(&data->update_lock);
	if (time_after(jiffies, data->last_updated + HZ) || !data->valid) {
		int i, j;

		for (i = 0; i < info->pages; i++) {
			data->status[PB_STATUS_BASE + i]
			    = data->read_status(client, i);
			for (j = 0; j < ARRAY_SIZE(pmbus_status); j++) {
				struct _pmbus_status *s = &pmbus_status[j];

				if (!(info->func[i] & s->func))
					continue;
				data->status[s->base + i]
					= _pmbus_read_byte_data(client, i,
								s->reg);
			}
		}

		if (info->func[0] & PMBUS_HAVE_STATUS_INPUT)
			data->status[PB_STATUS_INPUT_BASE]
			  = _pmbus_read_byte_data(client, 0,
						  PMBUS_STATUS_INPUT);

		if (info->func[0] & PMBUS_HAVE_STATUS_VMON)
			data->status[PB_STATUS_VMON_BASE]
			  = _pmbus_read_byte_data(client, 0,
						  PMBUS_VIRT_STATUS_VMON);

		for (sensor = data->sensors; sensor; sensor = sensor->next) {
			if (!data->valid || sensor->update)
				sensor->data
				    = _pmbus_read_word_data(client,
							    sensor->page,
							    sensor->reg);
		}
		pmbus_clear_faults(client);
		data->last_updated = jiffies;
		data->valid = 1;
	}
	mutex_unlock(&data->update_lock);
	return data;
}