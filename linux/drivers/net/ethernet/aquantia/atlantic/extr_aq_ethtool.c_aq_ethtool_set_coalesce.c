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
struct ethtool_coalesce {int rx_max_coalesced_frames; int tx_max_coalesced_frames; scalar_t__ rx_coalesce_usecs; scalar_t__ tx_coalesce_usecs; scalar_t__ tx_max_coalesced_frames_irq; scalar_t__ tx_coalesce_usecs_irq; scalar_t__ rx_max_coalesced_frames_irq; scalar_t__ rx_coalesce_usecs_irq; scalar_t__ use_adaptive_tx_coalesce; scalar_t__ use_adaptive_rx_coalesce; } ;
struct aq_nic_s {int dummy; } ;
struct aq_nic_cfg_s {scalar_t__ rx_itr; scalar_t__ tx_itr; int /*<<< orphan*/  itr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AQ_CFG_INTERRUPT_MODERATION_ON ; 
 scalar_t__ AQ_CFG_INTERRUPT_MODERATION_USEC_MAX ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 struct aq_nic_cfg_s* aq_nic_get_cfg (struct aq_nic_s*) ; 
 int aq_nic_update_interrupt_moderation_settings (struct aq_nic_s*) ; 
 struct aq_nic_s* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int aq_ethtool_set_coalesce(struct net_device *ndev,
				   struct ethtool_coalesce *coal)
{
	struct aq_nic_s *aq_nic = netdev_priv(ndev);
	struct aq_nic_cfg_s *cfg = aq_nic_get_cfg(aq_nic);

	/* This is not yet supported
	 */
	if (coal->use_adaptive_rx_coalesce || coal->use_adaptive_tx_coalesce)
		return -EOPNOTSUPP;

	/* Atlantic only supports timing based coalescing
	 */
	if (coal->rx_max_coalesced_frames > 1 ||
	    coal->rx_coalesce_usecs_irq ||
	    coal->rx_max_coalesced_frames_irq)
		return -EOPNOTSUPP;

	if (coal->tx_max_coalesced_frames > 1 ||
	    coal->tx_coalesce_usecs_irq ||
	    coal->tx_max_coalesced_frames_irq)
		return -EOPNOTSUPP;

	/* We do not support frame counting. Check this
	 */
	if (!(coal->rx_max_coalesced_frames == !coal->rx_coalesce_usecs))
		return -EOPNOTSUPP;
	if (!(coal->tx_max_coalesced_frames == !coal->tx_coalesce_usecs))
		return -EOPNOTSUPP;

	if (coal->rx_coalesce_usecs > AQ_CFG_INTERRUPT_MODERATION_USEC_MAX ||
	    coal->tx_coalesce_usecs > AQ_CFG_INTERRUPT_MODERATION_USEC_MAX)
		return -EINVAL;

	cfg->itr = AQ_CFG_INTERRUPT_MODERATION_ON;

	cfg->rx_itr = coal->rx_coalesce_usecs;
	cfg->tx_itr = coal->tx_coalesce_usecs;

	return aq_nic_update_interrupt_moderation_settings(aq_nic);
}