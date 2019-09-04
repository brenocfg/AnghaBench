#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct octeon_instr_queue {int /*<<< orphan*/  fill_threshold; } ;
struct octeon_device {int chip_id; struct octeon_instr_queue** instr_queue; scalar_t__ chip; int /*<<< orphan*/  tx_max_coalesced_frames; int /*<<< orphan*/  rx_max_coalesced_frames; int /*<<< orphan*/  rx_coalesce_usecs; } ;
struct octeon_cn6xxx {int /*<<< orphan*/  conf; } ;
struct oct_intrmod_cfg {int /*<<< orphan*/  tx_mincnt_trigger; int /*<<< orphan*/  tx_maxcnt_trigger; scalar_t__ tx_enable; int /*<<< orphan*/  rx_mincnt_trigger; int /*<<< orphan*/  rx_mintmr_trigger; int /*<<< orphan*/  rx_maxtmr_trigger; int /*<<< orphan*/  rx_maxcnt_trigger; int /*<<< orphan*/  minpkt_ratethr; int /*<<< orphan*/  maxpkt_ratethr; int /*<<< orphan*/  check_intrvl; scalar_t__ rx_enable; } ;
struct net_device {int dummy; } ;
struct TYPE_6__ {TYPE_2__* txpciq; } ;
struct lio {int /*<<< orphan*/  netdev; TYPE_3__ linfo; struct octeon_device* oct_dev; } ;
struct ethtool_coalesce {int /*<<< orphan*/  tx_max_coalesced_frames_low; int /*<<< orphan*/  tx_max_coalesced_frames_high; scalar_t__ use_adaptive_tx_coalesce; int /*<<< orphan*/  rx_max_coalesced_frames_low; int /*<<< orphan*/  rx_coalesce_usecs_low; int /*<<< orphan*/  rx_coalesce_usecs_high; int /*<<< orphan*/  rx_max_coalesced_frames_high; int /*<<< orphan*/  pkt_rate_low; int /*<<< orphan*/  pkt_rate_high; int /*<<< orphan*/  rate_sample_interval; scalar_t__ use_adaptive_rx_coalesce; int /*<<< orphan*/  tx_max_coalesced_frames; int /*<<< orphan*/  rx_max_coalesced_frames; int /*<<< orphan*/  rx_coalesce_usecs; } ;
struct TYPE_4__ {size_t q_no; } ;
struct TYPE_5__ {TYPE_1__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_GET_OQ_INTR_PKT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFG_GET_OQ_INTR_TIME (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENODEV ; 
 struct lio* GET_LIO (struct net_device*) ; 
 scalar_t__ OCTEON_CN23XX_PF (struct octeon_device*) ; 
#define  OCTEON_CN23XX_PF_VID 131 
 scalar_t__ OCTEON_CN23XX_VF (struct octeon_device*) ; 
#define  OCTEON_CN23XX_VF_VID 130 
#define  OCTEON_CN66XX 129 
#define  OCTEON_CN68XX 128 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  netif_info (struct lio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ octnet_get_intrmod_cfg (struct lio*,struct oct_intrmod_cfg*) ; 

__attribute__((used)) static int lio_get_intr_coalesce(struct net_device *netdev,
				 struct ethtool_coalesce *intr_coal)
{
	struct lio *lio = GET_LIO(netdev);
	struct octeon_device *oct = lio->oct_dev;
	struct octeon_instr_queue *iq;
	struct oct_intrmod_cfg intrmod_cfg;

	if (octnet_get_intrmod_cfg(lio, &intrmod_cfg))
		return -ENODEV;

	switch (oct->chip_id) {
	case OCTEON_CN23XX_PF_VID:
	case OCTEON_CN23XX_VF_VID: {
		if (!intrmod_cfg.rx_enable) {
			intr_coal->rx_coalesce_usecs = oct->rx_coalesce_usecs;
			intr_coal->rx_max_coalesced_frames =
				oct->rx_max_coalesced_frames;
		}
		if (!intrmod_cfg.tx_enable)
			intr_coal->tx_max_coalesced_frames =
				oct->tx_max_coalesced_frames;
		break;
	}
	case OCTEON_CN68XX:
	case OCTEON_CN66XX: {
		struct octeon_cn6xxx *cn6xxx =
			(struct octeon_cn6xxx *)oct->chip;

		if (!intrmod_cfg.rx_enable) {
			intr_coal->rx_coalesce_usecs =
				CFG_GET_OQ_INTR_TIME(cn6xxx->conf);
			intr_coal->rx_max_coalesced_frames =
				CFG_GET_OQ_INTR_PKT(cn6xxx->conf);
		}
		iq = oct->instr_queue[lio->linfo.txpciq[0].s.q_no];
		intr_coal->tx_max_coalesced_frames = iq->fill_threshold;
		break;
	}
	default:
		netif_info(lio, drv, lio->netdev, "Unknown Chip !!\n");
		return -EINVAL;
	}
	if (intrmod_cfg.rx_enable) {
		intr_coal->use_adaptive_rx_coalesce =
			intrmod_cfg.rx_enable;
		intr_coal->rate_sample_interval =
			intrmod_cfg.check_intrvl;
		intr_coal->pkt_rate_high =
			intrmod_cfg.maxpkt_ratethr;
		intr_coal->pkt_rate_low =
			intrmod_cfg.minpkt_ratethr;
		intr_coal->rx_max_coalesced_frames_high =
			intrmod_cfg.rx_maxcnt_trigger;
		intr_coal->rx_coalesce_usecs_high =
			intrmod_cfg.rx_maxtmr_trigger;
		intr_coal->rx_coalesce_usecs_low =
			intrmod_cfg.rx_mintmr_trigger;
		intr_coal->rx_max_coalesced_frames_low =
			intrmod_cfg.rx_mincnt_trigger;
	}
	if ((OCTEON_CN23XX_PF(oct) || OCTEON_CN23XX_VF(oct)) &&
	    (intrmod_cfg.tx_enable)) {
		intr_coal->use_adaptive_tx_coalesce =
			intrmod_cfg.tx_enable;
		intr_coal->tx_max_coalesced_frames_high =
			intrmod_cfg.tx_maxcnt_trigger;
		intr_coal->tx_max_coalesced_frames_low =
			intrmod_cfg.tx_mincnt_trigger;
	}
	return 0;
}