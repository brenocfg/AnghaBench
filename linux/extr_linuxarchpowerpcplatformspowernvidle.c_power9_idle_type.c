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
 unsigned long __power9_idle_type (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  irq_set_pending_from_srr1 (unsigned long) ; 

void power9_idle_type(unsigned long stop_psscr_val,
				      unsigned long stop_psscr_mask)
{
	unsigned long srr1;

	srr1 = __power9_idle_type(stop_psscr_val, stop_psscr_mask);
	irq_set_pending_from_srr1(srr1);
}