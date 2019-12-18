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
struct s5p_mfc_priv_buf {unsigned int dma; unsigned int size; size_t ctx; int /*<<< orphan*/ * virt; } ;
struct s5p_mfc_dev {unsigned int mem_base; struct device** mem_dev; int /*<<< orphan*/  mem_bitmap; scalar_t__ mem_virt; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned int PAGE_SHIFT ; 
 int /*<<< orphan*/  bitmap_clear (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,unsigned int,int /*<<< orphan*/ *,unsigned int) ; 

void s5p_mfc_release_priv_buf(struct s5p_mfc_dev *dev,
			      struct s5p_mfc_priv_buf *b)
{
	if (dev->mem_virt) {
		unsigned int start = (b->dma - dev->mem_base) >> PAGE_SHIFT;
		unsigned int count = b->size >> PAGE_SHIFT;

		bitmap_clear(dev->mem_bitmap, start, count);
	} else {
		struct device *mem_dev = dev->mem_dev[b->ctx];

		dma_free_coherent(mem_dev, b->size, b->virt, b->dma);
	}
	b->virt = NULL;
	b->dma = 0;
	b->size = 0;
}