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
struct cdns3_endpoint {int /*<<< orphan*/ * trb_pool; int /*<<< orphan*/  trb_pool_dma; struct cdns3_device* cdns3_dev; } ;
struct cdns3_device {int /*<<< orphan*/  sysdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdns3_ring_size (struct cdns3_endpoint*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cdns3_free_trb_pool(struct cdns3_endpoint *priv_ep)
{
	struct cdns3_device *priv_dev = priv_ep->cdns3_dev;

	if (priv_ep->trb_pool) {
		dma_free_coherent(priv_dev->sysdev,
				  cdns3_ring_size(priv_ep),
				  priv_ep->trb_pool, priv_ep->trb_pool_dma);
		priv_ep->trb_pool = NULL;
	}
}