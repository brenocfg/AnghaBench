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
struct irq_service {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  construct (struct irq_service*,struct irq_service_init_data*) ; 
 struct irq_service* kzalloc (int,int /*<<< orphan*/ ) ; 

struct irq_service *dal_irq_service_dcn20_create(
	struct irq_service_init_data *init_data)
{
	struct irq_service *irq_service = kzalloc(sizeof(*irq_service),
						  GFP_KERNEL);

	if (!irq_service)
		return NULL;

	construct(irq_service, init_data);
	return irq_service;
}