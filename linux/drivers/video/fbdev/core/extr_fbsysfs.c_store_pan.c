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
struct fb_var_screeninfo {void* yoffset; void* xoffset; } ;
struct fb_info {struct fb_var_screeninfo var; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  console_lock () ; 
 int /*<<< orphan*/  console_unlock () ; 
 struct fb_info* dev_get_drvdata (struct device*) ; 
 int fb_pan_display (struct fb_info*,struct fb_var_screeninfo*) ; 
 void* simple_strtoul (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t store_pan(struct device *device,
			 struct device_attribute *attr,
			 const char *buf, size_t count)
{
	struct fb_info *fb_info = dev_get_drvdata(device);
	struct fb_var_screeninfo var;
	char *last = NULL;
	int err;

	var = fb_info->var;
	var.xoffset = simple_strtoul(buf, &last, 0);
	last++;
	if (last - buf >= count)
		return -EINVAL;
	var.yoffset = simple_strtoul(last, &last, 0);

	console_lock();
	err = fb_pan_display(fb_info, &var);
	console_unlock();

	if (err < 0)
		return err;
	return count;
}