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
struct net_device {int dummy; } ;
struct aq_nic_s {int dummy; } ;
struct aq_nic_cfg_s {int hw_features; int is_lro; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int NETIF_F_LRO ; 
 int /*<<< orphan*/  aq_ndev_close (struct net_device*) ; 
 int /*<<< orphan*/  aq_ndev_open (struct net_device*) ; 
 struct aq_nic_cfg_s* aq_nic_get_cfg (struct aq_nic_s*) ; 
 struct aq_nic_s* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static int aq_ndev_set_features(struct net_device *ndev,
				netdev_features_t features)
{
	struct aq_nic_s *aq_nic = netdev_priv(ndev);
	struct aq_nic_cfg_s *aq_cfg = aq_nic_get_cfg(aq_nic);
	bool is_lro = false;

	if (aq_cfg->hw_features & NETIF_F_LRO) {
		is_lro = features & NETIF_F_LRO;

		if (aq_cfg->is_lro != is_lro) {
			aq_cfg->is_lro = is_lro;

			if (netif_running(ndev)) {
				aq_ndev_close(ndev);
				aq_ndev_open(ndev);
			}
		}
	}

	return 0;
}