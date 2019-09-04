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
struct dpaa_bp {int /*<<< orphan*/  size; int /*<<< orphan*/  dev; } ;
struct bm_buffer {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  bm_buf_addr (struct bm_buffer*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phys_to_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_free_frag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void dpaa_bp_free_pf(const struct dpaa_bp *bp,
				   struct bm_buffer *bmb)
{
	dma_addr_t addr = bm_buf_addr(bmb);

	dma_unmap_single(bp->dev, addr, bp->size, DMA_FROM_DEVICE);

	skb_free_frag(phys_to_virt(addr));
}