#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int /*<<< orphan*/  qpl; } ;
struct gve_tx_ring {int q_num; int mask; int /*<<< orphan*/ * info; int /*<<< orphan*/ * desc; scalar_t__ bus; TYPE_2__ tx_fifo; int /*<<< orphan*/  netdev_txq; void* q_resources; scalar_t__ q_resources_bus; } ;
struct gve_priv {int tx_desc_cnt; int /*<<< orphan*/  dev; TYPE_1__* pdev; struct gve_tx_ring* tx; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* dma_alloc_coherent (struct device*,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,size_t,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  gve_assign_tx_qpl (struct gve_priv*) ; 
 int /*<<< orphan*/  gve_tx_add_to_block (struct gve_priv*,int) ; 
 scalar_t__ gve_tx_fifo_init (struct gve_priv*,TYPE_2__*) ; 
 int /*<<< orphan*/  gve_tx_fifo_release (struct gve_priv*,TYPE_2__*) ; 
 int /*<<< orphan*/  memset (struct gve_tx_ring*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_get_tx_queue (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_dbg (struct gve_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,unsigned long) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vzalloc (int) ; 

__attribute__((used)) static int gve_tx_alloc_ring(struct gve_priv *priv, int idx)
{
	struct gve_tx_ring *tx = &priv->tx[idx];
	struct device *hdev = &priv->pdev->dev;
	u32 slots = priv->tx_desc_cnt;
	size_t bytes;

	/* Make sure everything is zeroed to start */
	memset(tx, 0, sizeof(*tx));
	tx->q_num = idx;

	tx->mask = slots - 1;

	/* alloc metadata */
	tx->info = vzalloc(sizeof(*tx->info) * slots);
	if (!tx->info)
		return -ENOMEM;

	/* alloc tx queue */
	bytes = sizeof(*tx->desc) * slots;
	tx->desc = dma_alloc_coherent(hdev, bytes, &tx->bus, GFP_KERNEL);
	if (!tx->desc)
		goto abort_with_info;

	tx->tx_fifo.qpl = gve_assign_tx_qpl(priv);

	/* map Tx FIFO */
	if (gve_tx_fifo_init(priv, &tx->tx_fifo))
		goto abort_with_desc;

	tx->q_resources =
		dma_alloc_coherent(hdev,
				   sizeof(*tx->q_resources),
				   &tx->q_resources_bus,
				   GFP_KERNEL);
	if (!tx->q_resources)
		goto abort_with_fifo;

	netif_dbg(priv, drv, priv->dev, "tx[%d]->bus=%lx\n", idx,
		  (unsigned long)tx->bus);
	tx->netdev_txq = netdev_get_tx_queue(priv->dev, idx);
	gve_tx_add_to_block(priv, idx);

	return 0;

abort_with_fifo:
	gve_tx_fifo_release(priv, &tx->tx_fifo);
abort_with_desc:
	dma_free_coherent(hdev, bytes, tx->desc, tx->bus);
	tx->desc = NULL;
abort_with_info:
	vfree(tx->info);
	tx->info = NULL;
	return -ENOMEM;
}