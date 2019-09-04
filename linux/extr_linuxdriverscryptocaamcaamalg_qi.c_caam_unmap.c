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
struct scatterlist {int dummy; } ;
struct device {int dummy; } ;
typedef  enum optype { ____Placeholder_optype } optype ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int GIVENCRYPT ; 
 int /*<<< orphan*/  dma_unmap_sg (struct device*,struct scatterlist*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void caam_unmap(struct device *dev, struct scatterlist *src,
		       struct scatterlist *dst, int src_nents,
		       int dst_nents, dma_addr_t iv_dma, int ivsize,
		       enum optype op_type, dma_addr_t qm_sg_dma,
		       int qm_sg_bytes)
{
	if (dst != src) {
		if (src_nents)
			dma_unmap_sg(dev, src, src_nents, DMA_TO_DEVICE);
		dma_unmap_sg(dev, dst, dst_nents, DMA_FROM_DEVICE);
	} else {
		dma_unmap_sg(dev, src, src_nents, DMA_BIDIRECTIONAL);
	}

	if (iv_dma)
		dma_unmap_single(dev, iv_dma, ivsize,
				 op_type == GIVENCRYPT ? DMA_FROM_DEVICE :
							 DMA_TO_DEVICE);
	if (qm_sg_bytes)
		dma_unmap_single(dev, qm_sg_dma, qm_sg_bytes, DMA_TO_DEVICE);
}