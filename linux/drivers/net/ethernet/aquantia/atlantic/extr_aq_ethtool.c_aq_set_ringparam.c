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
struct ethtool_ringparam {int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_pending; scalar_t__ rx_jumbo_pending; scalar_t__ rx_mini_pending; } ;
struct aq_nic_s {size_t aq_vecs; int /*<<< orphan*/ * aq_vec; } ;
struct aq_nic_cfg_s {size_t vecs; void* txds; void* rxds; struct aq_hw_caps_s* aq_hw_caps; } ;
struct aq_hw_caps_s {int /*<<< orphan*/  txds_max; int /*<<< orphan*/  txds_min; int /*<<< orphan*/  rxds_max; int /*<<< orphan*/  rxds_min; } ;

/* Variables and functions */
 void* ALIGN (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AQ_HW_RXD_MULTIPLE ; 
 int /*<<< orphan*/  AQ_HW_TXD_MULTIPLE ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  aq_nic_free_vectors (struct aq_nic_s*) ; 
 struct aq_nic_cfg_s* aq_nic_get_cfg (struct aq_nic_s*) ; 
 int /*<<< orphan*/  aq_vec_alloc (struct aq_nic_s*,size_t,struct aq_nic_cfg_s*) ; 
 int /*<<< orphan*/  dev_close (struct net_device*) ; 
 int dev_open (struct net_device*,int /*<<< orphan*/ *) ; 
 void* max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* min (void*,int /*<<< orphan*/ ) ; 
 struct aq_nic_s* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int aq_set_ringparam(struct net_device *ndev,
			    struct ethtool_ringparam *ring)
{
	int err = 0;
	bool ndev_running = false;
	struct aq_nic_s *aq_nic = netdev_priv(ndev);
	struct aq_nic_cfg_s *aq_nic_cfg = aq_nic_get_cfg(aq_nic);
	const struct aq_hw_caps_s *hw_caps = aq_nic_cfg->aq_hw_caps;

	if (ring->rx_mini_pending || ring->rx_jumbo_pending) {
		err = -EOPNOTSUPP;
		goto err_exit;
	}

	if (netif_running(ndev)) {
		ndev_running = true;
		dev_close(ndev);
	}

	aq_nic_free_vectors(aq_nic);

	aq_nic_cfg->rxds = max(ring->rx_pending, hw_caps->rxds_min);
	aq_nic_cfg->rxds = min(aq_nic_cfg->rxds, hw_caps->rxds_max);
	aq_nic_cfg->rxds = ALIGN(aq_nic_cfg->rxds, AQ_HW_RXD_MULTIPLE);

	aq_nic_cfg->txds = max(ring->tx_pending, hw_caps->txds_min);
	aq_nic_cfg->txds = min(aq_nic_cfg->txds, hw_caps->txds_max);
	aq_nic_cfg->txds = ALIGN(aq_nic_cfg->txds, AQ_HW_TXD_MULTIPLE);

	for (aq_nic->aq_vecs = 0; aq_nic->aq_vecs < aq_nic_cfg->vecs;
	     aq_nic->aq_vecs++) {
		aq_nic->aq_vec[aq_nic->aq_vecs] =
		    aq_vec_alloc(aq_nic, aq_nic->aq_vecs, aq_nic_cfg);
		if (unlikely(!aq_nic->aq_vec[aq_nic->aq_vecs])) {
			err = -ENOMEM;
			goto err_exit;
		}
	}
	if (ndev_running)
		err = dev_open(ndev, NULL);

err_exit:
	return err;
}