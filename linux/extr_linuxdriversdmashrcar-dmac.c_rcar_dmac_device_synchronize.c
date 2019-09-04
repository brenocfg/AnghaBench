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
struct rcar_dmac_chan {int /*<<< orphan*/  irq; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 struct rcar_dmac_chan* to_rcar_dmac_chan (struct dma_chan*) ; 

__attribute__((used)) static void rcar_dmac_device_synchronize(struct dma_chan *chan)
{
	struct rcar_dmac_chan *rchan = to_rcar_dmac_chan(chan);

	synchronize_irq(rchan->irq);
}