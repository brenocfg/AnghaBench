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
struct kp2000_device {int /*<<< orphan*/  dma_common_regs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int KPC_DMA_CARD_IRQ_ENABLE ; 
 int KPC_DMA_CARD_USER_INTERRUPT_ACTIVE ; 
 int KPC_DMA_CARD_USER_INTERRUPT_MODE ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t kp2000_irq_handler(int irq, void *dev_id)
{
	struct kp2000_device *pcard = dev_id;

	writel(KPC_DMA_CARD_IRQ_ENABLE |
	       KPC_DMA_CARD_USER_INTERRUPT_MODE |
	       KPC_DMA_CARD_USER_INTERRUPT_ACTIVE,
	       pcard->dma_common_regs);
	return IRQ_HANDLED;
}