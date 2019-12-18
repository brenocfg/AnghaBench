#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct octeon_device {int chip_id; void* tx_max_coalesced_frames; void* rx_max_coalesced_frames; void* rx_coalesce_usecs; TYPE_5__* pci_dev; TYPE_4__** instr_queue; } ;
struct oct_intrmod_cfg {int rx_enable; int tx_enable; void* tx_frames; void* rx_usecs; void* rx_frames; int /*<<< orphan*/  member_0; } ;
struct net_device {int dummy; } ;
struct TYPE_8__ {size_t num_txpciq; TYPE_2__* txpciq; } ;
struct lio {TYPE_3__ linfo; struct octeon_device* oct_dev; } ;
struct ethtool_coalesce {int tx_max_coalesced_frames; scalar_t__ use_adaptive_tx_coalesce; scalar_t__ use_adaptive_rx_coalesce; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {int fill_threshold; } ;
struct TYPE_6__ {size_t q_no; } ;
struct TYPE_7__ {TYPE_1__ s; } ;

/* Variables and functions */
 void* CFG_GET_IQ_INTR_PKT (int /*<<< orphan*/ ) ; 
 void* CFG_GET_OQ_INTR_PKT (int /*<<< orphan*/ ) ; 
 void* CFG_GET_OQ_INTR_TIME (int /*<<< orphan*/ ) ; 
 int CN6XXX_DB_MAX ; 
 int CN6XXX_DB_MIN ; 
 int EINVAL ; 
 struct lio* GET_LIO (struct net_device*) ; 
#define  OCTEON_CN23XX_PF_VID 131 
#define  OCTEON_CN23XX_VF_VID 130 
#define  OCTEON_CN66XX 129 
#define  OCTEON_CN68XX 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int,int) ; 
 int oct_cfg_adaptive_intr (struct lio*,struct oct_intrmod_cfg*,struct ethtool_coalesce*) ; 
 int oct_cfg_rx_intrcnt (struct lio*,struct oct_intrmod_cfg*,struct ethtool_coalesce*) ; 
 int oct_cfg_rx_intrtime (struct lio*,struct oct_intrmod_cfg*,struct ethtool_coalesce*) ; 
 int oct_cfg_tx_intrcnt (struct lio*,struct oct_intrmod_cfg*,struct ethtool_coalesce*) ; 
 int /*<<< orphan*/  octeon_get_conf (struct octeon_device*) ; 

__attribute__((used)) static int lio_set_intr_coalesce(struct net_device *netdev,
				 struct ethtool_coalesce *intr_coal)
{
	struct lio *lio = GET_LIO(netdev);
	int ret;
	struct octeon_device *oct = lio->oct_dev;
	struct oct_intrmod_cfg intrmod = {0};
	u32 j, q_no;
	int db_max, db_min;

	switch (oct->chip_id) {
	case OCTEON_CN68XX:
	case OCTEON_CN66XX:
		db_min = CN6XXX_DB_MIN;
		db_max = CN6XXX_DB_MAX;
		if ((intr_coal->tx_max_coalesced_frames >= db_min) &&
		    (intr_coal->tx_max_coalesced_frames <= db_max)) {
			for (j = 0; j < lio->linfo.num_txpciq; j++) {
				q_no = lio->linfo.txpciq[j].s.q_no;
				oct->instr_queue[q_no]->fill_threshold =
					intr_coal->tx_max_coalesced_frames;
			}
		} else {
			dev_err(&oct->pci_dev->dev,
				"LIQUIDIO: Invalid tx-frames:%d. Range is min:%d max:%d\n",
				intr_coal->tx_max_coalesced_frames,
				db_min, db_max);
			return -EINVAL;
		}
		break;
	case OCTEON_CN23XX_PF_VID:
	case OCTEON_CN23XX_VF_VID:
		break;
	default:
		return -EINVAL;
	}

	intrmod.rx_enable = intr_coal->use_adaptive_rx_coalesce ? 1 : 0;
	intrmod.tx_enable = intr_coal->use_adaptive_tx_coalesce ? 1 : 0;
	intrmod.rx_frames = CFG_GET_OQ_INTR_PKT(octeon_get_conf(oct));
	intrmod.rx_usecs = CFG_GET_OQ_INTR_TIME(octeon_get_conf(oct));
	intrmod.tx_frames = CFG_GET_IQ_INTR_PKT(octeon_get_conf(oct));

	ret = oct_cfg_adaptive_intr(lio, &intrmod, intr_coal);

	if (!intr_coal->use_adaptive_rx_coalesce) {
		ret = oct_cfg_rx_intrtime(lio, &intrmod, intr_coal);
		if (ret)
			goto ret_intrmod;

		ret = oct_cfg_rx_intrcnt(lio, &intrmod, intr_coal);
		if (ret)
			goto ret_intrmod;
	} else {
		oct->rx_coalesce_usecs =
			CFG_GET_OQ_INTR_TIME(octeon_get_conf(oct));
		oct->rx_max_coalesced_frames =
			CFG_GET_OQ_INTR_PKT(octeon_get_conf(oct));
	}

	if (!intr_coal->use_adaptive_tx_coalesce) {
		ret = oct_cfg_tx_intrcnt(lio, &intrmod, intr_coal);
		if (ret)
			goto ret_intrmod;
	} else {
		oct->tx_max_coalesced_frames =
			CFG_GET_IQ_INTR_PKT(octeon_get_conf(oct));
	}

	return 0;
ret_intrmod:
	return ret;
}