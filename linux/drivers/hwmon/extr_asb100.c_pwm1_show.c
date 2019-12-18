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
struct asb100_data {int pwm; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int ASB100_PWM_FROM_REG (int) ; 
 struct asb100_data* asb100_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t pwm1_show(struct device *dev, struct device_attribute *attr,
		char *buf)
{
	struct asb100_data *data = asb100_update_device(dev);
	return sprintf(buf, "%d\n", ASB100_PWM_FROM_REG(data->pwm & 0x0f));
}