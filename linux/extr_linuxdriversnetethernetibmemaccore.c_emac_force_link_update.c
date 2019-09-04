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
struct emac_instance {int /*<<< orphan*/  link_work; scalar_t__ link_polling; int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_POLL_LINK_OFF ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_rmb () ; 

__attribute__((used)) static void emac_force_link_update(struct emac_instance *dev)
{
	netif_carrier_off(dev->ndev);
	smp_rmb();
	if (dev->link_polling) {
		cancel_delayed_work_sync(&dev->link_work);
		if (dev->link_polling)
			schedule_delayed_work(&dev->link_work,  PHY_POLL_LINK_OFF);
	}
}