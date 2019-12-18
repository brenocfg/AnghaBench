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
struct wilc {int vif_num; int /*<<< orphan*/  wiphy; int /*<<< orphan*/  bus_data; int /*<<< orphan*/  hif_workqueue; TYPE_1__** vif; int /*<<< orphan*/ * firmware; } ;
struct TYPE_2__ {scalar_t__ ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (scalar_t__) ; 
 int /*<<< orphan*/  wilc_wfi_deinit_mon_interface (struct wilc*,int) ; 
 int /*<<< orphan*/  wilc_wlan_cfg_deinit (struct wilc*) ; 
 int /*<<< orphan*/  wiphy_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_unregister (int /*<<< orphan*/ ) ; 

void wilc_netdev_cleanup(struct wilc *wilc)
{
	int i;

	if (!wilc)
		return;

	if (wilc->firmware) {
		release_firmware(wilc->firmware);
		wilc->firmware = NULL;
	}

	for (i = 0; i < wilc->vif_num; i++) {
		if (wilc->vif[i] && wilc->vif[i]->ndev)
			unregister_netdev(wilc->vif[i]->ndev);
	}

	wilc_wfi_deinit_mon_interface(wilc, false);
	flush_workqueue(wilc->hif_workqueue);
	destroy_workqueue(wilc->hif_workqueue);
	wilc_wlan_cfg_deinit(wilc);
	kfree(wilc->bus_data);
	wiphy_unregister(wilc->wiphy);
	wiphy_free(wilc->wiphy);
}