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
struct net_device {scalar_t__ base_addr; scalar_t__ dma; } ;
struct corkscrew_private {scalar_t__ dev; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  CORKSCREW_TOTAL_SIZE ; 
 scalar_t__ EL3_CMD ; 
 int /*<<< orphan*/  TotalReset ; 
 int /*<<< orphan*/  free_dma (scalar_t__) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 struct corkscrew_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pnp_device_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_region (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_pnp_dev (scalar_t__) ; 

__attribute__((used)) static void cleanup_card(struct net_device *dev)
{
	struct corkscrew_private *vp = netdev_priv(dev);
	list_del_init(&vp->list);
	if (dev->dma)
		free_dma(dev->dma);
	outw(TotalReset, dev->base_addr + EL3_CMD);
	release_region(dev->base_addr, CORKSCREW_TOTAL_SIZE);
	if (vp->dev)
		pnp_device_detach(to_pnp_dev(vp->dev));
}