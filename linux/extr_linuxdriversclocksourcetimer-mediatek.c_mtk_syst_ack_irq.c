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
struct timer_of {int dummy; } ;

/* Variables and functions */
 int SYST_CON_EN ; 
 int SYST_CON_IRQ_CLR ; 
 int /*<<< orphan*/  SYST_CON_REG (struct timer_of*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_syst_ack_irq(struct timer_of *to)
{
	/* Clear and disable interrupt */
	writel(SYST_CON_IRQ_CLR | SYST_CON_EN, SYST_CON_REG(to));
}