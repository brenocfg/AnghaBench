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
 int /*<<< orphan*/  CH_INTSIGNAL_ENA ; 
 int /*<<< orphan*/  axi_chan_iowrite32 (struct axi_dma_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void axi_chan_irq_sig_set(struct axi_dma_chan *chan, u32 irq_mask)
{
	axi_chan_iowrite32(chan, CH_INTSIGNAL_ENA, irq_mask);
}