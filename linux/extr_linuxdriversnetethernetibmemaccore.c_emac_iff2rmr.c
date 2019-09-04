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
typedef  int u32 ;
struct net_device {int flags; int /*<<< orphan*/  mtu; } ;
struct emac_instance {int dummy; } ;

/* Variables and functions */
 int EMAC4_RMR_BASE ; 
 int EMAC4_RMR_MJS (int /*<<< orphan*/ ) ; 
 int EMAC4_RMR_MJS_MASK ; 
 int /*<<< orphan*/  EMAC_APM821XX_REQ_JUMBO_FRAME_SIZE ; 
 int /*<<< orphan*/  EMAC_FTR_EMAC4 ; 
 int EMAC_RMR_BAE ; 
 int EMAC_RMR_BASE ; 
 int EMAC_RMR_IAE ; 
 int EMAC_RMR_MAE ; 
 int EMAC_RMR_PME ; 
 int EMAC_RMR_PMME ; 
 int EMAC_RMR_SFCS ; 
 int EMAC_RMR_SP ; 
 scalar_t__ EMAC_XAHT_SLOTS (struct emac_instance*) ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 scalar_t__ emac_has_feature (struct emac_instance*,int /*<<< orphan*/ ) ; 
 scalar_t__ netdev_mc_count (struct net_device*) ; 
 int /*<<< orphan*/  netdev_mc_empty (struct net_device*) ; 
 struct emac_instance* netdev_priv (struct net_device*) ; 

__attribute__((used)) static inline u32 emac_iff2rmr(struct net_device *ndev)
{
	struct emac_instance *dev = netdev_priv(ndev);
	u32 r;

	r = EMAC_RMR_SP | EMAC_RMR_SFCS | EMAC_RMR_IAE | EMAC_RMR_BAE;

	if (emac_has_feature(dev, EMAC_FTR_EMAC4))
	    r |= EMAC4_RMR_BASE;
	else
	    r |= EMAC_RMR_BASE;

	if (ndev->flags & IFF_PROMISC)
		r |= EMAC_RMR_PME;
	else if (ndev->flags & IFF_ALLMULTI ||
			 (netdev_mc_count(ndev) > EMAC_XAHT_SLOTS(dev)))
		r |= EMAC_RMR_PMME;
	else if (!netdev_mc_empty(ndev))
		r |= EMAC_RMR_MAE;

	if (emac_has_feature(dev, EMAC_APM821XX_REQ_JUMBO_FRAME_SIZE)) {
		r &= ~EMAC4_RMR_MJS_MASK;
		r |= EMAC4_RMR_MJS(ndev->mtu);
	}

	return r;
}