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
struct sonic_local {int /*<<< orphan*/  descriptors_laddr; int /*<<< orphan*/  descriptors; int /*<<< orphan*/  dma_bitmode; int /*<<< orphan*/  device; } ;
struct nubus_board {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int SIZEOF_SONIC_DESC ; 
 int SONIC_BUS_SCALE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct sonic_local* netdev_priv (struct net_device*) ; 
 struct net_device* nubus_get_drvdata (struct nubus_board*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int mac_sonic_nubus_remove(struct nubus_board *board)
{
	struct net_device *ndev = nubus_get_drvdata(board);
	struct sonic_local *lp = netdev_priv(ndev);

	unregister_netdev(ndev);
	dma_free_coherent(lp->device,
			  SIZEOF_SONIC_DESC * SONIC_BUS_SCALE(lp->dma_bitmode),
			  lp->descriptors, lp->descriptors_laddr);
	free_netdev(ndev);

	return 0;
}