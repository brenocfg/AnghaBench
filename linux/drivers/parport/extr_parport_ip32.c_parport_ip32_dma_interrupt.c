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
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  ctx; scalar_t__ left; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  MACEPAR_CONTEXT_DATA_BOUND ; 
 TYPE_1__ parport_ip32_dma ; 
 int /*<<< orphan*/  parport_ip32_dma_setup_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_trace (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t parport_ip32_dma_interrupt(int irq, void *dev_id)
{
	if (parport_ip32_dma.left)
		pr_trace(NULL, "(%d): ctx=%d", irq, parport_ip32_dma.ctx);
	parport_ip32_dma_setup_context(MACEPAR_CONTEXT_DATA_BOUND);
	return IRQ_HANDLED;
}