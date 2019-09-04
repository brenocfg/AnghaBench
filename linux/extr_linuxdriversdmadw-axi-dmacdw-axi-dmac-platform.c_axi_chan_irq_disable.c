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
typedef  int /*<<< orphan*/  u32 ;
struct axi_dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH_INTSTATUS_ENA ; 
 int /*<<< orphan*/  DWAXIDMAC_IRQ_ALL ; 
 int /*<<< orphan*/  DWAXIDMAC_IRQ_NONE ; 
 int /*<<< orphan*/  axi_chan_ioread32 (struct axi_dma_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  axi_chan_iowrite32 (struct axi_dma_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static inline void axi_chan_irq_disable(struct axi_dma_chan *chan, u32 irq_mask)
{
	u32 val;

	if (likely(irq_mask == DWAXIDMAC_IRQ_ALL)) {
		axi_chan_iowrite32(chan, CH_INTSTATUS_ENA, DWAXIDMAC_IRQ_NONE);
	} else {
		val = axi_chan_ioread32(chan, CH_INTSTATUS_ENA);
		val &= ~irq_mask;
		axi_chan_iowrite32(chan, CH_INTSTATUS_ENA, val);
	}
}