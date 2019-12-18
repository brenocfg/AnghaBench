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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int TP_EC_FAN_AUTO ; 
 int TP_EC_FAN_FULLSPEED ; 
 int fan_get_status_safe (int*) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ssize_t fan_pwm1_enable_show(struct device *dev,
				    struct device_attribute *attr,
				    char *buf)
{
	int res, mode;
	u8 status;

	res = fan_get_status_safe(&status);
	if (res)
		return res;

	if (status & TP_EC_FAN_FULLSPEED) {
		mode = 0;
	} else if (status & TP_EC_FAN_AUTO) {
		mode = 2;
	} else
		mode = 1;

	return snprintf(buf, PAGE_SIZE, "%d\n", mode);
}