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
struct s5p_mfc_priv_buf {size_t ctx; int /*<<< orphan*/  size; int /*<<< orphan*/  dma; int /*<<< orphan*/ * virt; } ;
struct s5p_mfc_dev {struct device** mem_dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void s5p_mfc_release_generic_buf(struct s5p_mfc_dev *dev,
			      struct s5p_mfc_priv_buf *b)
{
	struct device *mem_dev = dev->mem_dev[b->ctx];
	dma_free_coherent(mem_dev, b->size, b->virt, b->dma);
	b->virt = NULL;
	b->dma = 0;
	b->size = 0;
}