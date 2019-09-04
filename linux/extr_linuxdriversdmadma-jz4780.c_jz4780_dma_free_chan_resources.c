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
struct jz4780_dma_chan {int /*<<< orphan*/ * desc_pool; int /*<<< orphan*/  vchan; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ *) ; 
 struct jz4780_dma_chan* to_jz4780_dma_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  vchan_free_chan_resources (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void jz4780_dma_free_chan_resources(struct dma_chan *chan)
{
	struct jz4780_dma_chan *jzchan = to_jz4780_dma_chan(chan);

	vchan_free_chan_resources(&jzchan->vchan);
	dma_pool_destroy(jzchan->desc_pool);
	jzchan->desc_pool = NULL;
}