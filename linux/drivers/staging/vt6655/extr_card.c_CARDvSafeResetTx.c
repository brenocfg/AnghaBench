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
struct TYPE_4__ {void* owner; } ;
struct vnt_tx_desc {TYPE_2__ td0; } ;
struct TYPE_3__ {unsigned int* tx_descs; } ;
struct vnt_private {int /*<<< orphan*/  tx_beacon_dma; int /*<<< orphan*/  PortOffset; int /*<<< orphan*/  td1_pool_dma; int /*<<< orphan*/  td0_pool_dma; struct vnt_tx_desc* apTD1Rings; TYPE_1__ opts; struct vnt_tx_desc* apTD0Rings; scalar_t__* iTDUsed; struct vnt_tx_desc** apCurrTD; struct vnt_tx_desc** apTailTD; } ;

/* Variables and functions */
 int /*<<< orphan*/  MACvSetCurrBCNTxDescAddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACvSetCurrTXDescAddr (int /*<<< orphan*/ ,struct vnt_private*,int /*<<< orphan*/ ) ; 
 void* OWNED_BY_HOST ; 
 int /*<<< orphan*/  TYPE_AC0DMA ; 
 unsigned int TYPE_MAXTD ; 
 int /*<<< orphan*/  TYPE_TXDMA0 ; 

void CARDvSafeResetTx(struct vnt_private *priv)
{
	unsigned int uu;
	struct vnt_tx_desc *pCurrTD;

	/* initialize TD index */
	priv->apTailTD[0] = &priv->apTD0Rings[0];
	priv->apCurrTD[0] = &priv->apTD0Rings[0];

	priv->apTailTD[1] = &priv->apTD1Rings[0];
	priv->apCurrTD[1] = &priv->apTD1Rings[0];

	for (uu = 0; uu < TYPE_MAXTD; uu++)
		priv->iTDUsed[uu] = 0;

	for (uu = 0; uu < priv->opts.tx_descs[0]; uu++) {
		pCurrTD = &priv->apTD0Rings[uu];
		pCurrTD->td0.owner = OWNED_BY_HOST;
		/* init all Tx Packet pointer to NULL */
	}
	for (uu = 0; uu < priv->opts.tx_descs[1]; uu++) {
		pCurrTD = &priv->apTD1Rings[uu];
		pCurrTD->td0.owner = OWNED_BY_HOST;
		/* init all Tx Packet pointer to NULL */
	}

	/* set MAC TD pointer */
	MACvSetCurrTXDescAddr(TYPE_TXDMA0, priv, priv->td0_pool_dma);

	MACvSetCurrTXDescAddr(TYPE_AC0DMA, priv, priv->td1_pool_dma);

	/* set MAC Beacon TX pointer */
	MACvSetCurrBCNTxDescAddr(priv->PortOffset,
				 (priv->tx_beacon_dma));
}