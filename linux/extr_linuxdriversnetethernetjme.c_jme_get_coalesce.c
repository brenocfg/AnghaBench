#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_2__ {int cur; } ;
struct jme_adapter {TYPE_1__ dpi; int /*<<< orphan*/  flags; } ;
struct ethtool_coalesce {int use_adaptive_rx_coalesce; scalar_t__ rx_max_coalesced_frames; scalar_t__ rx_coalesce_usecs; int /*<<< orphan*/  tx_max_coalesced_frames; int /*<<< orphan*/  tx_coalesce_usecs; } ;

/* Variables and functions */
 int /*<<< orphan*/  JME_FLAG_POLL ; 
#define  PCC_P1 130 
 scalar_t__ PCC_P1_CNT ; 
 scalar_t__ PCC_P1_TO ; 
#define  PCC_P2 129 
 scalar_t__ PCC_P2_CNT ; 
 scalar_t__ PCC_P2_TO ; 
#define  PCC_P3 128 
 scalar_t__ PCC_P3_CNT ; 
 scalar_t__ PCC_P3_TO ; 
 int /*<<< orphan*/  PCC_TX_CNT ; 
 int /*<<< orphan*/  PCC_TX_TO ; 
 struct jme_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
jme_get_coalesce(struct net_device *netdev, struct ethtool_coalesce *ecmd)
{
	struct jme_adapter *jme = netdev_priv(netdev);

	ecmd->tx_coalesce_usecs = PCC_TX_TO;
	ecmd->tx_max_coalesced_frames = PCC_TX_CNT;

	if (test_bit(JME_FLAG_POLL, &jme->flags)) {
		ecmd->use_adaptive_rx_coalesce = false;
		ecmd->rx_coalesce_usecs = 0;
		ecmd->rx_max_coalesced_frames = 0;
		return 0;
	}

	ecmd->use_adaptive_rx_coalesce = true;

	switch (jme->dpi.cur) {
	case PCC_P1:
		ecmd->rx_coalesce_usecs = PCC_P1_TO;
		ecmd->rx_max_coalesced_frames = PCC_P1_CNT;
		break;
	case PCC_P2:
		ecmd->rx_coalesce_usecs = PCC_P2_TO;
		ecmd->rx_max_coalesced_frames = PCC_P2_CNT;
		break;
	case PCC_P3:
		ecmd->rx_coalesce_usecs = PCC_P3_TO;
		ecmd->rx_max_coalesced_frames = PCC_P3_CNT;
		break;
	default:
		break;
	}

	return 0;
}