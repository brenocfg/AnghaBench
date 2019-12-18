#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ptp_clock {int /*<<< orphan*/  pincfg_mux; TYPE_2__* info; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct device_attribute {TYPE_3__ attr; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_5__ {TYPE_1__* pin_config; } ;
struct TYPE_4__ {unsigned int func; unsigned int chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ERESTARTSYS ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct ptp_clock* dev_get_drvdata (struct device*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ptp_pin_name2index (struct ptp_clock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 

__attribute__((used)) static ssize_t ptp_pin_show(struct device *dev, struct device_attribute *attr,
			    char *page)
{
	struct ptp_clock *ptp = dev_get_drvdata(dev);
	unsigned int func, chan;
	int index;

	index = ptp_pin_name2index(ptp, attr->attr.name);
	if (index < 0)
		return -EINVAL;

	if (mutex_lock_interruptible(&ptp->pincfg_mux))
		return -ERESTARTSYS;

	func = ptp->info->pin_config[index].func;
	chan = ptp->info->pin_config[index].chan;

	mutex_unlock(&ptp->pincfg_mux);

	return snprintf(page, PAGE_SIZE, "%u %u\n", func, chan);
}