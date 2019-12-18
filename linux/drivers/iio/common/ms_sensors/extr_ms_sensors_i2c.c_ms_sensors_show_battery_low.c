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
typedef  int u8 ;
struct ms_ht_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/  client; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ms_sensors_read_config_reg (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sprintf (char*,char*,int) ; 

ssize_t ms_sensors_show_battery_low(struct ms_ht_dev *dev_data,
				    char *buf)
{
	int ret;
	u8 config_reg;

	mutex_lock(&dev_data->lock);
	ret = ms_sensors_read_config_reg(dev_data->client, &config_reg);
	mutex_unlock(&dev_data->lock);
	if (ret)
		return ret;

	return sprintf(buf, "%d\n", (config_reg & 0x40) >> 6);
}