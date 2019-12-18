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
struct chsc_ssd_info {int path_mask; TYPE_1__* chpid; } ;
struct subchannel {struct chsc_ssd_info ssd_info; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */
 int sprintf (char*,char*,...) ; 
 struct subchannel* to_subchannel (struct device*) ; 

__attribute__((used)) static ssize_t chpids_show(struct device *dev,
			   struct device_attribute *attr,
			   char *buf)
{
	struct subchannel *sch = to_subchannel(dev);
	struct chsc_ssd_info *ssd = &sch->ssd_info;
	ssize_t ret = 0;
	int mask;
	int chp;

	for (chp = 0; chp < 8; chp++) {
		mask = 0x80 >> chp;
		if (ssd->path_mask & mask)
			ret += sprintf(buf + ret, "%02x ", ssd->chpid[chp].id);
		else
			ret += sprintf(buf + ret, "00 ");
	}
	ret += sprintf(buf + ret, "\n");
	return ret;
}