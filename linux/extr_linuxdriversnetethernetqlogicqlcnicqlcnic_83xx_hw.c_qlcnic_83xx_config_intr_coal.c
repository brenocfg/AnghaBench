#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct qlcnic_nic_intr_coalesce {scalar_t__ rx_time_us; scalar_t__ rx_packets; int type; scalar_t__ tx_time_us; scalar_t__ tx_packets; int /*<<< orphan*/  flag; } ;
struct qlcnic_adapter {int /*<<< orphan*/  netdev; TYPE_2__* recv_ctx; TYPE_1__* ahw; } ;
struct ethtool_coalesce {scalar_t__ tx_coalesce_usecs; scalar_t__ tx_max_coalesced_frames; scalar_t__ rx_coalesce_usecs; scalar_t__ rx_max_coalesced_frames; } ;
struct TYPE_4__ {scalar_t__ state; } ;
struct TYPE_3__ {struct qlcnic_nic_intr_coalesce coal; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 scalar_t__ QLCNIC_HOST_CTX_STATE_FREED ; 
#define  QLCNIC_INTR_COAL_TYPE_RX 130 
#define  QLCNIC_INTR_COAL_TYPE_RX_TX 129 
#define  QLCNIC_INTR_COAL_TYPE_TX 128 
 int /*<<< orphan*/  QLCNIC_INTR_DEFAULT ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int qlcnic_83xx_set_rx_intr_coal (struct qlcnic_adapter*) ; 
 int qlcnic_83xx_set_rx_tx_intr_coal (struct qlcnic_adapter*) ; 
 int qlcnic_83xx_set_tx_intr_coal (struct qlcnic_adapter*) ; 

int qlcnic_83xx_config_intr_coal(struct qlcnic_adapter *adapter,
				 struct ethtool_coalesce *ethcoal)
{
	struct qlcnic_nic_intr_coalesce *coal = &adapter->ahw->coal;
	u32 rx_coalesce_usecs, rx_max_frames;
	u32 tx_coalesce_usecs, tx_max_frames;
	int err;

	if (adapter->recv_ctx->state == QLCNIC_HOST_CTX_STATE_FREED)
		return -EIO;

	tx_coalesce_usecs = ethcoal->tx_coalesce_usecs;
	tx_max_frames = ethcoal->tx_max_coalesced_frames;
	rx_coalesce_usecs = ethcoal->rx_coalesce_usecs;
	rx_max_frames = ethcoal->rx_max_coalesced_frames;
	coal->flag = QLCNIC_INTR_DEFAULT;

	if ((coal->rx_time_us == rx_coalesce_usecs) &&
	    (coal->rx_packets == rx_max_frames)) {
		coal->type = QLCNIC_INTR_COAL_TYPE_TX;
		coal->tx_time_us = tx_coalesce_usecs;
		coal->tx_packets = tx_max_frames;
	} else if ((coal->tx_time_us == tx_coalesce_usecs) &&
		   (coal->tx_packets == tx_max_frames)) {
		coal->type = QLCNIC_INTR_COAL_TYPE_RX;
		coal->rx_time_us = rx_coalesce_usecs;
		coal->rx_packets = rx_max_frames;
	} else {
		coal->type = QLCNIC_INTR_COAL_TYPE_RX_TX;
		coal->rx_time_us = rx_coalesce_usecs;
		coal->rx_packets = rx_max_frames;
		coal->tx_time_us = tx_coalesce_usecs;
		coal->tx_packets = tx_max_frames;
	}

	switch (coal->type) {
	case QLCNIC_INTR_COAL_TYPE_RX:
		err = qlcnic_83xx_set_rx_intr_coal(adapter);
		break;
	case QLCNIC_INTR_COAL_TYPE_TX:
		err = qlcnic_83xx_set_tx_intr_coal(adapter);
		break;
	case QLCNIC_INTR_COAL_TYPE_RX_TX:
		err = qlcnic_83xx_set_rx_tx_intr_coal(adapter);
		break;
	default:
		err = -EINVAL;
		netdev_err(adapter->netdev,
			   "Invalid Interrupt coalescing type\n");
		break;
	}

	return err;
}