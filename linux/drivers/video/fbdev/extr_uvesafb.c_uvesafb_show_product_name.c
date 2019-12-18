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
struct TYPE_2__ {int oem_product_name_ptr; } ;
struct uvesafb_par {TYPE_1__ vbe_ib; } ;
struct fb_info {struct uvesafb_par* par; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct fb_info* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static ssize_t uvesafb_show_product_name(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct fb_info *info = dev_get_drvdata(dev);
	struct uvesafb_par *par = info->par;

	if (par->vbe_ib.oem_product_name_ptr)
		return snprintf(buf, PAGE_SIZE, "%s\n", (char *)
			(&par->vbe_ib) + par->vbe_ib.oem_product_name_ptr);
	else
		return 0;
}