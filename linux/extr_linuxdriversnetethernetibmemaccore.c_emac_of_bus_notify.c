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

/* Variables and functions */
 unsigned long BUS_NOTIFY_BOUND_DRIVER ; 
 int /*<<< orphan*/  emac_probe_wait ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int emac_of_bus_notify(struct notifier_block *nb, unsigned long action,
			      void *data)
{
	/* We are only intereted in device addition */
	if (action == BUS_NOTIFY_BOUND_DRIVER)
		wake_up_all(&emac_probe_wait);
	return 0;
}