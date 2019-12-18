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
struct g762_data {int fan_sta; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  fan_cmd2; int /*<<< orphan*/  fan_cmd1; int /*<<< orphan*/  clk_freq; int /*<<< orphan*/  act_cnt; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  G762_CLKDIV_FROM_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G762_GEARMULT_FROM_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G762_PULSE_FROM_REG (int /*<<< orphan*/ ) ; 
 int G762_REG_FAN_STA_OOC ; 
 scalar_t__ IS_ERR (struct g762_data*) ; 
 int /*<<< orphan*/  PTR_ERR (struct g762_data*) ; 
 struct g762_data* g762_update_client (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned int rpm_from_cnt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 

__attribute__((used)) static ssize_t fan1_input_show(struct device *dev,
			       struct device_attribute *da, char *buf)
{
	struct g762_data *data = g762_update_client(dev);
	unsigned int rpm = 0;

	if (IS_ERR(data))
		return PTR_ERR(data);

	mutex_lock(&data->update_lock);
	/* reverse logic: fan out of control reporting is enabled low */
	if (data->fan_sta & G762_REG_FAN_STA_OOC) {
		rpm = rpm_from_cnt(data->act_cnt, data->clk_freq,
				   G762_PULSE_FROM_REG(data->fan_cmd1),
				   G762_CLKDIV_FROM_REG(data->fan_cmd1),
				   G762_GEARMULT_FROM_REG(data->fan_cmd2));
	}
	mutex_unlock(&data->update_lock);

	return sprintf(buf, "%u\n", rpm);
}