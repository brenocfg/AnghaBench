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
struct TYPE_2__ {int /*<<< orphan*/  coreid; } ;
struct ssb_device {int /*<<< orphan*/  core_index; TYPE_1__ id; } ;
struct ssb_bus {int /*<<< orphan*/  bar_lock; struct ssb_device* mapped_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  ssb_core_name (int /*<<< orphan*/ ) ; 
 int ssb_pci_switch_coreidx (struct ssb_bus*,int /*<<< orphan*/ ) ; 

int ssb_pci_switch_core(struct ssb_bus *bus,
			struct ssb_device *dev)
{
	int err;
	unsigned long flags;

#if SSB_VERBOSE_PCICORESWITCH_DEBUG
	pr_info("Switching to %s core, index %d\n",
		ssb_core_name(dev->id.coreid), dev->core_index);
#endif

	spin_lock_irqsave(&bus->bar_lock, flags);
	err = ssb_pci_switch_coreidx(bus, dev->core_index);
	if (!err)
		bus->mapped_device = dev;
	spin_unlock_irqrestore(&bus->bar_lock, flags);

	return err;
}