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
struct sensor_device_attribute {int /*<<< orphan*/  index; } ;
struct nct6775_data {int* BEEP_BITS; int beeps; int /*<<< orphan*/  num_temp_beeps; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int TEMP_ALARM_BASE ; 
 int find_temp_source (struct nct6775_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nct6775_data* nct6775_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t
show_temp_beep(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	struct nct6775_data *data = nct6775_update_device(dev);
	unsigned int beep = 0;
	int nr;

	/*
	 * For temperatures, there is no fixed mapping from registers to beep
	 * enable bits. Beep enable bits are determined by the temperature
	 * source mapping.
	 */
	nr = find_temp_source(data, sattr->index, data->num_temp_beeps);
	if (nr >= 0) {
		int bit = data->BEEP_BITS[nr + TEMP_ALARM_BASE];

		beep = (data->beeps >> bit) & 0x01;
	}
	return sprintf(buf, "%u\n", beep);
}