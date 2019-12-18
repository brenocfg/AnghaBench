#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pasemi_mac {TYPE_2__* dma_pdev; } ;
struct TYPE_4__ {int chno; } ;
struct TYPE_6__ {TYPE_1__ chan; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int MAX_RETRIES ; 
 int /*<<< orphan*/  PAS_DMA_RXCHAN_CCMDSTA (int) ; 
 unsigned int PAS_DMA_RXCHAN_CCMDSTA_ACT ; 
 int /*<<< orphan*/  PAS_DMA_RXCHAN_CCMDSTA_ST ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int) ; 
 unsigned int read_dma_reg (int /*<<< orphan*/ ) ; 
 TYPE_3__* rx_ring (struct pasemi_mac*) ; 
 int /*<<< orphan*/  write_dma_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pasemi_mac_pause_rxchan(struct pasemi_mac *mac)
{
	unsigned int sta, retries;
	int rxch = rx_ring(mac)->chan.chno;

	write_dma_reg(PAS_DMA_RXCHAN_CCMDSTA(rxch),
		      PAS_DMA_RXCHAN_CCMDSTA_ST);
	for (retries = 0; retries < MAX_RETRIES; retries++) {
		sta = read_dma_reg(PAS_DMA_RXCHAN_CCMDSTA(rxch));
		if (!(sta & PAS_DMA_RXCHAN_CCMDSTA_ACT))
			break;
		cond_resched();
	}

	if (sta & PAS_DMA_RXCHAN_CCMDSTA_ACT)
		dev_err(&mac->dma_pdev->dev,
			"Failed to stop rx channel, ccmdsta 08%x\n", sta);
	write_dma_reg(PAS_DMA_RXCHAN_CCMDSTA(rxch), 0);
}