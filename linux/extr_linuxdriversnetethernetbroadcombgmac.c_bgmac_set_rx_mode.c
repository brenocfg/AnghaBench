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
struct net_device {int flags; } ;
struct bgmac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BGMAC_CMDCFG_PROM ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  bgmac_cmdcfg_maskset (struct bgmac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct bgmac* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void bgmac_set_rx_mode(struct net_device *net_dev)
{
	struct bgmac *bgmac = netdev_priv(net_dev);

	if (net_dev->flags & IFF_PROMISC)
		bgmac_cmdcfg_maskset(bgmac, ~0, BGMAC_CMDCFG_PROM, true);
	else
		bgmac_cmdcfg_maskset(bgmac, ~BGMAC_CMDCFG_PROM, 0, true);
}