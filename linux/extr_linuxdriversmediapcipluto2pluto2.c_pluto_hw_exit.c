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
struct pluto {int dummy; } ;

/* Variables and functions */
 int MISC_ALED ; 
 int MISC_LED0 ; 
 int MISC_LED1 ; 
 int /*<<< orphan*/  REG_MISC ; 
 int /*<<< orphan*/  pluto_disable_irqs (struct pluto*) ; 
 int /*<<< orphan*/  pluto_dma_unmap (struct pluto*) ; 
 int /*<<< orphan*/  pluto_reset_frontend (struct pluto*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pluto_reset_ts (struct pluto*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pluto_rw (struct pluto*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void pluto_hw_exit(struct pluto *pluto)
{
	/* disable interrupts */
	pluto_disable_irqs(pluto);

	pluto_reset_ts(pluto, 0);

	/* LED: disable automatic control, enable yellow, disable green */
	pluto_rw(pluto, REG_MISC, MISC_ALED | MISC_LED1 | MISC_LED0, MISC_LED1);

	/* unmap DMA */
	pluto_dma_unmap(pluto);

	pluto_reset_frontend(pluto, 0);
}