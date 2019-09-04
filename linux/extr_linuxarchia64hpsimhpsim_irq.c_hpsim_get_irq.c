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
 int /*<<< orphan*/  AUTO_ASSIGN ; 
 int assign_irq_vector (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_simple_irq ; 
 int /*<<< orphan*/  hpsim_connect_irq (int,int) ; 
 int /*<<< orphan*/  hpsim_irq_set_chip (int) ; 
 int /*<<< orphan*/  irq_set_handler (int,int /*<<< orphan*/ ) ; 

int hpsim_get_irq(int intr)
{
	int irq = assign_irq_vector(AUTO_ASSIGN);

	if (irq >= 0) {
		hpsim_irq_set_chip(irq);
		irq_set_handler(irq, handle_simple_irq);
		hpsim_connect_irq(intr, irq);
	}

	return irq;
}