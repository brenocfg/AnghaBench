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
struct xgene_enet_pdata {TYPE_1__* ring_ops; } ;
struct xgene_enet_desc_ring {int /*<<< orphan*/  dma; int /*<<< orphan*/  desc_addr; int /*<<< orphan*/  size; int /*<<< orphan*/  ndev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* clear ) (struct xgene_enet_desc_ring*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  devm_kfree (struct device*,struct xgene_enet_desc_ring*) ; 
 int /*<<< orphan*/  dmam_free_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct device* ndev_to_dev (int /*<<< orphan*/ ) ; 
 struct xgene_enet_pdata* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct xgene_enet_desc_ring*) ; 

__attribute__((used)) static void xgene_enet_free_desc_ring(struct xgene_enet_desc_ring *ring)
{
	struct xgene_enet_pdata *pdata;
	struct device *dev;

	if (!ring)
		return;

	dev = ndev_to_dev(ring->ndev);
	pdata = netdev_priv(ring->ndev);

	if (ring->desc_addr) {
		pdata->ring_ops->clear(ring);
		dmam_free_coherent(dev, ring->size, ring->desc_addr, ring->dma);
	}
	devm_kfree(dev, ring);
}