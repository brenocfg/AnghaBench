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
struct vivid_dev {int dummy; } ;
struct fb_var_screeninfo {int dummy; } ;
struct fb_info {scalar_t__ par; } ;

/* Variables and functions */
 int _vivid_fb_check_var (struct fb_var_screeninfo*,struct vivid_dev*) ; 
 int /*<<< orphan*/  dprintk (struct vivid_dev*,int,char*) ; 

__attribute__((used)) static int vivid_fb_check_var(struct fb_var_screeninfo *var, struct fb_info *info)
{
	struct vivid_dev *dev = (struct vivid_dev *) info->par;

	dprintk(dev, 1, "vivid_fb_check_var\n");
	return _vivid_fb_check_var(var, dev);
}