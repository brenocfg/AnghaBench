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
struct pxad_chan {int /*<<< orphan*/  prio; int /*<<< orphan*/  drcmr; int /*<<< orphan*/ * desc_pool; int /*<<< orphan*/  vc; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PXAD_PRIO_LOWEST ; 
 int /*<<< orphan*/  U32_MAX ; 
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ *) ; 
 struct pxad_chan* to_pxad_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  vchan_free_chan_resources (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pxad_free_chan_resources(struct dma_chan *dchan)
{
	struct pxad_chan *chan = to_pxad_chan(dchan);

	vchan_free_chan_resources(&chan->vc);
	dma_pool_destroy(chan->desc_pool);
	chan->desc_pool = NULL;

	chan->drcmr = U32_MAX;
	chan->prio = PXAD_PRIO_LOWEST;
}