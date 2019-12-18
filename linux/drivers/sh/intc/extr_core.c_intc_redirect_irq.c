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
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 
 scalar_t__ irq_desc_get_handler_data (struct irq_desc*) ; 

__attribute__((used)) static void intc_redirect_irq(struct irq_desc *desc)
{
	generic_handle_irq((unsigned int)irq_desc_get_handler_data(desc));
}