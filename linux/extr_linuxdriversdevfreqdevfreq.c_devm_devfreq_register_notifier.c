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
struct notifier_block {int dummy; } ;
struct device {int dummy; } ;
struct devfreq_notifier_devres {unsigned int list; struct notifier_block* nb; struct devfreq* devfreq; } ;
struct devfreq {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int devfreq_register_notifier (struct devfreq*,struct notifier_block*,unsigned int) ; 
 int /*<<< orphan*/  devm_devfreq_notifier_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct devfreq_notifier_devres*) ; 
 struct devfreq_notifier_devres* devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct devfreq_notifier_devres*) ; 

int devm_devfreq_register_notifier(struct device *dev,
				struct devfreq *devfreq,
				struct notifier_block *nb,
				unsigned int list)
{
	struct devfreq_notifier_devres *ptr;
	int ret;

	ptr = devres_alloc(devm_devfreq_notifier_release, sizeof(*ptr),
				GFP_KERNEL);
	if (!ptr)
		return -ENOMEM;

	ret = devfreq_register_notifier(devfreq, nb, list);
	if (ret) {
		devres_free(ptr);
		return ret;
	}

	ptr->devfreq = devfreq;
	ptr->nb = nb;
	ptr->list = list;
	devres_add(dev, ptr);

	return 0;
}