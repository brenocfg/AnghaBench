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
struct ethtool_coalesce {scalar_t__ use_adaptive_rx_coalesce; int /*<<< orphan*/  rx_coalesce_usecs; int /*<<< orphan*/  tx_coalesce_usecs; } ;
struct ena_com_dev {int dummy; } ;
struct ena_adapter {struct ena_com_dev* ena_dev; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ena_com_disable_adaptive_moderation (struct ena_com_dev*) ; 
 int /*<<< orphan*/  ena_com_enable_adaptive_moderation (struct ena_com_dev*) ; 
 scalar_t__ ena_com_get_adaptive_moderation_enabled (struct ena_com_dev*) ; 
 int /*<<< orphan*/  ena_com_interrupt_moderation_supported (struct ena_com_dev*) ; 
 int ena_com_update_nonadaptive_moderation_interval_rx (struct ena_com_dev*,int /*<<< orphan*/ ) ; 
 int ena_com_update_nonadaptive_moderation_interval_tx (struct ena_com_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ena_update_rx_rings_intr_moderation (struct ena_adapter*) ; 
 int /*<<< orphan*/  ena_update_tx_rings_intr_moderation (struct ena_adapter*) ; 
 struct ena_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ena_set_coalesce(struct net_device *net_dev,
			    struct ethtool_coalesce *coalesce)
{
	struct ena_adapter *adapter = netdev_priv(net_dev);
	struct ena_com_dev *ena_dev = adapter->ena_dev;
	int rc;

	if (!ena_com_interrupt_moderation_supported(ena_dev)) {
		/* the devie doesn't support interrupt moderation */
		return -EOPNOTSUPP;
	}

	rc = ena_com_update_nonadaptive_moderation_interval_tx(ena_dev,
							       coalesce->tx_coalesce_usecs);
	if (rc)
		return rc;

	ena_update_tx_rings_intr_moderation(adapter);

	if (coalesce->use_adaptive_rx_coalesce) {
		if (!ena_com_get_adaptive_moderation_enabled(ena_dev))
			ena_com_enable_adaptive_moderation(ena_dev);
		return 0;
	}

	rc = ena_com_update_nonadaptive_moderation_interval_rx(ena_dev,
							       coalesce->rx_coalesce_usecs);
	if (rc)
		return rc;

	ena_update_rx_rings_intr_moderation(adapter);

	if (!coalesce->use_adaptive_rx_coalesce) {
		if (ena_com_get_adaptive_moderation_enabled(ena_dev))
			ena_com_disable_adaptive_moderation(ena_dev);
	}

	return 0;
}