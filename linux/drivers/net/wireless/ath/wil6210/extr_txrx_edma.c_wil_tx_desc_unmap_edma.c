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
typedef  union wil_tx_desc {int dummy; } wil_tx_desc ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  length; } ;
struct wil_tx_enhanced_desc {TYPE_1__ dma; } ;
struct wil_ctx {int mapped_as; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dma_unmap_page (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
#define  wil_mapped_as_page 129 
#define  wil_mapped_as_single 128 
 int /*<<< orphan*/  wil_tx_desc_get_addr_edma (TYPE_1__*) ; 

__attribute__((used)) static void wil_tx_desc_unmap_edma(struct device *dev,
				   union wil_tx_desc *desc,
				   struct wil_ctx *ctx)
{
	struct wil_tx_enhanced_desc *d = (struct wil_tx_enhanced_desc *)desc;
	dma_addr_t pa = wil_tx_desc_get_addr_edma(&d->dma);
	u16 dmalen = le16_to_cpu(d->dma.length);

	switch (ctx->mapped_as) {
	case wil_mapped_as_single:
		dma_unmap_single(dev, pa, dmalen, DMA_TO_DEVICE);
		break;
	case wil_mapped_as_page:
		dma_unmap_page(dev, pa, dmalen, DMA_TO_DEVICE);
		break;
	default:
		break;
	}
}