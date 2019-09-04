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
 int /*<<< orphan*/  IRQ_LEVEL ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  irq_clear_status_flags (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_and_handler_name (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lapic_chip ; 

__attribute__((used)) static void lapic_register_intr(int irq)
{
	irq_clear_status_flags(irq, IRQ_LEVEL);
	irq_set_chip_and_handler_name(irq, &lapic_chip, handle_edge_irq,
				      "edge");
}