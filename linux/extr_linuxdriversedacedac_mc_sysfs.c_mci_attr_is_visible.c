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
typedef  int /*<<< orphan*/  umode_t ;
struct mem_ctl_info {scalar_t__ set_sdram_scrub_rate; scalar_t__ get_sdram_scrub_rate; } ;
struct kobject {int dummy; } ;
struct device {int dummy; } ;
struct attribute {int /*<<< orphan*/  mode; } ;
struct TYPE_2__ {struct attribute attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_IRUGO ; 
 int /*<<< orphan*/  S_IWUSR ; 
 TYPE_1__ dev_attr_sdram_scrub_rate ; 
 struct device* kobj_to_dev (struct kobject*) ; 
 struct mem_ctl_info* to_mci (struct device*) ; 

__attribute__((used)) static umode_t mci_attr_is_visible(struct kobject *kobj,
				   struct attribute *attr, int idx)
{
	struct device *dev = kobj_to_dev(kobj);
	struct mem_ctl_info *mci = to_mci(dev);
	umode_t mode = 0;

	if (attr != &dev_attr_sdram_scrub_rate.attr)
		return attr->mode;
	if (mci->get_sdram_scrub_rate)
		mode |= S_IRUGO;
	if (mci->set_sdram_scrub_rate)
		mode |= S_IWUSR;
	return mode;
}