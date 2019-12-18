#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lm93_data {int* vccp_limits; int /*<<< orphan*/  update_lock; TYPE_1__* block7; int /*<<< orphan*/ * vid; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_4__ {int index; } ;
struct TYPE_3__ {int min; } ;

/* Variables and functions */
 int LM93_IN_REL_TO_REG (unsigned long,int /*<<< orphan*/ ,long) ; 
 int LM93_IN_TO_REG (int,unsigned long) ; 
 int /*<<< orphan*/  LM93_REG_IN_MIN (int) ; 
 int /*<<< orphan*/  LM93_REG_VCCP_LIMIT_OFF (int) ; 
 long LM93_VID_FROM_REG (int /*<<< orphan*/ ) ; 
 struct lm93_data* dev_get_drvdata (struct device*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  lm93_write_byte (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__* to_sensor_dev_attr (struct device_attribute*) ; 
 scalar_t__* vccp_limit_type ; 

__attribute__((used)) static ssize_t in_min_store(struct device *dev, struct device_attribute *attr,
			    const char *buf, size_t count)
{
	int nr = (to_sensor_dev_attr(attr))->index;
	struct lm93_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int vccp = nr - 6;
	long vid;
	unsigned long val;
	int err;

	err = kstrtoul(buf, 10, &val);
	if (err)
		return err;

	mutex_lock(&data->update_lock);
	if ((nr == 6 || nr == 7) && vccp_limit_type[vccp]) {
		vid = LM93_VID_FROM_REG(data->vid[vccp]);
		data->vccp_limits[vccp] = (data->vccp_limits[vccp] & 0xf0) |
				LM93_IN_REL_TO_REG(val, 0, vid);
		lm93_write_byte(client, LM93_REG_VCCP_LIMIT_OFF(vccp),
				data->vccp_limits[vccp]);
	} else {
		data->block7[nr].min = LM93_IN_TO_REG(nr, val);
		lm93_write_byte(client, LM93_REG_IN_MIN(nr),
				data->block7[nr].min);
	}
	mutex_unlock(&data->update_lock);
	return count;
}