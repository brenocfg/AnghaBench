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

/* Variables and functions */
 int XICS_IPI ; 
 int /*<<< orphan*/  icp_native_set_xirr (int) ; 

__attribute__((used)) static void icp_native_flush_ipi(void)
{
	/* We take the ipi irq but and never return so we
	 * need to EOI the IPI, but want to leave our priority 0
	 *
	 * should we check all the other interrupts too?
	 * should we be flagging idle loop instead?
	 * or creating some task to be scheduled?
	 */

	icp_native_set_xirr((0x00 << 24) | XICS_IPI);
}