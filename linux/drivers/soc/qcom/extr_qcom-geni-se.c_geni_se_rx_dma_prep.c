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
typedef  size_t u32 ;
struct geni_wrapper {int /*<<< orphan*/  dev; } ;
struct geni_se {scalar_t__ base; struct geni_wrapper* wrapper; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int EINVAL ; 
 int EIO ; 
 size_t GENI_SE_DMA_AHB_ERR_EN ; 
 size_t GENI_SE_DMA_DONE_EN ; 
 size_t GENI_SE_DMA_EOT_EN ; 
 scalar_t__ SE_DMA_RX_ATTR ; 
 scalar_t__ SE_DMA_RX_IRQ_EN_SET ; 
 scalar_t__ SE_DMA_RX_LEN ; 
 scalar_t__ SE_DMA_RX_PTR_H ; 
 scalar_t__ SE_DMA_RX_PTR_L ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t lower_32_bits (int /*<<< orphan*/ ) ; 
 size_t upper_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (size_t,scalar_t__) ; 

int geni_se_rx_dma_prep(struct geni_se *se, void *buf, size_t len,
			dma_addr_t *iova)
{
	struct geni_wrapper *wrapper = se->wrapper;
	u32 val;

	if (!wrapper)
		return -EINVAL;

	*iova = dma_map_single(wrapper->dev, buf, len, DMA_FROM_DEVICE);
	if (dma_mapping_error(wrapper->dev, *iova))
		return -EIO;

	val = GENI_SE_DMA_DONE_EN;
	val |= GENI_SE_DMA_EOT_EN;
	val |= GENI_SE_DMA_AHB_ERR_EN;
	writel_relaxed(val, se->base + SE_DMA_RX_IRQ_EN_SET);
	writel_relaxed(lower_32_bits(*iova), se->base + SE_DMA_RX_PTR_L);
	writel_relaxed(upper_32_bits(*iova), se->base + SE_DMA_RX_PTR_H);
	/* RX does not have EOT buffer type bit. So just reset RX_ATTR */
	writel_relaxed(0, se->base + SE_DMA_RX_ATTR);
	writel_relaxed(len, se->base + SE_DMA_RX_LEN);
	return 0;
}