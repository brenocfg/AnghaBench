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
struct picolcd_fb_data {unsigned int update_rate; } ;
struct picolcd_data {TYPE_1__* fb_info; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {struct picolcd_fb_data* par; } ;

/* Variables and functions */
 size_t PAGE_SIZE ; 
 unsigned int PICOLCDFB_UPDATE_RATE_LIMIT ; 
 struct picolcd_data* dev_get_drvdata (struct device*) ; 
 int min (size_t,size_t) ; 
 scalar_t__ snprintf (char*,size_t,char*,unsigned int) ; 

__attribute__((used)) static ssize_t picolcd_fb_update_rate_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct picolcd_data *data = dev_get_drvdata(dev);
	struct picolcd_fb_data *fbdata = data->fb_info->par;
	unsigned i, fb_update_rate = fbdata->update_rate;
	size_t ret = 0;

	for (i = 1; i <= PICOLCDFB_UPDATE_RATE_LIMIT; i++)
		if (ret >= PAGE_SIZE)
			break;
		else if (i == fb_update_rate)
			ret += snprintf(buf+ret, PAGE_SIZE-ret, "[%u] ", i);
		else
			ret += snprintf(buf+ret, PAGE_SIZE-ret, "%u ", i);
	if (ret > 0)
		buf[min(ret, (size_t)PAGE_SIZE)-1] = '\n';
	return ret;
}