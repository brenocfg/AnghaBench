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
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {void* gpio2; void* gpio1; void* cpu_vid; void* vid; } ;
struct atxp1_data {int valid; int /*<<< orphan*/  update_lock; TYPE_1__ reg; scalar_t__ last_updated; struct i2c_client* client; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATXP1_CVID ; 
 int /*<<< orphan*/  ATXP1_GPIO1 ; 
 int /*<<< orphan*/  ATXP1_GPIO2 ; 
 int /*<<< orphan*/  ATXP1_VID ; 
 scalar_t__ HZ ; 
 struct atxp1_data* dev_get_drvdata (struct device*) ; 
 void* i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static struct atxp1_data *atxp1_update_device(struct device *dev)
{
	struct atxp1_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;

	mutex_lock(&data->update_lock);

	if (time_after(jiffies, data->last_updated + HZ) || !data->valid) {

		/* Update local register data */
		data->reg.vid = i2c_smbus_read_byte_data(client, ATXP1_VID);
		data->reg.cpu_vid = i2c_smbus_read_byte_data(client,
							     ATXP1_CVID);
		data->reg.gpio1 = i2c_smbus_read_byte_data(client, ATXP1_GPIO1);
		data->reg.gpio2 = i2c_smbus_read_byte_data(client, ATXP1_GPIO2);

		data->valid = 1;
	}

	mutex_unlock(&data->update_lock);

	return data;
}