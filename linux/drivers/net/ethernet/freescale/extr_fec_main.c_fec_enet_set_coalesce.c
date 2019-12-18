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
struct fec_enet_private {int quirks; int rx_pkts_itr; int tx_pkts_itr; int /*<<< orphan*/  tx_time_itr; int /*<<< orphan*/  rx_time_itr; TYPE_1__* pdev; } ;
struct ethtool_coalesce {int rx_max_coalesced_frames; int tx_max_coalesced_frames; int /*<<< orphan*/  tx_coalesce_usecs; int /*<<< orphan*/  rx_coalesce_usecs; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int FEC_QUIRK_HAS_COALESCE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  fec_enet_itr_coal_set (struct net_device*) ; 
 unsigned int fec_enet_us_to_itr_clock (struct net_device*,int /*<<< orphan*/ ) ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
fec_enet_set_coalesce(struct net_device *ndev, struct ethtool_coalesce *ec)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	struct device *dev = &fep->pdev->dev;
	unsigned int cycle;

	if (!(fep->quirks & FEC_QUIRK_HAS_COALESCE))
		return -EOPNOTSUPP;

	if (ec->rx_max_coalesced_frames > 255) {
		dev_err(dev, "Rx coalesced frames exceed hardware limitation\n");
		return -EINVAL;
	}

	if (ec->tx_max_coalesced_frames > 255) {
		dev_err(dev, "Tx coalesced frame exceed hardware limitation\n");
		return -EINVAL;
	}

	cycle = fec_enet_us_to_itr_clock(ndev, fep->rx_time_itr);
	if (cycle > 0xFFFF) {
		dev_err(dev, "Rx coalesced usec exceed hardware limitation\n");
		return -EINVAL;
	}

	cycle = fec_enet_us_to_itr_clock(ndev, fep->tx_time_itr);
	if (cycle > 0xFFFF) {
		dev_err(dev, "Rx coalesced usec exceed hardware limitation\n");
		return -EINVAL;
	}

	fep->rx_time_itr = ec->rx_coalesce_usecs;
	fep->rx_pkts_itr = ec->rx_max_coalesced_frames;

	fep->tx_time_itr = ec->tx_coalesce_usecs;
	fep->tx_pkts_itr = ec->tx_max_coalesced_frames;

	fec_enet_itr_coal_set(ndev);

	return 0;
}