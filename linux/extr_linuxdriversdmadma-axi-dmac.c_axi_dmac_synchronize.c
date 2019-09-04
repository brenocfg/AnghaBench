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
struct dma_chan {int dummy; } ;
struct axi_dmac_chan {int /*<<< orphan*/  vchan; } ;

/* Variables and functions */
 struct axi_dmac_chan* to_axi_dmac_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  vchan_synchronize (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void axi_dmac_synchronize(struct dma_chan *c)
{
	struct axi_dmac_chan *chan = to_axi_dmac_chan(c);

	vchan_synchronize(&chan->vchan);
}