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
struct it87_data {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 struct it87_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ has_10_9mv_adc (struct it87_data*) ; 
 scalar_t__ has_12mv_adc (struct it87_data*) ; 
 scalar_t__ has_vin3_5v (struct it87_data*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t show_label(struct device *dev, struct device_attribute *attr,
			  char *buf)
{
	static const char * const labels[] = {
		"+5V",
		"5VSB",
		"Vbat",
		"AVCC",
	};
	static const char * const labels_it8721[] = {
		"+3.3V",
		"3VSB",
		"Vbat",
		"+3.3V",
	};
	struct it87_data *data = dev_get_drvdata(dev);
	int nr = to_sensor_dev_attr(attr)->index;
	const char *label;

	if (has_vin3_5v(data) && nr == 0)
		label = labels[0];
	else if (has_12mv_adc(data) || has_10_9mv_adc(data))
		label = labels_it8721[nr];
	else
		label = labels[nr];

	return sprintf(buf, "%s\n", label);
}