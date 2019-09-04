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
struct g762_data {int valid; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  set_cnt; int /*<<< orphan*/  client; int /*<<< orphan*/  fan_cmd2; int /*<<< orphan*/  fan_cmd1; int /*<<< orphan*/  clk_freq; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  G762_CLKDIV_FROM_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G762_GEARMULT_FROM_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G762_PULSE_FROM_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G762_REG_SET_CNT ; 
 scalar_t__ IS_ERR (struct g762_data*) ; 
 int PTR_ERR (struct g762_data*) ; 
 int /*<<< orphan*/  cnt_from_rpm (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct g762_data* g762_update_client (struct device*) ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_set_fan_target(struct device *dev, unsigned long val)
{
	struct g762_data *data = g762_update_client(dev);
	int ret;

	if (IS_ERR(data))
		return PTR_ERR(data);

	mutex_lock(&data->update_lock);
	data->set_cnt = cnt_from_rpm(val, data->clk_freq,
				     G762_PULSE_FROM_REG(data->fan_cmd1),
				     G762_CLKDIV_FROM_REG(data->fan_cmd1),
				     G762_GEARMULT_FROM_REG(data->fan_cmd2));
	ret = i2c_smbus_write_byte_data(data->client, G762_REG_SET_CNT,
					data->set_cnt);
	data->valid = false;
	mutex_unlock(&data->update_lock);

	return ret;
}