#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_8__ {int /*<<< orphan*/ * data_ring; int /*<<< orphan*/  data_bus; int /*<<< orphan*/  page_info; TYPE_3__* qpl; } ;
struct TYPE_6__ {int /*<<< orphan*/ * desc_ring; int /*<<< orphan*/  bus; } ;
struct gve_rx_ring {int mask; TYPE_4__ data; int /*<<< orphan*/ * q_resources; int /*<<< orphan*/  q_resources_bus; TYPE_2__ desc; } ;
struct gve_rx_desc {int dummy; } ;
struct gve_priv {int rx_desc_cnt; int /*<<< orphan*/  dev; TYPE_1__* pdev; struct gve_rx_ring* rx; } ;
struct device {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (struct device*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  gve_rx_remove_from_block (struct gve_priv*,int) ; 
 int /*<<< orphan*/  gve_unassign_qpl (struct gve_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_dbg (struct gve_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void gve_rx_free_ring(struct gve_priv *priv, int idx)
{
	struct gve_rx_ring *rx = &priv->rx[idx];
	struct device *dev = &priv->pdev->dev;
	size_t bytes;
	u32 slots;

	gve_rx_remove_from_block(priv, idx);

	bytes = sizeof(struct gve_rx_desc) * priv->rx_desc_cnt;
	dma_free_coherent(dev, bytes, rx->desc.desc_ring, rx->desc.bus);
	rx->desc.desc_ring = NULL;

	dma_free_coherent(dev, sizeof(*rx->q_resources),
			  rx->q_resources, rx->q_resources_bus);
	rx->q_resources = NULL;

	gve_unassign_qpl(priv, rx->data.qpl->id);
	rx->data.qpl = NULL;
	kvfree(rx->data.page_info);

	slots = rx->mask + 1;
	bytes = sizeof(*rx->data.data_ring) * slots;
	dma_free_coherent(dev, bytes, rx->data.data_ring,
			  rx->data.data_bus);
	rx->data.data_ring = NULL;
	netif_dbg(priv, drv, priv->dev, "freed rx ring %d\n", idx);
}