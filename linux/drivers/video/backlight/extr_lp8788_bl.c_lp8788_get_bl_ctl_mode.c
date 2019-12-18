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
struct lp8788_bl {int mode; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  enum lp8788_bl_ctrl_mode { ____Placeholder_lp8788_bl_ctrl_mode } lp8788_bl_ctrl_mode ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct lp8788_bl* dev_get_drvdata (struct device*) ; 
 scalar_t__ is_brightness_ctrl_by_pwm (int) ; 
 scalar_t__ is_brightness_ctrl_by_register (int) ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static ssize_t lp8788_get_bl_ctl_mode(struct device *dev,
				     struct device_attribute *attr, char *buf)
{
	struct lp8788_bl *bl = dev_get_drvdata(dev);
	enum lp8788_bl_ctrl_mode mode = bl->mode;
	char *strmode;

	if (is_brightness_ctrl_by_pwm(mode))
		strmode = "PWM based";
	else if (is_brightness_ctrl_by_register(mode))
		strmode = "Register based";
	else
		strmode = "Invalid mode";

	return scnprintf(buf, PAGE_SIZE, "%s\n", strmode);
}