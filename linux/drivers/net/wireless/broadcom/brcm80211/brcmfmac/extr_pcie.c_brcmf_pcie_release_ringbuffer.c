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
typedef  int u32 ;
struct device {int dummy; } ;
struct TYPE_2__ {int depth; int item_len; void* buf_addr; } ;
struct brcmf_pcie_ringbuf {int /*<<< orphan*/  dma_handle; TYPE_1__ commonring; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct brcmf_pcie_ringbuf*) ; 

__attribute__((used)) static void brcmf_pcie_release_ringbuffer(struct device *dev,
					  struct brcmf_pcie_ringbuf *ring)
{
	void *dma_buf;
	u32 size;

	if (!ring)
		return;

	dma_buf = ring->commonring.buf_addr;
	if (dma_buf) {
		size = ring->commonring.depth * ring->commonring.item_len;
		dma_free_coherent(dev, size, dma_buf, ring->dma_handle);
	}
	kfree(ring);
}