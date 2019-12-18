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
struct b43_dma {int parity; void* rx_ring; void* tx_ring_mcast; void* tx_ring_AC_VO; void* tx_ring_AC_VI; void* tx_ring_AC_BE; void* tx_ring_AC_BK; int /*<<< orphan*/  translation_in_low; int /*<<< orphan*/  translation; } ;
struct b43_wldev {int /*<<< orphan*/  wl; TYPE_1__* dev; struct b43_dma dma; } ;
typedef  enum b43_dmatype { ____Placeholder_b43_dmatype } b43_dmatype ;
struct TYPE_2__ {int bus_type; int core_rev; int /*<<< orphan*/  sdev; int /*<<< orphan*/  bdev; int /*<<< orphan*/  dma_dev; } ;

/* Variables and functions */
#define  B43_BUS_BCMA 129 
#define  B43_BUS_SSB 128 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  b43_dma_translation_in_low_word (struct b43_wldev*,int) ; 
 int b43_engine_type (struct b43_wldev*) ; 
 void* b43_setup_dmaring (struct b43_wldev*,int,int,int) ; 
 int /*<<< orphan*/  b43dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  b43err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  bcma_core_dma_translation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_ring (struct b43_dma*,int /*<<< orphan*/ ) ; 
 int dma_set_mask_and_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssb_dma_translation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tx_ring_AC_BE ; 
 int /*<<< orphan*/  tx_ring_AC_BK ; 
 int /*<<< orphan*/  tx_ring_AC_VI ; 
 int /*<<< orphan*/  tx_ring_AC_VO ; 
 int /*<<< orphan*/  tx_ring_mcast ; 

int b43_dma_init(struct b43_wldev *dev)
{
	struct b43_dma *dma = &dev->dma;
	enum b43_dmatype type = b43_engine_type(dev);
	int err;

	err = dma_set_mask_and_coherent(dev->dev->dma_dev, DMA_BIT_MASK(type));
	if (err) {
		b43err(dev->wl, "The machine/kernel does not support "
		       "the required %u-bit DMA mask\n", type);
		return err;
	}

	switch (dev->dev->bus_type) {
#ifdef CONFIG_B43_BCMA
	case B43_BUS_BCMA:
		dma->translation = bcma_core_dma_translation(dev->dev->bdev);
		break;
#endif
#ifdef CONFIG_B43_SSB
	case B43_BUS_SSB:
		dma->translation = ssb_dma_translation(dev->dev->sdev);
		break;
#endif
	}
	dma->translation_in_low = b43_dma_translation_in_low_word(dev, type);

	dma->parity = true;
#ifdef CONFIG_B43_BCMA
	/* TODO: find out which SSB devices need disabling parity */
	if (dev->dev->bus_type == B43_BUS_BCMA)
		dma->parity = false;
#endif

	err = -ENOMEM;
	/* setup TX DMA channels. */
	dma->tx_ring_AC_BK = b43_setup_dmaring(dev, 0, 1, type);
	if (!dma->tx_ring_AC_BK)
		goto out;

	dma->tx_ring_AC_BE = b43_setup_dmaring(dev, 1, 1, type);
	if (!dma->tx_ring_AC_BE)
		goto err_destroy_bk;

	dma->tx_ring_AC_VI = b43_setup_dmaring(dev, 2, 1, type);
	if (!dma->tx_ring_AC_VI)
		goto err_destroy_be;

	dma->tx_ring_AC_VO = b43_setup_dmaring(dev, 3, 1, type);
	if (!dma->tx_ring_AC_VO)
		goto err_destroy_vi;

	dma->tx_ring_mcast = b43_setup_dmaring(dev, 4, 1, type);
	if (!dma->tx_ring_mcast)
		goto err_destroy_vo;

	/* setup RX DMA channel. */
	dma->rx_ring = b43_setup_dmaring(dev, 0, 0, type);
	if (!dma->rx_ring)
		goto err_destroy_mcast;

	/* No support for the TX status DMA ring. */
	B43_WARN_ON(dev->dev->core_rev < 5);

	b43dbg(dev->wl, "%u-bit DMA initialized\n",
	       (unsigned int)type);
	err = 0;
out:
	return err;

err_destroy_mcast:
	destroy_ring(dma, tx_ring_mcast);
err_destroy_vo:
	destroy_ring(dma, tx_ring_AC_VO);
err_destroy_vi:
	destroy_ring(dma, tx_ring_AC_VI);
err_destroy_be:
	destroy_ring(dma, tx_ring_AC_BE);
err_destroy_bk:
	destroy_ring(dma, tx_ring_AC_BK);
	return err;
}