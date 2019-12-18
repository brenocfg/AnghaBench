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
struct net_device {int flags; } ;
struct ionic_lif {int uc_overflow; int mc_overflow; unsigned int rx_mode; TYPE_1__* ionic; } ;
struct TYPE_5__ {int /*<<< orphan*/  max_mcast_filters; int /*<<< orphan*/  max_ucast_filters; } ;
struct TYPE_6__ {TYPE_2__ eth; } ;
struct ionic_identity {TYPE_3__ lif; } ;
struct TYPE_4__ {struct ionic_identity ident; } ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_PROMISC ; 
 unsigned int IONIC_RX_MODE_F_ALLMULTI ; 
 unsigned int IONIC_RX_MODE_F_BROADCAST ; 
 unsigned int IONIC_RX_MODE_F_MULTICAST ; 
 unsigned int IONIC_RX_MODE_F_PROMISC ; 
 unsigned int IONIC_RX_MODE_F_UNICAST ; 
 int /*<<< orphan*/  __dev_mc_sync (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __dev_uc_sync (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ionic_lif_rx_mode (struct ionic_lif*,unsigned int) ; 
 int /*<<< orphan*/  ionic_addr_add ; 
 int /*<<< orphan*/  ionic_addr_del ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned int netdev_mc_count (struct net_device*) ; 
 struct ionic_lif* netdev_priv (struct net_device*) ; 
 int netdev_uc_count (struct net_device*) ; 

__attribute__((used)) static void ionic_set_rx_mode(struct net_device *netdev)
{
	struct ionic_lif *lif = netdev_priv(netdev);
	struct ionic_identity *ident;
	unsigned int nfilters;
	unsigned int rx_mode;

	ident = &lif->ionic->ident;

	rx_mode = IONIC_RX_MODE_F_UNICAST;
	rx_mode |= (netdev->flags & IFF_MULTICAST) ? IONIC_RX_MODE_F_MULTICAST : 0;
	rx_mode |= (netdev->flags & IFF_BROADCAST) ? IONIC_RX_MODE_F_BROADCAST : 0;
	rx_mode |= (netdev->flags & IFF_PROMISC) ? IONIC_RX_MODE_F_PROMISC : 0;
	rx_mode |= (netdev->flags & IFF_ALLMULTI) ? IONIC_RX_MODE_F_ALLMULTI : 0;

	/* sync unicast addresses
	 * next check to see if we're in an overflow state
	 *    if so, we track that we overflowed and enable NIC PROMISC
	 *    else if the overflow is set and not needed
	 *       we remove our overflow flag and check the netdev flags
	 *       to see if we can disable NIC PROMISC
	 */
	__dev_uc_sync(netdev, ionic_addr_add, ionic_addr_del);
	nfilters = le32_to_cpu(ident->lif.eth.max_ucast_filters);
	if (netdev_uc_count(netdev) + 1 > nfilters) {
		rx_mode |= IONIC_RX_MODE_F_PROMISC;
		lif->uc_overflow = true;
	} else if (lif->uc_overflow) {
		lif->uc_overflow = false;
		if (!(netdev->flags & IFF_PROMISC))
			rx_mode &= ~IONIC_RX_MODE_F_PROMISC;
	}

	/* same for multicast */
	__dev_mc_sync(netdev, ionic_addr_add, ionic_addr_del);
	nfilters = le32_to_cpu(ident->lif.eth.max_mcast_filters);
	if (netdev_mc_count(netdev) > nfilters) {
		rx_mode |= IONIC_RX_MODE_F_ALLMULTI;
		lif->mc_overflow = true;
	} else if (lif->mc_overflow) {
		lif->mc_overflow = false;
		if (!(netdev->flags & IFF_ALLMULTI))
			rx_mode &= ~IONIC_RX_MODE_F_ALLMULTI;
	}

	if (lif->rx_mode != rx_mode)
		_ionic_lif_rx_mode(lif, rx_mode);
}