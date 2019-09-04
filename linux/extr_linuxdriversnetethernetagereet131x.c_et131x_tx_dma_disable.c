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
struct et131x_adapter {TYPE_2__* regs; } ;
struct TYPE_3__ {int /*<<< orphan*/  csr; } ;
struct TYPE_4__ {TYPE_1__ txdma; } ;

/* Variables and functions */
 int ET_TXDMA_CSR_HALT ; 
 int ET_TXDMA_SNGL_EPKT ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void et131x_tx_dma_disable(struct et131x_adapter *adapter)
{
	/* Setup the transmit dma configuration register */
	writel(ET_TXDMA_CSR_HALT | ET_TXDMA_SNGL_EPKT,
	       &adapter->regs->txdma.csr);
}