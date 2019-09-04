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
struct g760a_data {int fan_sta; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  fan_div; int /*<<< orphan*/  clk; int /*<<< orphan*/  act_cnt; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int G760A_REG_FAN_STA_RPM_LOW ; 
 struct g760a_data* g760a_update_client (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned int rpm_from_cnt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 

__attribute__((used)) static ssize_t fan1_input_show(struct device *dev,
			       struct device_attribute *da, char *buf)
{
	struct g760a_data *data = g760a_update_client(dev);
	unsigned int rpm = 0;

	mutex_lock(&data->update_lock);
	if (!(data->fan_sta & G760A_REG_FAN_STA_RPM_LOW))
		rpm = rpm_from_cnt(data->act_cnt, data->clk, data->fan_div);
	mutex_unlock(&data->update_lock);

	return sprintf(buf, "%d\n", rpm);
}