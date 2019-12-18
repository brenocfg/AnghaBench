#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct perf_thread {int /*<<< orphan*/  dma_sync; int /*<<< orphan*/  src; int /*<<< orphan*/  tidx; int /*<<< orphan*/  dma_chan; struct perf_ctx* perf; } ;
struct perf_ctx {int /*<<< orphan*/  twait; int /*<<< orphan*/  tsync; TYPE_2__* ntb; TYPE_1__* test_peer; } ;
typedef  int /*<<< orphan*/  dma_cap_mask_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  outbuf_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_MEMCPY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_to_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cap_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_request_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct perf_ctx*) ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmalloc_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_dma_filter ; 
 int /*<<< orphan*/  use_dma ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int perf_init_test(struct perf_thread *pthr)
{
	struct perf_ctx *perf = pthr->perf;
	dma_cap_mask_t dma_mask;

	pthr->src = kmalloc_node(perf->test_peer->outbuf_size, GFP_KERNEL,
				 dev_to_node(&perf->ntb->dev));
	if (!pthr->src)
		return -ENOMEM;

	get_random_bytes(pthr->src, perf->test_peer->outbuf_size);

	if (!use_dma)
		return 0;

	dma_cap_zero(dma_mask);
	dma_cap_set(DMA_MEMCPY, dma_mask);
	pthr->dma_chan = dma_request_channel(dma_mask, perf_dma_filter, perf);
	if (!pthr->dma_chan) {
		dev_err(&perf->ntb->dev, "%d: Failed to get DMA channel\n",
			pthr->tidx);
		atomic_dec(&perf->tsync);
		wake_up(&perf->twait);
		kfree(pthr->src);
		return -ENODEV;
	}

	atomic_set(&pthr->dma_sync, 0);

	return 0;
}