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
struct z8530_channel {int /*<<< orphan*/  dma_tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  z8530_tx (struct z8530_channel*) ; 

__attribute__((used)) static void z8530_dma_tx(struct z8530_channel *chan)
{
	if(!chan->dma_tx)
	{
		pr_warn("Hey who turned the DMA off?\n");
		z8530_tx(chan);
		return;
	}
	/* This shouldn't occur in DMA mode */
	pr_err("DMA tx - bogus event!\n");
	z8530_tx(chan);
}