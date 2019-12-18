#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ umode_t ;
struct ptp_clock_info {int /*<<< orphan*/  pps; int /*<<< orphan*/  n_per_out; int /*<<< orphan*/  n_ext_ts; } ;
struct ptp_clock {struct ptp_clock_info* info; } ;
struct kobject {int dummy; } ;
struct device {int dummy; } ;
struct attribute {scalar_t__ mode; } ;
struct TYPE_8__ {struct attribute attr; } ;
struct TYPE_7__ {struct attribute attr; } ;
struct TYPE_6__ {struct attribute attr; } ;
struct TYPE_5__ {struct attribute attr; } ;

/* Variables and functions */
 TYPE_4__ dev_attr_extts_enable ; 
 TYPE_3__ dev_attr_fifo ; 
 TYPE_2__ dev_attr_period ; 
 TYPE_1__ dev_attr_pps_enable ; 
 struct ptp_clock* dev_get_drvdata (struct device*) ; 
 struct device* kobj_to_dev (struct kobject*) ; 

__attribute__((used)) static umode_t ptp_is_attribute_visible(struct kobject *kobj,
					struct attribute *attr, int n)
{
	struct device *dev = kobj_to_dev(kobj);
	struct ptp_clock *ptp = dev_get_drvdata(dev);
	struct ptp_clock_info *info = ptp->info;
	umode_t mode = attr->mode;

	if (attr == &dev_attr_extts_enable.attr ||
	    attr == &dev_attr_fifo.attr) {
		if (!info->n_ext_ts)
			mode = 0;
	} else if (attr == &dev_attr_period.attr) {
		if (!info->n_per_out)
			mode = 0;
	} else if (attr == &dev_attr_pps_enable.attr) {
		if (!info->pps)
			mode = 0;
	}

	return mode;
}