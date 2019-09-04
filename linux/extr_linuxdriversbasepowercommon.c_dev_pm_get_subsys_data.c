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
struct pm_subsys_data {int refcount; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; struct pm_subsys_data* subsys_data; } ;
struct device {TYPE_1__ power; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct pm_subsys_data*) ; 
 struct pm_subsys_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_clk_init (struct device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int dev_pm_get_subsys_data(struct device *dev)
{
	struct pm_subsys_data *psd;

	psd = kzalloc(sizeof(*psd), GFP_KERNEL);
	if (!psd)
		return -ENOMEM;

	spin_lock_irq(&dev->power.lock);

	if (dev->power.subsys_data) {
		dev->power.subsys_data->refcount++;
	} else {
		spin_lock_init(&psd->lock);
		psd->refcount = 1;
		dev->power.subsys_data = psd;
		pm_clk_init(dev);
		psd = NULL;
	}

	spin_unlock_irq(&dev->power.lock);

	/* kfree() verifies that its argument is nonzero. */
	kfree(psd);

	return 0;
}