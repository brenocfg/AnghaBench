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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adt7470_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  client; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 unsigned char ADT7470_CFG_LF ; 
 unsigned char ADT7470_FREQ_MASK ; 
 unsigned char ADT7470_FREQ_SHIFT ; 
 int /*<<< orphan*/  ADT7470_REG_CFG ; 
 int /*<<< orphan*/  ADT7470_REG_CFG_2 ; 
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/ * adt7470_freq_map ; 
 struct adt7470_data* adt7470_update_device (struct device*) ; 
 unsigned char i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t pwm1_freq_show(struct device *dev,
			      struct device_attribute *devattr, char *buf)
{
	struct adt7470_data *data = adt7470_update_device(dev);
	unsigned char cfg_reg_1;
	unsigned char cfg_reg_2;
	int index;

	mutex_lock(&data->lock);
	cfg_reg_1 = i2c_smbus_read_byte_data(data->client, ADT7470_REG_CFG);
	cfg_reg_2 = i2c_smbus_read_byte_data(data->client, ADT7470_REG_CFG_2);
	mutex_unlock(&data->lock);

	index = (cfg_reg_2 & ADT7470_FREQ_MASK) >> ADT7470_FREQ_SHIFT;
	if (!(cfg_reg_1 & ADT7470_CFG_LF))
		index += 8;
	if (index >= ARRAY_SIZE(adt7470_freq_map))
		index = ARRAY_SIZE(adt7470_freq_map) - 1;

	return scnprintf(buf, PAGE_SIZE, "%d\n", adt7470_freq_map[index]);
}