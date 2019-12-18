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
struct fb_var_screeninfo {int /*<<< orphan*/  rotate; } ;
struct fb_info {struct fb_var_screeninfo var; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int activate (struct fb_info*,struct fb_var_screeninfo*) ; 
 struct fb_info* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  simple_strtoul (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t store_rotate(struct device *device,
			    struct device_attribute *attr,
			    const char *buf, size_t count)
{
	struct fb_info *fb_info = dev_get_drvdata(device);
	struct fb_var_screeninfo var;
	char **last = NULL;
	int err;

	var = fb_info->var;
	var.rotate = simple_strtoul(buf, last, 0);

	if ((err = activate(fb_info, &var)))
		return err;

	return count;
}