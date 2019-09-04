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
struct TYPE_2__ {int /*<<< orphan*/  phys; int /*<<< orphan*/  chan; } ;
struct timb_dma_desc {struct timb_dma_desc* desc_list; int /*<<< orphan*/  desc_list_len; TYPE_1__ txd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  chan2dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chan2dmadev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,struct timb_dma_desc*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct timb_dma_desc*) ; 

__attribute__((used)) static void td_free_desc(struct timb_dma_desc *td_desc)
{
	dev_dbg(chan2dev(td_desc->txd.chan), "Freeing desc: %p\n", td_desc);
	dma_unmap_single(chan2dmadev(td_desc->txd.chan), td_desc->txd.phys,
		td_desc->desc_list_len, DMA_TO_DEVICE);

	kfree(td_desc->desc_list);
	kfree(td_desc);
}