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
struct wilc_vif {struct wilc* wilc; } ;
struct wilc {int /*<<< orphan*/  vif_mutex; int /*<<< orphan*/  txq_add_to_head_cs; int /*<<< orphan*/  cfg_cmd_lock; int /*<<< orphan*/  rxq_cs; int /*<<< orphan*/  hif_cs; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct wilc_vif* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void wlan_deinit_locks(struct net_device *dev)
{
	struct wilc_vif *vif = netdev_priv(dev);
	struct wilc *wilc = vif->wilc;

	mutex_destroy(&wilc->hif_cs);
	mutex_destroy(&wilc->rxq_cs);
	mutex_destroy(&wilc->cfg_cmd_lock);
	mutex_destroy(&wilc->txq_add_to_head_cs);
	mutex_destroy(&wilc->vif_mutex);
}