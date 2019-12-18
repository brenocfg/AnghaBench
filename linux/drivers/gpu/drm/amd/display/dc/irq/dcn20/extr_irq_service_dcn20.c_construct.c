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
struct irq_service_init_data {int dummy; } ;
struct irq_service {int /*<<< orphan*/ * funcs; int /*<<< orphan*/  info; } ;

/* Variables and functions */
 int /*<<< orphan*/  dal_irq_service_construct (struct irq_service*,struct irq_service_init_data*) ; 
 int /*<<< orphan*/  irq_service_funcs_dcn20 ; 
 int /*<<< orphan*/  irq_source_info_dcn20 ; 

__attribute__((used)) static void construct(
	struct irq_service *irq_service,
	struct irq_service_init_data *init_data)
{
	dal_irq_service_construct(irq_service, init_data);

	irq_service->info = irq_source_info_dcn20;
	irq_service->funcs = &irq_service_funcs_dcn20;
}