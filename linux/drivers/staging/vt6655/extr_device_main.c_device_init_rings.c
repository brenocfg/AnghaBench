#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vnt_tx_desc {int dummy; } ;
struct vnt_rx_desc {int dummy; } ;
struct TYPE_4__ {int rx_descs0; int rx_descs1; int* tx_descs; } ;
struct vnt_private {TYPE_2__ opts; scalar_t__ tx_bufs_dma1; scalar_t__ tx_beacon_dma; scalar_t__ tx_bufs_dma0; void* tx_beacon_bufs; void* pbyTmpBuff; void* tx1_bufs; void* tx0_bufs; void* apTD1Rings; void* apTD0Rings; scalar_t__ td0_pool_dma; scalar_t__ td1_pool_dma; scalar_t__ rd1_pool_dma; scalar_t__ pool_dma; TYPE_1__* pcid; scalar_t__ rd0_pool_dma; void* aRD1Ring; void* aRD0Ring; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CB_BEACON_BUF_SIZE ; 
 int CB_MAX_BUF_SIZE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int PKT_BUF_SZ ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,void*,scalar_t__) ; 

__attribute__((used)) static bool device_init_rings(struct vnt_private *priv)
{
	void *vir_pool;

	/*allocate all RD/TD rings a single pool*/
	vir_pool = dma_alloc_coherent(&priv->pcid->dev,
				      priv->opts.rx_descs0 * sizeof(struct vnt_rx_desc) + priv->opts.rx_descs1 * sizeof(struct vnt_rx_desc) + priv->opts.tx_descs[0] * sizeof(struct vnt_tx_desc) + priv->opts.tx_descs[1] * sizeof(struct vnt_tx_desc),
				      &priv->pool_dma, GFP_ATOMIC);
	if (!vir_pool) {
		dev_err(&priv->pcid->dev, "allocate desc dma memory failed\n");
		return false;
	}

	priv->aRD0Ring = vir_pool;
	priv->aRD1Ring = vir_pool +
		priv->opts.rx_descs0 * sizeof(struct vnt_rx_desc);

	priv->rd0_pool_dma = priv->pool_dma;
	priv->rd1_pool_dma = priv->rd0_pool_dma +
		priv->opts.rx_descs0 * sizeof(struct vnt_rx_desc);

	priv->tx0_bufs = dma_alloc_coherent(&priv->pcid->dev,
					    priv->opts.tx_descs[0] * PKT_BUF_SZ + priv->opts.tx_descs[1] * PKT_BUF_SZ + CB_BEACON_BUF_SIZE + CB_MAX_BUF_SIZE,
					    &priv->tx_bufs_dma0, GFP_ATOMIC);
	if (!priv->tx0_bufs) {
		dev_err(&priv->pcid->dev, "allocate buf dma memory failed\n");

		dma_free_coherent(&priv->pcid->dev,
				  priv->opts.rx_descs0 * sizeof(struct vnt_rx_desc) +
				  priv->opts.rx_descs1 * sizeof(struct vnt_rx_desc) +
				  priv->opts.tx_descs[0] * sizeof(struct vnt_tx_desc) +
				  priv->opts.tx_descs[1] * sizeof(struct vnt_tx_desc),
				  vir_pool, priv->pool_dma);
		return false;
	}

	priv->td0_pool_dma = priv->rd1_pool_dma +
		priv->opts.rx_descs1 * sizeof(struct vnt_rx_desc);

	priv->td1_pool_dma = priv->td0_pool_dma +
		priv->opts.tx_descs[0] * sizeof(struct vnt_tx_desc);

	/* vir_pool: pvoid type */
	priv->apTD0Rings = vir_pool
		+ priv->opts.rx_descs0 * sizeof(struct vnt_rx_desc)
		+ priv->opts.rx_descs1 * sizeof(struct vnt_rx_desc);

	priv->apTD1Rings = vir_pool
		+ priv->opts.rx_descs0 * sizeof(struct vnt_rx_desc)
		+ priv->opts.rx_descs1 * sizeof(struct vnt_rx_desc)
		+ priv->opts.tx_descs[0] * sizeof(struct vnt_tx_desc);

	priv->tx1_bufs = priv->tx0_bufs +
		priv->opts.tx_descs[0] * PKT_BUF_SZ;

	priv->tx_beacon_bufs = priv->tx1_bufs +
		priv->opts.tx_descs[1] * PKT_BUF_SZ;

	priv->pbyTmpBuff = priv->tx_beacon_bufs +
		CB_BEACON_BUF_SIZE;

	priv->tx_bufs_dma1 = priv->tx_bufs_dma0 +
		priv->opts.tx_descs[0] * PKT_BUF_SZ;

	priv->tx_beacon_dma = priv->tx_bufs_dma1 +
		priv->opts.tx_descs[1] * PKT_BUF_SZ;

	return true;
}