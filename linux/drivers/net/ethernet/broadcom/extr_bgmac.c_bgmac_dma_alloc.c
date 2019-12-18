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
typedef  int /*<<< orphan*/  u16 ;
struct device {int dummy; } ;
struct bgmac_dma_ring {void* index_base; int /*<<< orphan*/  dma_base; void* unaligned; int /*<<< orphan*/  mmio_base; void* cpu_base; } ;
struct bgmac_dma_desc {int dummy; } ;
struct bgmac {int feature_flags; int /*<<< orphan*/  dev; struct bgmac_dma_ring* rx_ring; struct bgmac_dma_ring* tx_ring; struct device* dma_dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BCMA_IOST ; 
 int BCMA_IOST_DMA64 ; 
#define  BGMAC_DMA_BASE0 131 
#define  BGMAC_DMA_BASE1 130 
#define  BGMAC_DMA_BASE2 129 
#define  BGMAC_DMA_BASE3 128 
 int /*<<< orphan*/  BGMAC_DMA_RING_RX ; 
 int /*<<< orphan*/  BGMAC_DMA_RING_TX ; 
 int BGMAC_FEAT_IDM_MASK ; 
 int BGMAC_MAX_RX_RINGS ; 
 int BGMAC_MAX_TX_RINGS ; 
 int BGMAC_RX_RING_SLOTS ; 
 int BGMAC_TX_RING_SLOTS ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int ENOMEM ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bgmac_dma_free (struct bgmac*) ; 
 void* bgmac_dma_unaligned (struct bgmac*,struct bgmac_dma_ring*,int /*<<< orphan*/ ) ; 
 int bgmac_idm_read (struct bgmac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 void* dma_alloc_coherent (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* lower_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bgmac_dma_alloc(struct bgmac *bgmac)
{
	struct device *dma_dev = bgmac->dma_dev;
	struct bgmac_dma_ring *ring;
	static const u16 ring_base[] = { BGMAC_DMA_BASE0, BGMAC_DMA_BASE1,
					 BGMAC_DMA_BASE2, BGMAC_DMA_BASE3, };
	int size; /* ring size: different for Tx and Rx */
	int i;

	BUILD_BUG_ON(BGMAC_MAX_TX_RINGS > ARRAY_SIZE(ring_base));
	BUILD_BUG_ON(BGMAC_MAX_RX_RINGS > ARRAY_SIZE(ring_base));

	if (!(bgmac->feature_flags & BGMAC_FEAT_IDM_MASK)) {
		if (!(bgmac_idm_read(bgmac, BCMA_IOST) & BCMA_IOST_DMA64)) {
			dev_err(bgmac->dev, "Core does not report 64-bit DMA\n");
			return -ENOTSUPP;
		}
	}

	for (i = 0; i < BGMAC_MAX_TX_RINGS; i++) {
		ring = &bgmac->tx_ring[i];
		ring->mmio_base = ring_base[i];

		/* Alloc ring of descriptors */
		size = BGMAC_TX_RING_SLOTS * sizeof(struct bgmac_dma_desc);
		ring->cpu_base = dma_alloc_coherent(dma_dev, size,
						    &ring->dma_base,
						    GFP_KERNEL);
		if (!ring->cpu_base) {
			dev_err(bgmac->dev, "Allocation of TX ring 0x%X failed\n",
				ring->mmio_base);
			goto err_dma_free;
		}

		ring->unaligned = bgmac_dma_unaligned(bgmac, ring,
						      BGMAC_DMA_RING_TX);
		if (ring->unaligned)
			ring->index_base = lower_32_bits(ring->dma_base);
		else
			ring->index_base = 0;

		/* No need to alloc TX slots yet */
	}

	for (i = 0; i < BGMAC_MAX_RX_RINGS; i++) {
		ring = &bgmac->rx_ring[i];
		ring->mmio_base = ring_base[i];

		/* Alloc ring of descriptors */
		size = BGMAC_RX_RING_SLOTS * sizeof(struct bgmac_dma_desc);
		ring->cpu_base = dma_alloc_coherent(dma_dev, size,
						    &ring->dma_base,
						    GFP_KERNEL);
		if (!ring->cpu_base) {
			dev_err(bgmac->dev, "Allocation of RX ring 0x%X failed\n",
				ring->mmio_base);
			goto err_dma_free;
		}

		ring->unaligned = bgmac_dma_unaligned(bgmac, ring,
						      BGMAC_DMA_RING_RX);
		if (ring->unaligned)
			ring->index_base = lower_32_bits(ring->dma_base);
		else
			ring->index_base = 0;
	}

	return 0;

err_dma_free:
	bgmac_dma_free(bgmac);
	return -ENOMEM;
}