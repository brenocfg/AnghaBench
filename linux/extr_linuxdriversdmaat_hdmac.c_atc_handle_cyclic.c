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
struct dma_async_tx_descriptor {int dummy; } ;
struct at_dma_chan {int /*<<< orphan*/  chan_common; } ;
struct at_desc {struct dma_async_tx_descriptor txd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSCR ; 
 struct at_desc* atc_first_active (struct at_dma_chan*) ; 
 int /*<<< orphan*/  chan2dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  channel_readl (struct at_dma_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_desc_get_callback_invoke (struct dma_async_tx_descriptor*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void atc_handle_cyclic(struct at_dma_chan *atchan)
{
	struct at_desc			*first = atc_first_active(atchan);
	struct dma_async_tx_descriptor	*txd = &first->txd;

	dev_vdbg(chan2dev(&atchan->chan_common),
			"new cyclic period llp 0x%08x\n",
			channel_readl(atchan, DSCR));

	dmaengine_desc_get_callback_invoke(txd, NULL);
}