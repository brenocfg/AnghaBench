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
struct pch_dma_chan {int /*<<< orphan*/  active_list; } ;

/* Variables and functions */
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ list_is_singular (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdc_chain_complete (struct pch_dma_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdc_complete_all (struct pch_dma_chan*) ; 
 int /*<<< orphan*/  pdc_dostart (struct pch_dma_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdc_first_active (struct pch_dma_chan*) ; 

__attribute__((used)) static void pdc_advance_work(struct pch_dma_chan *pd_chan)
{
	if (list_empty(&pd_chan->active_list) ||
		list_is_singular(&pd_chan->active_list)) {
		pdc_complete_all(pd_chan);
	} else {
		pdc_chain_complete(pd_chan, pdc_first_active(pd_chan));
		pdc_dostart(pd_chan, pdc_first_active(pd_chan));
	}
}