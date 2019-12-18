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
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int MSI_LCD_LEVEL_MAX ; 
 int set_lcd_level (int) ; 
 int sscanf (char const*,char*,int*) ; 

__attribute__((used)) static ssize_t store_lcd_level(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{

	int level, ret;

	if (sscanf(buf, "%i", &level) != 1 ||
	    (level < 0 || level >= MSI_LCD_LEVEL_MAX))
		return -EINVAL;

	ret = set_lcd_level(level);
	if (ret < 0)
		return ret;

	return count;
}