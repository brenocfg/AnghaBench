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
struct rave_sp {int /*<<< orphan*/  event_notifier_list; } ;
struct notifier_block {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int blocking_notifier_chain_register (int /*<<< orphan*/ *,struct notifier_block*) ; 
 struct rave_sp* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_add (struct device*,struct notifier_block**) ; 
 struct notifier_block** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct notifier_block**) ; 
 int /*<<< orphan*/  rave_sp_unregister_event_notifier ; 

int devm_rave_sp_register_event_notifier(struct device *dev,
					 struct notifier_block *nb)
{
	struct rave_sp *sp = dev_get_drvdata(dev->parent);
	struct notifier_block **rcnb;
	int ret;

	rcnb = devres_alloc(rave_sp_unregister_event_notifier,
			    sizeof(*rcnb), GFP_KERNEL);
	if (!rcnb)
		return -ENOMEM;

	ret = blocking_notifier_chain_register(&sp->event_notifier_list, nb);
	if (!ret) {
		*rcnb = nb;
		devres_add(dev, rcnb);
	} else {
		devres_free(rcnb);
	}

	return ret;
}