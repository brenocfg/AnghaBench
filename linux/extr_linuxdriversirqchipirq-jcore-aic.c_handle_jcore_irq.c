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
struct irq_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  handle_percpu_irq (struct irq_desc*) ; 
 int /*<<< orphan*/  handle_simple_irq (struct irq_desc*) ; 
 int /*<<< orphan*/  irq_desc_get_irq_data (struct irq_desc*) ; 
 scalar_t__ irqd_is_per_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_jcore_irq(struct irq_desc *desc)
{
	if (irqd_is_per_cpu(irq_desc_get_irq_data(desc)))
		handle_percpu_irq(desc);
	else
		handle_simple_irq(desc);
}