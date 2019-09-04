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
struct ethtool_coalesce {int /*<<< orphan*/  rx_max_coalesced_frames_high; int /*<<< orphan*/  rx_coalesce_usecs_high; int /*<<< orphan*/  rx_max_coalesced_frames; int /*<<< orphan*/  rx_coalesce_usecs; int /*<<< orphan*/  rx_max_coalesced_frames_low; int /*<<< orphan*/  rx_coalesce_usecs_low; scalar_t__ use_adaptive_rx_coalesce; int /*<<< orphan*/  tx_coalesce_usecs; scalar_t__ rate_sample_interval; scalar_t__ tx_max_coalesced_frames_high; scalar_t__ tx_coalesce_usecs_high; scalar_t__ pkt_rate_high; scalar_t__ tx_max_coalesced_frames_low; scalar_t__ tx_coalesce_usecs_low; scalar_t__ pkt_rate_low; scalar_t__ use_adaptive_tx_coalesce; scalar_t__ stats_block_coalesce_usecs; scalar_t__ tx_max_coalesced_frames_irq; scalar_t__ tx_max_coalesced_frames; scalar_t__ tx_coalesce_usecs_irq; scalar_t__ rx_max_coalesced_frames_irq; scalar_t__ rx_coalesce_usecs_irq; } ;
struct ena_intr_moder_entry {void* bytes_per_interval; int /*<<< orphan*/  pkts_per_interval; int /*<<< orphan*/  intr_moder_interval; } ;
struct ena_com_dev {int dummy; } ;
struct ena_adapter {struct ena_com_dev* ena_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 void* ENA_INTR_BYTE_COUNT_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ENA_INTR_MODER_HIGHEST ; 
 int /*<<< orphan*/  ENA_INTR_MODER_LOWEST ; 
 int /*<<< orphan*/  ENA_INTR_MODER_MID ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ena_com_disable_adaptive_moderation (struct ena_com_dev*) ; 
 int /*<<< orphan*/  ena_com_enable_adaptive_moderation (struct ena_com_dev*) ; 
 scalar_t__ ena_com_get_adaptive_moderation_enabled (struct ena_com_dev*) ; 
 int /*<<< orphan*/  ena_com_init_intr_moderation_entry (struct ena_com_dev*,int /*<<< orphan*/ ,struct ena_intr_moder_entry*) ; 
 int /*<<< orphan*/  ena_com_interrupt_moderation_supported (struct ena_com_dev*) ; 
 int ena_com_update_nonadaptive_moderation_interval_rx (struct ena_com_dev*,int /*<<< orphan*/ ) ; 
 int ena_com_update_nonadaptive_moderation_interval_tx (struct ena_com_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ena_update_tx_rings_intr_moderation (struct ena_adapter*) ; 
 struct ena_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ena_set_coalesce(struct net_device *net_dev,
			    struct ethtool_coalesce *coalesce)
{
	struct ena_adapter *adapter = netdev_priv(net_dev);
	struct ena_com_dev *ena_dev = adapter->ena_dev;
	struct ena_intr_moder_entry intr_moder_entry;
	int rc;

	if (!ena_com_interrupt_moderation_supported(ena_dev)) {
		/* the devie doesn't support interrupt moderation */
		return -EOPNOTSUPP;
	}

	if (coalesce->rx_coalesce_usecs_irq ||
	    coalesce->rx_max_coalesced_frames_irq ||
	    coalesce->tx_coalesce_usecs_irq ||
	    coalesce->tx_max_coalesced_frames ||
	    coalesce->tx_max_coalesced_frames_irq ||
	    coalesce->stats_block_coalesce_usecs ||
	    coalesce->use_adaptive_tx_coalesce ||
	    coalesce->pkt_rate_low ||
	    coalesce->tx_coalesce_usecs_low ||
	    coalesce->tx_max_coalesced_frames_low ||
	    coalesce->pkt_rate_high ||
	    coalesce->tx_coalesce_usecs_high ||
	    coalesce->tx_max_coalesced_frames_high ||
	    coalesce->rate_sample_interval)
		return -EINVAL;

	rc = ena_com_update_nonadaptive_moderation_interval_tx(ena_dev,
							       coalesce->tx_coalesce_usecs);
	if (rc)
		return rc;

	ena_update_tx_rings_intr_moderation(adapter);

	if (ena_com_get_adaptive_moderation_enabled(ena_dev)) {
		if (!coalesce->use_adaptive_rx_coalesce) {
			ena_com_disable_adaptive_moderation(ena_dev);
			rc = ena_com_update_nonadaptive_moderation_interval_rx(ena_dev,
									       coalesce->rx_coalesce_usecs);
			return rc;
		}
	} else { /* was in non-adaptive mode */
		if (coalesce->use_adaptive_rx_coalesce) {
			ena_com_enable_adaptive_moderation(ena_dev);
		} else {
			rc = ena_com_update_nonadaptive_moderation_interval_rx(ena_dev,
									       coalesce->rx_coalesce_usecs);
			return rc;
		}
	}

	intr_moder_entry.intr_moder_interval = coalesce->rx_coalesce_usecs_low;
	intr_moder_entry.pkts_per_interval = coalesce->rx_max_coalesced_frames_low;
	intr_moder_entry.bytes_per_interval = ENA_INTR_BYTE_COUNT_NOT_SUPPORTED;
	ena_com_init_intr_moderation_entry(adapter->ena_dev, ENA_INTR_MODER_LOWEST, &intr_moder_entry);

	intr_moder_entry.intr_moder_interval = coalesce->rx_coalesce_usecs;
	intr_moder_entry.pkts_per_interval = coalesce->rx_max_coalesced_frames;
	intr_moder_entry.bytes_per_interval = ENA_INTR_BYTE_COUNT_NOT_SUPPORTED;
	ena_com_init_intr_moderation_entry(adapter->ena_dev, ENA_INTR_MODER_MID, &intr_moder_entry);

	intr_moder_entry.intr_moder_interval = coalesce->rx_coalesce_usecs_high;
	intr_moder_entry.pkts_per_interval = coalesce->rx_max_coalesced_frames_high;
	intr_moder_entry.bytes_per_interval = ENA_INTR_BYTE_COUNT_NOT_SUPPORTED;
	ena_com_init_intr_moderation_entry(adapter->ena_dev, ENA_INTR_MODER_HIGHEST, &intr_moder_entry);

	return 0;
}