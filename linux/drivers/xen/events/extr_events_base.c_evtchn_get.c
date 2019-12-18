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
struct irq_info {scalar_t__ refcnt; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int get_evtchn_to_irq (unsigned int) ; 
 struct irq_info* irq_get_handler_data (int) ; 
 int /*<<< orphan*/  irq_mapping_update_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned int xen_evtchn_max_channels () ; 

int evtchn_get(unsigned int evtchn)
{
	int irq;
	struct irq_info *info;
	int err = -ENOENT;

	if (evtchn >= xen_evtchn_max_channels())
		return -EINVAL;

	mutex_lock(&irq_mapping_update_lock);

	irq = get_evtchn_to_irq(evtchn);
	if (irq == -1)
		goto done;

	info = irq_get_handler_data(irq);

	if (!info)
		goto done;

	err = -EINVAL;
	if (info->refcnt <= 0)
		goto done;

	info->refcnt++;
	err = 0;
 done:
	mutex_unlock(&irq_mapping_update_lock);

	return err;
}