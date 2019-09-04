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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int OMAP3430_ST_IO_CHAIN_MASK ; 
 int OMAP3430_ST_IO_MASK ; 
 int /*<<< orphan*/  WKUP_MOD ; 
 int omap_prm_clear_mod_irqs (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static irqreturn_t _prcm_int_handle_io(int irq, void *unused)
{
	int c;

	c = omap_prm_clear_mod_irqs(WKUP_MOD, 1, OMAP3430_ST_IO_MASK |
				    OMAP3430_ST_IO_CHAIN_MASK);

	return c ? IRQ_HANDLED : IRQ_NONE;
}