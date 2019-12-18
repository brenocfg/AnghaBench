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
struct s5p_mfc_priv_buf {unsigned int ctx; int /*<<< orphan*/  size; int /*<<< orphan*/  dma; int /*<<< orphan*/  virt; } ;
struct s5p_mfc_dev {struct device** mem_dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_alloc_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfc_debug (int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  mfc_err (char*,int /*<<< orphan*/ ) ; 

int s5p_mfc_alloc_generic_buf(struct s5p_mfc_dev *dev, unsigned int mem_ctx,
			   struct s5p_mfc_priv_buf *b)
{
	struct device *mem_dev = dev->mem_dev[mem_ctx];

	mfc_debug(3, "Allocating generic buf: %zu\n", b->size);

	b->ctx = mem_ctx;
	b->virt = dma_alloc_coherent(mem_dev, b->size, &b->dma, GFP_KERNEL);
	if (!b->virt)
		goto no_mem;

	mfc_debug(3, "Allocated addr %p %pad\n", b->virt, &b->dma);
	return 0;
no_mem:
	mfc_err("Allocating generic buffer of size %zu failed\n", b->size);
	return -ENOMEM;
}