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
 unsigned long __power7_idle_type (unsigned long) ; 
 int /*<<< orphan*/  irq_set_pending_from_srr1 (unsigned long) ; 

void power7_idle_type(unsigned long type)
{
	unsigned long srr1;

	srr1 = __power7_idle_type(type);
	irq_set_pending_from_srr1(srr1);
}