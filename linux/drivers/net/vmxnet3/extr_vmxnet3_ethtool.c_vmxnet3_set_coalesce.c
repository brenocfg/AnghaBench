#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int confVer; int /*<<< orphan*/  confPA; int /*<<< orphan*/  confLen; } ;
union Vmxnet3_CmdInfo {TYPE_5__ varConf; } ;
typedef  scalar_t__ u32 ;
struct vmxnet3_adapter {int default_coal_mode; int /*<<< orphan*/  cmd_lock; int /*<<< orphan*/  coal_conf_pa; TYPE_6__* coal_conf; struct Vmxnet3_DriverShared* shared; } ;
struct net_device {int dummy; } ;
struct ethtool_coalesce {scalar_t__ rx_coalesce_usecs; scalar_t__ use_adaptive_rx_coalesce; scalar_t__ tx_max_coalesced_frames; scalar_t__ rx_max_coalesced_frames; scalar_t__ rate_sample_interval; scalar_t__ tx_max_coalesced_frames_high; scalar_t__ tx_coalesce_usecs_high; scalar_t__ rx_max_coalesced_frames_high; scalar_t__ rx_coalesce_usecs_high; scalar_t__ pkt_rate_high; scalar_t__ tx_max_coalesced_frames_low; scalar_t__ tx_coalesce_usecs_low; scalar_t__ rx_max_coalesced_frames_low; scalar_t__ rx_coalesce_usecs_low; scalar_t__ pkt_rate_low; scalar_t__ use_adaptive_tx_coalesce; scalar_t__ stats_block_coalesce_usecs; scalar_t__ tx_max_coalesced_frames_irq; scalar_t__ tx_coalesce_usecs_irq; scalar_t__ tx_coalesce_usecs; scalar_t__ rx_max_coalesced_frames_irq; scalar_t__ rx_coalesce_usecs_irq; } ;
struct TYPE_7__ {union Vmxnet3_CmdInfo cmdInfo; } ;
struct Vmxnet3_DriverShared {TYPE_1__ cu; } ;
struct TYPE_9__ {void* tx_depth; void* rx_depth; void* tx_comp_depth; } ;
struct TYPE_8__ {scalar_t__ rbc_rate; } ;
struct TYPE_10__ {TYPE_3__ coalStatic; TYPE_2__ coalRbc; } ;
struct TYPE_12__ {TYPE_4__ coalPara; int /*<<< orphan*/  coalMode; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  VMXNET3_CMD_SET_COALESCE ; 
 int /*<<< orphan*/  VMXNET3_COALESCE_ADAPT ; 
 int /*<<< orphan*/  VMXNET3_COALESCE_DISABLED ; 
 int /*<<< orphan*/  VMXNET3_COALESCE_RBC ; 
 int /*<<< orphan*/  VMXNET3_COALESCE_STATIC ; 
 scalar_t__ VMXNET3_COAL_RBC_MAX_RATE ; 
 scalar_t__ VMXNET3_COAL_RBC_MIN_RATE ; 
 scalar_t__ VMXNET3_COAL_RBC_RATE (scalar_t__) ; 
 void* VMXNET3_COAL_STATIC_DEFAULT_DEPTH ; 
 scalar_t__ VMXNET3_COAL_STATIC_MAX_DEPTH ; 
 int /*<<< orphan*/  VMXNET3_REG_CMD ; 
 int /*<<< orphan*/  VMXNET3_VERSION_GE_3 (struct vmxnet3_adapter*) ; 
 int /*<<< orphan*/  VMXNET3_WRITE_BAR1_REG (struct vmxnet3_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 struct vmxnet3_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
vmxnet3_set_coalesce(struct net_device *netdev, struct ethtool_coalesce *ec)
{
	struct vmxnet3_adapter *adapter = netdev_priv(netdev);
	struct Vmxnet3_DriverShared *shared = adapter->shared;
	union Vmxnet3_CmdInfo *cmdInfo = &shared->cu.cmdInfo;
	unsigned long flags;

	if (!VMXNET3_VERSION_GE_3(adapter))
		return -EOPNOTSUPP;

	if (ec->rx_coalesce_usecs_irq ||
	    ec->rx_max_coalesced_frames_irq ||
	    ec->tx_coalesce_usecs ||
	    ec->tx_coalesce_usecs_irq ||
	    ec->tx_max_coalesced_frames_irq ||
	    ec->stats_block_coalesce_usecs ||
	    ec->use_adaptive_tx_coalesce ||
	    ec->pkt_rate_low ||
	    ec->rx_coalesce_usecs_low ||
	    ec->rx_max_coalesced_frames_low ||
	    ec->tx_coalesce_usecs_low ||
	    ec->tx_max_coalesced_frames_low ||
	    ec->pkt_rate_high ||
	    ec->rx_coalesce_usecs_high ||
	    ec->rx_max_coalesced_frames_high ||
	    ec->tx_coalesce_usecs_high ||
	    ec->tx_max_coalesced_frames_high ||
	    ec->rate_sample_interval) {
		return -EINVAL;
	}

	if ((ec->rx_coalesce_usecs == 0) &&
	    (ec->use_adaptive_rx_coalesce == 0) &&
	    (ec->tx_max_coalesced_frames == 0) &&
	    (ec->rx_max_coalesced_frames == 0)) {
		memset(adapter->coal_conf, 0, sizeof(*adapter->coal_conf));
		adapter->coal_conf->coalMode = VMXNET3_COALESCE_DISABLED;
		goto done;
	}

	if (ec->rx_coalesce_usecs != 0) {
		u32 rbc_rate;

		if ((ec->use_adaptive_rx_coalesce != 0) ||
		    (ec->tx_max_coalesced_frames != 0) ||
		    (ec->rx_max_coalesced_frames != 0)) {
			return -EINVAL;
		}

		rbc_rate = VMXNET3_COAL_RBC_RATE(ec->rx_coalesce_usecs);
		if (rbc_rate < VMXNET3_COAL_RBC_MIN_RATE ||
		    rbc_rate > VMXNET3_COAL_RBC_MAX_RATE) {
			return -EINVAL;
		}

		memset(adapter->coal_conf, 0, sizeof(*adapter->coal_conf));
		adapter->coal_conf->coalMode = VMXNET3_COALESCE_RBC;
		adapter->coal_conf->coalPara.coalRbc.rbc_rate = rbc_rate;
		goto done;
	}

	if (ec->use_adaptive_rx_coalesce != 0) {
		if ((ec->rx_coalesce_usecs != 0) ||
		    (ec->tx_max_coalesced_frames != 0) ||
		    (ec->rx_max_coalesced_frames != 0)) {
			return -EINVAL;
		}
		memset(adapter->coal_conf, 0, sizeof(*adapter->coal_conf));
		adapter->coal_conf->coalMode = VMXNET3_COALESCE_ADAPT;
		goto done;
	}

	if ((ec->tx_max_coalesced_frames != 0) ||
	    (ec->rx_max_coalesced_frames != 0)) {
		if ((ec->rx_coalesce_usecs != 0) ||
		    (ec->use_adaptive_rx_coalesce != 0)) {
			return -EINVAL;
		}

		if ((ec->tx_max_coalesced_frames >
		    VMXNET3_COAL_STATIC_MAX_DEPTH) ||
		    (ec->rx_max_coalesced_frames >
		     VMXNET3_COAL_STATIC_MAX_DEPTH)) {
			return -EINVAL;
		}

		memset(adapter->coal_conf, 0, sizeof(*adapter->coal_conf));
		adapter->coal_conf->coalMode = VMXNET3_COALESCE_STATIC;

		adapter->coal_conf->coalPara.coalStatic.tx_comp_depth =
			(ec->tx_max_coalesced_frames ?
			 ec->tx_max_coalesced_frames :
			 VMXNET3_COAL_STATIC_DEFAULT_DEPTH);

		adapter->coal_conf->coalPara.coalStatic.rx_depth =
			(ec->rx_max_coalesced_frames ?
			 ec->rx_max_coalesced_frames :
			 VMXNET3_COAL_STATIC_DEFAULT_DEPTH);

		adapter->coal_conf->coalPara.coalStatic.tx_depth =
			 VMXNET3_COAL_STATIC_DEFAULT_DEPTH;
		goto done;
	}

done:
	adapter->default_coal_mode = false;
	if (netif_running(netdev)) {
		spin_lock_irqsave(&adapter->cmd_lock, flags);
		cmdInfo->varConf.confVer = 1;
		cmdInfo->varConf.confLen =
			cpu_to_le32(sizeof(*adapter->coal_conf));
		cmdInfo->varConf.confPA  = cpu_to_le64(adapter->coal_conf_pa);
		VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_CMD,
				       VMXNET3_CMD_SET_COALESCE);
		spin_unlock_irqrestore(&adapter->cmd_lock, flags);
	}

	return 0;
}