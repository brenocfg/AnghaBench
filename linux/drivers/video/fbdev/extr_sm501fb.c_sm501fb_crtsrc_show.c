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
struct sm501fb_info {scalar_t__ regs; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ SM501_DC_CRT_CONTROL ; 
 unsigned long SM501_DC_CRT_CONTROL_SEL ; 
 struct sm501fb_info* dev_get_drvdata (struct device*) ; 
 unsigned long smc501_readl (scalar_t__) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static ssize_t sm501fb_crtsrc_show(struct device *dev,
			       struct device_attribute *attr, char *buf)
{
	struct sm501fb_info *info = dev_get_drvdata(dev);
	unsigned long ctrl;

	ctrl = smc501_readl(info->regs + SM501_DC_CRT_CONTROL);
	ctrl &= SM501_DC_CRT_CONTROL_SEL;

	return snprintf(buf, PAGE_SIZE, "%s\n", ctrl ? "crt" : "panel");
}