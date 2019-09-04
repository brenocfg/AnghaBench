#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pasemi_mac {int /*<<< orphan*/  dma_if; TYPE_1__* dma_pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int MAX_RETRIES ; 
 int /*<<< orphan*/  PAS_DMA_RXINT_RCMDSTA (int /*<<< orphan*/ ) ; 
 unsigned int PAS_DMA_RXINT_RCMDSTA_ACT ; 
 int /*<<< orphan*/  PAS_DMA_RXINT_RCMDSTA_ST ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int) ; 
 unsigned int read_dma_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_dma_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pasemi_mac_pause_rxint(struct pasemi_mac *mac)
{
	unsigned int sta, retries;

	write_dma_reg(PAS_DMA_RXINT_RCMDSTA(mac->dma_if),
		      PAS_DMA_RXINT_RCMDSTA_ST);
	for (retries = 0; retries < MAX_RETRIES; retries++) {
		sta = read_dma_reg(PAS_DMA_RXINT_RCMDSTA(mac->dma_if));
		if (!(sta & PAS_DMA_RXINT_RCMDSTA_ACT))
			break;
		cond_resched();
	}

	if (sta & PAS_DMA_RXINT_RCMDSTA_ACT)
		dev_err(&mac->dma_pdev->dev,
			"Failed to stop rx interface, rcmdsta %08x\n", sta);
	write_dma_reg(PAS_DMA_RXINT_RCMDSTA(mac->dma_if), 0);
}