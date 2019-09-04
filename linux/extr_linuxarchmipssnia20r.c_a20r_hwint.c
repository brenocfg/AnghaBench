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
 int /*<<< orphan*/  IE_IRQ0 ; 
 scalar_t__ SNI_A20R_IRQ_BASE ; 
 int a20r_ack_hwint () ; 
 int /*<<< orphan*/  clear_c0_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_IRQ (scalar_t__) ; 
 int ffs (int) ; 
 scalar_t__ likely (int) ; 
 int read_c0_cause () ; 
 int /*<<< orphan*/  set_c0_status (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void a20r_hwint(void)
{
	u32 cause, status;
	int irq;

	clear_c0_status(IE_IRQ0);
	status = a20r_ack_hwint();
	cause = read_c0_cause();

	irq = ffs(((cause & status) >> 8) & 0xf8);
	if (likely(irq > 0))
		do_IRQ(SNI_A20R_IRQ_BASE + irq - 1);
	set_c0_status(IE_IRQ0);
}