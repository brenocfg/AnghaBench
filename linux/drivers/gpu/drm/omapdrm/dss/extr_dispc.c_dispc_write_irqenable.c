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
struct dispc_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISPC_IRQENABLE ; 
 int /*<<< orphan*/  dispc_clear_irqstatus (struct dispc_device*,int) ; 
 int dispc_read_reg (struct dispc_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_write_reg (struct dispc_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dispc_write_irqenable(struct dispc_device *dispc, u32 mask)
{
	u32 old_mask = dispc_read_reg(dispc, DISPC_IRQENABLE);

	/* clear the irqstatus for newly enabled irqs */
	dispc_clear_irqstatus(dispc, (mask ^ old_mask) & mask);

	dispc_write_reg(dispc, DISPC_IRQENABLE, mask);

	/* flush posted write */
	dispc_read_reg(dispc, DISPC_IRQENABLE);
}