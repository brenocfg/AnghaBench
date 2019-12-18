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
struct emac_adapter {int /*<<< orphan*/  reset_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  emac_mac_down (struct emac_adapter*) ; 
 int emac_mac_up (struct emac_adapter*) ; 
 int /*<<< orphan*/  emac_sgmii_reset (struct emac_adapter*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int emac_reinit_locked(struct emac_adapter *adpt)
{
	int ret;

	mutex_lock(&adpt->reset_lock);

	emac_mac_down(adpt);
	emac_sgmii_reset(adpt);
	ret = emac_mac_up(adpt);

	mutex_unlock(&adpt->reset_lock);

	return ret;
}