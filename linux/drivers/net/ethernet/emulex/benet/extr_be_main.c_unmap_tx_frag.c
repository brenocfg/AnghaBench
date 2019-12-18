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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct device {int dummy; } ;
struct be_eth_wrb {int /*<<< orphan*/  frag_pa_lo; int /*<<< orphan*/  frag_pa_hi; int /*<<< orphan*/  frag_len; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dma_unmap_page (struct device*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unmap_tx_frag(struct device *dev, struct be_eth_wrb *wrb,
			  bool unmap_single)
{
	dma_addr_t dma;
	u32 frag_len = le32_to_cpu(wrb->frag_len);


	dma = (u64)le32_to_cpu(wrb->frag_pa_hi) << 32 |
		(u64)le32_to_cpu(wrb->frag_pa_lo);
	if (frag_len) {
		if (unmap_single)
			dma_unmap_single(dev, dma, frag_len, DMA_TO_DEVICE);
		else
			dma_unmap_page(dev, dma, frag_len, DMA_TO_DEVICE);
	}
}