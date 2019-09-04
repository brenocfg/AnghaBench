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
struct i2c_client {int dummy; } ;
struct g760a_data {int /*<<< orphan*/  update_lock; int /*<<< orphan*/  set_cnt; struct i2c_client* client; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  G760A_REG_SET_CNT ; 
 int /*<<< orphan*/  PWM_TO_CNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clamp_val (unsigned long,int /*<<< orphan*/ ,int) ; 
 struct g760a_data* g760a_update_client (struct device*) ; 
 int /*<<< orphan*/  g760a_write_value (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t pwm1_store(struct device *dev, struct device_attribute *da,
			  const char *buf, size_t count)
{
	struct g760a_data *data = g760a_update_client(dev);
	struct i2c_client *client = data->client;
	unsigned long val;

	if (kstrtoul(buf, 10, &val))
		return -EINVAL;

	mutex_lock(&data->update_lock);
	data->set_cnt = PWM_TO_CNT(clamp_val(val, 0, 255));
	g760a_write_value(client, G760A_REG_SET_CNT, data->set_cnt);
	mutex_unlock(&data->update_lock);

	return count;
}