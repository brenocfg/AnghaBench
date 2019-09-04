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
struct pxad_chan {int /*<<< orphan*/  vc; int /*<<< orphan*/  wq_state; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_chan_running (struct pxad_chan*) ; 
 struct pxad_chan* to_pxad_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  vchan_synchronize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pxad_synchronize(struct dma_chan *dchan)
{
	struct pxad_chan *chan = to_pxad_chan(dchan);

	wait_event(chan->wq_state, !is_chan_running(chan));
	vchan_synchronize(&chan->vc);
}