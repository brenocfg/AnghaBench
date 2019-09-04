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
struct lpc32xx_kscan_drv {int matrix_sz; int /*<<< orphan*/  input; int /*<<< orphan*/  kscan_base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  LPC32XX_KS_IRQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpc32xx_mod_states (struct lpc32xx_kscan_drv*,int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t lpc32xx_kscan_irq(int irq, void *dev_id)
{
	struct lpc32xx_kscan_drv *kscandat = dev_id;
	int i;

	for (i = 0; i < kscandat->matrix_sz; i++)
		lpc32xx_mod_states(kscandat, i);

	writel(1, LPC32XX_KS_IRQ(kscandat->kscan_base));

	input_sync(kscandat->input);

	return IRQ_HANDLED;
}