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
struct s5p_mfc_priv_buf {int size; scalar_t__ dma; unsigned int ctx; scalar_t__ virt; } ;
struct s5p_mfc_dev {int mem_size; scalar_t__ mem_base; scalar_t__* dma_base; struct device** mem_dev; scalar_t__ mem_virt; int /*<<< orphan*/  mem_bitmap; } ;
struct device {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SHIFT ; 
 int SZ_64K ; 
 unsigned int bitmap_find_next_zero_area (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  bitmap_set (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 scalar_t__ dma_alloc_coherent (struct device*,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mfc_debug (int,char*,int,...) ; 
 int /*<<< orphan*/  mfc_err (char*,...) ; 

int s5p_mfc_alloc_priv_buf(struct s5p_mfc_dev *dev, unsigned int mem_ctx,
			   struct s5p_mfc_priv_buf *b)
{
	unsigned int bits = dev->mem_size >> PAGE_SHIFT;
	unsigned int count = b->size >> PAGE_SHIFT;
	unsigned int align = (SZ_64K >> PAGE_SHIFT) - 1;
	unsigned int start, offset;

	mfc_debug(3, "Allocating priv: %zu\n", b->size);

	if (dev->mem_virt) {
		start = bitmap_find_next_zero_area(dev->mem_bitmap, bits, 0, count, align);
		if (start > bits)
			goto no_mem;

		bitmap_set(dev->mem_bitmap, start, count);
		offset = start << PAGE_SHIFT;
		b->virt = dev->mem_virt + offset;
		b->dma = dev->mem_base + offset;
	} else {
		struct device *mem_dev = dev->mem_dev[mem_ctx];
		dma_addr_t base = dev->dma_base[mem_ctx];

		b->ctx = mem_ctx;
		b->virt = dma_alloc_coherent(mem_dev, b->size, &b->dma, GFP_KERNEL);
		if (!b->virt)
			goto no_mem;
		if (b->dma < base) {
			mfc_err("Invalid memory configuration - buffer (%pad) is below base memory address(%pad)\n",
				&b->dma, &base);
			dma_free_coherent(mem_dev, b->size, b->virt, b->dma);
			return -ENOMEM;
		}
	}

	mfc_debug(3, "Allocated addr %p %pad\n", b->virt, &b->dma);
	return 0;
no_mem:
	mfc_err("Allocating private buffer of size %zu failed\n", b->size);
	return -ENOMEM;
}