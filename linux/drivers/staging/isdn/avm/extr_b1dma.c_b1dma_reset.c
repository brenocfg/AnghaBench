#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int csr; scalar_t__ cardtype; int /*<<< orphan*/  port; } ;
typedef  TYPE_1__ avmcard ;

/* Variables and functions */
 int /*<<< orphan*/  AMCC_INTCSR ; 
 int /*<<< orphan*/  AMCC_MCSR ; 
 int /*<<< orphan*/  AMCC_RXLEN ; 
 int /*<<< orphan*/  AMCC_TXLEN ; 
 scalar_t__ avm_t1pci ; 
 int /*<<< orphan*/  b1dma_writel (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  t1outp (int /*<<< orphan*/ ,int,int) ; 

void b1dma_reset(avmcard *card)
{
	card->csr = 0x0;
	b1dma_writel(card, card->csr, AMCC_INTCSR);
	b1dma_writel(card, 0, AMCC_MCSR);
	b1dma_writel(card, 0, AMCC_RXLEN);
	b1dma_writel(card, 0, AMCC_TXLEN);

	t1outp(card->port, 0x10, 0x00);
	t1outp(card->port, 0x07, 0x00);

	b1dma_writel(card, 0, AMCC_MCSR);
	mdelay(10);
	b1dma_writel(card, 0x0f000000, AMCC_MCSR); /* reset all */
	mdelay(10);
	b1dma_writel(card, 0, AMCC_MCSR);
	if (card->cardtype == avm_t1pci)
		mdelay(42);
	else
		mdelay(10);
}