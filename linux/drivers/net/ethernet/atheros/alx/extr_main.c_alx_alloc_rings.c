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
struct alx_txd {int dummy; } ;
struct alx_rrd {int dummy; } ;
struct alx_rfd {int dummy; } ;
struct TYPE_7__ {int size; int /*<<< orphan*/  virt; int /*<<< orphan*/  dma; } ;
struct TYPE_6__ {TYPE_1__* pdev; } ;
struct alx_priv {int tx_ringsz; int num_txq; int rx_ringsz; int /*<<< orphan*/  dev; TYPE_4__** qnapi; TYPE_3__ descmem; TYPE_2__ hw; } ;
struct TYPE_8__ {int /*<<< orphan*/  rxq; int /*<<< orphan*/  txq; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int alx_alloc_rx_ring (struct alx_priv*,int /*<<< orphan*/ ,int) ; 
 int alx_alloc_tx_ring (struct alx_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int alx_alloc_rings(struct alx_priv *alx)
{
	int i, offset = 0;

	/* physical tx/rx ring descriptors
	 *
	 * Allocate them as a single chunk because they must not cross a
	 * 4G boundary (hardware has a single register for high 32 bits
	 * of addresses only)
	 */
	alx->descmem.size = sizeof(struct alx_txd) * alx->tx_ringsz *
			    alx->num_txq +
			    sizeof(struct alx_rrd) * alx->rx_ringsz +
			    sizeof(struct alx_rfd) * alx->rx_ringsz;
	alx->descmem.virt = dma_alloc_coherent(&alx->hw.pdev->dev,
					       alx->descmem.size,
					       &alx->descmem.dma, GFP_KERNEL);
	if (!alx->descmem.virt)
		return -ENOMEM;

	/* alignment requirements */
	BUILD_BUG_ON(sizeof(struct alx_txd) % 8);
	BUILD_BUG_ON(sizeof(struct alx_rrd) % 8);

	for (i = 0; i < alx->num_txq; i++) {
		offset = alx_alloc_tx_ring(alx, alx->qnapi[i]->txq, offset);
		if (offset < 0) {
			netdev_err(alx->dev, "Allocation of tx buffer failed!\n");
			return -ENOMEM;
		}
	}

	offset = alx_alloc_rx_ring(alx, alx->qnapi[0]->rxq, offset);
	if (offset < 0) {
		netdev_err(alx->dev, "Allocation of rx buffer failed!\n");
		return -ENOMEM;
	}

	return 0;
}