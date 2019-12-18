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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  LTC4215_ADIN ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 unsigned int abs (int const) ; 
 unsigned int ltc4215_get_current (struct device*) ; 
 int ltc4215_get_voltage (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,unsigned int const) ; 

__attribute__((used)) static ssize_t ltc4215_power_show(struct device *dev,
				  struct device_attribute *da, char *buf)
{
	const unsigned int curr = ltc4215_get_current(dev);
	const int output_voltage = ltc4215_get_voltage(dev, LTC4215_ADIN);

	/* current in mA * voltage in mV == power in uW */
	const unsigned int power = abs(output_voltage * curr);

	return snprintf(buf, PAGE_SIZE, "%u\n", power);
}