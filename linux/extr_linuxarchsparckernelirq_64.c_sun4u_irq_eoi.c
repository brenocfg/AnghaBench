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
struct irq_handler_data {int /*<<< orphan*/  iclr; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICLR_IDLE ; 
 struct irq_handler_data* irq_data_get_irq_handler_data (struct irq_data*) ; 
 scalar_t__ likely (struct irq_handler_data*) ; 
 int /*<<< orphan*/  upa_writeq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sun4u_irq_eoi(struct irq_data *data)
{
	struct irq_handler_data *handler_data;

	handler_data = irq_data_get_irq_handler_data(data);
	if (likely(handler_data))
		upa_writeq(ICLR_IDLE, handler_data->iclr);
}