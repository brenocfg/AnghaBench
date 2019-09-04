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
struct ethtool_coalesce {int tx_coalesce_usecs; int rx_coalesce_usecs; int rx_coalesce_usecs_low; int rx_coalesce_usecs_high; scalar_t__ use_adaptive_rx_coalesce; int /*<<< orphan*/  rx_max_coalesced_frames_high; int /*<<< orphan*/  rx_max_coalesced_frames; int /*<<< orphan*/  rx_max_coalesced_frames_low; } ;
struct ena_intr_moder_entry {int intr_moder_interval; int /*<<< orphan*/  pkts_per_interval; } ;
struct ena_com_dev {int intr_delay_resolution; } ;
struct ena_adapter {struct ena_com_dev* ena_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_INTR_MODER_HIGHEST ; 
 int /*<<< orphan*/  ENA_INTR_MODER_LOWEST ; 
 int /*<<< orphan*/  ENA_INTR_MODER_MID ; 
 int EOPNOTSUPP ; 
 scalar_t__ ena_com_get_adaptive_moderation_enabled (struct ena_com_dev*) ; 
 int /*<<< orphan*/  ena_com_get_intr_moderation_entry (struct ena_com_dev*,int /*<<< orphan*/ ,struct ena_intr_moder_entry*) ; 
 int ena_com_get_nonadaptive_moderation_interval_rx (struct ena_com_dev*) ; 
 int ena_com_get_nonadaptive_moderation_interval_tx (struct ena_com_dev*) ; 
 int /*<<< orphan*/  ena_com_interrupt_moderation_supported (struct ena_com_dev*) ; 
 struct ena_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ena_get_coalesce(struct net_device *net_dev,
			    struct ethtool_coalesce *coalesce)
{
	struct ena_adapter *adapter = netdev_priv(net_dev);
	struct ena_com_dev *ena_dev = adapter->ena_dev;
	struct ena_intr_moder_entry intr_moder_entry;

	if (!ena_com_interrupt_moderation_supported(ena_dev)) {
		/* the devie doesn't support interrupt moderation */
		return -EOPNOTSUPP;
	}
	coalesce->tx_coalesce_usecs =
		ena_com_get_nonadaptive_moderation_interval_tx(ena_dev) /
			ena_dev->intr_delay_resolution;
	if (!ena_com_get_adaptive_moderation_enabled(ena_dev)) {
		coalesce->rx_coalesce_usecs =
			ena_com_get_nonadaptive_moderation_interval_rx(ena_dev)
			/ ena_dev->intr_delay_resolution;
	} else {
		ena_com_get_intr_moderation_entry(adapter->ena_dev, ENA_INTR_MODER_LOWEST, &intr_moder_entry);
		coalesce->rx_coalesce_usecs_low = intr_moder_entry.intr_moder_interval;
		coalesce->rx_max_coalesced_frames_low = intr_moder_entry.pkts_per_interval;

		ena_com_get_intr_moderation_entry(adapter->ena_dev, ENA_INTR_MODER_MID, &intr_moder_entry);
		coalesce->rx_coalesce_usecs = intr_moder_entry.intr_moder_interval;
		coalesce->rx_max_coalesced_frames = intr_moder_entry.pkts_per_interval;

		ena_com_get_intr_moderation_entry(adapter->ena_dev, ENA_INTR_MODER_HIGHEST, &intr_moder_entry);
		coalesce->rx_coalesce_usecs_high = intr_moder_entry.intr_moder_interval;
		coalesce->rx_max_coalesced_frames_high = intr_moder_entry.pkts_per_interval;
	}
	coalesce->use_adaptive_rx_coalesce =
		ena_com_get_adaptive_moderation_enabled(ena_dev);

	return 0;
}