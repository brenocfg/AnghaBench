#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct picolcd_fb_data {unsigned int update_rate; } ;
struct picolcd_data {TYPE_2__* fb_info; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_4__ {TYPE_1__* fbdefio; struct picolcd_fb_data* par; } ;
struct TYPE_3__ {int delay; } ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t ERANGE ; 
 int HZ ; 
 unsigned int PICOLCDFB_UPDATE_RATE_DEFAULT ; 
 unsigned int PICOLCDFB_UPDATE_RATE_LIMIT ; 
 struct picolcd_data* dev_get_drvdata (struct device*) ; 
 int sscanf (char const*,char*,unsigned int*) ; 

__attribute__((used)) static ssize_t picolcd_fb_update_rate_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct picolcd_data *data = dev_get_drvdata(dev);
	struct picolcd_fb_data *fbdata = data->fb_info->par;
	int i;
	unsigned u;

	if (count < 1 || count > 10)
		return -EINVAL;

	i = sscanf(buf, "%u", &u);
	if (i != 1)
		return -EINVAL;

	if (u > PICOLCDFB_UPDATE_RATE_LIMIT)
		return -ERANGE;
	else if (u == 0)
		u = PICOLCDFB_UPDATE_RATE_DEFAULT;

	fbdata->update_rate = u;
	data->fb_info->fbdefio->delay = HZ / fbdata->update_rate;
	return count;
}