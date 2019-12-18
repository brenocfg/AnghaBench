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
struct irq_service_init_data {scalar_t__ ctx; } ;
struct irq_service {scalar_t__ ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 

void dal_irq_service_construct(
	struct irq_service *irq_service,
	struct irq_service_init_data *init_data)
{
	if (!init_data || !init_data->ctx) {
		BREAK_TO_DEBUGGER();
		return;
	}

	irq_service->ctx = init_data->ctx;
}