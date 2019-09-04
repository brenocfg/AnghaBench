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
struct stih_cec {scalar_t__ regs; int /*<<< orphan*/  irq_status; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ CEC_STATUS ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t stih_cec_irq_handler(int irq, void *priv)
{
	struct stih_cec *cec = priv;

	cec->irq_status = readl(cec->regs + CEC_STATUS);
	writel(cec->irq_status, cec->regs + CEC_STATUS);

	return IRQ_WAKE_THREAD;
}