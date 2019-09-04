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
struct gpio_fan_data {int speed_index; int num_speed; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct gpio_fan_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t pwm1_show(struct device *dev, struct device_attribute *attr,
			 char *buf)
{
	struct gpio_fan_data *fan_data = dev_get_drvdata(dev);
	u8 pwm = fan_data->speed_index * 255 / (fan_data->num_speed - 1);

	return sprintf(buf, "%d\n", pwm);
}