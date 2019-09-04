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
typedef  size_t u32 ;
struct axi_dma_chip {TYPE_2__* dw; } ;
struct TYPE_4__ {int /*<<< orphan*/ * chan; TYPE_1__* hdata; } ;
struct TYPE_3__ {size_t nr_channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWAXIDMAC_IRQ_ALL ; 
 int /*<<< orphan*/  axi_chan_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  axi_chan_irq_disable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void axi_dma_hw_init(struct axi_dma_chip *chip)
{
	u32 i;

	for (i = 0; i < chip->dw->hdata->nr_channels; i++) {
		axi_chan_irq_disable(&chip->dw->chan[i], DWAXIDMAC_IRQ_ALL);
		axi_chan_disable(&chip->dw->chan[i]);
	}
}