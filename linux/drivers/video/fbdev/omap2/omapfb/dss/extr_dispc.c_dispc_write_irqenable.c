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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  DISPC_IRQENABLE ; 
 int /*<<< orphan*/  dispc_clear_irqstatus (int) ; 
 int dispc_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_write_reg (int /*<<< orphan*/ ,int) ; 

void dispc_write_irqenable(u32 mask)
{
	u32 old_mask = dispc_read_reg(DISPC_IRQENABLE);

	/* clear the irqstatus for newly enabled irqs */
	dispc_clear_irqstatus((mask ^ old_mask) & mask);

	dispc_write_reg(DISPC_IRQENABLE, mask);
}