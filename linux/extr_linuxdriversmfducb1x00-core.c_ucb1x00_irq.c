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
struct ucb1x00 {scalar_t__ irq_base; } ;
struct irq_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UCB_IE_CLEAR ; 
 int /*<<< orphan*/  UCB_IE_STATUS ; 
 int /*<<< orphan*/  generic_handle_irq (scalar_t__) ; 
 struct ucb1x00* irq_desc_get_handler_data (struct irq_desc*) ; 
 int /*<<< orphan*/  ucb1x00_disable (struct ucb1x00*) ; 
 int /*<<< orphan*/  ucb1x00_enable (struct ucb1x00*) ; 
 unsigned int ucb1x00_reg_read (struct ucb1x00*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucb1x00_reg_write (struct ucb1x00*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void ucb1x00_irq(struct irq_desc *desc)
{
	struct ucb1x00 *ucb = irq_desc_get_handler_data(desc);
	unsigned int isr, i;

	ucb1x00_enable(ucb);
	isr = ucb1x00_reg_read(ucb, UCB_IE_STATUS);
	ucb1x00_reg_write(ucb, UCB_IE_CLEAR, isr);
	ucb1x00_reg_write(ucb, UCB_IE_CLEAR, 0);

	for (i = 0; i < 16 && isr; i++, isr >>= 1)
		if (isr & 1)
			generic_handle_irq(ucb->irq_base + i);
	ucb1x00_disable(ucb);
}