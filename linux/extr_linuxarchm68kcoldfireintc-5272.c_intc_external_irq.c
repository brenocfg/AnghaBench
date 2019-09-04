#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct irq_desc {int /*<<< orphan*/  irq_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* irq_ack ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  handle_simple_irq (struct irq_desc*) ; 
 TYPE_1__* irq_desc_get_chip (struct irq_desc*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void intc_external_irq(struct irq_desc *desc)
{
	irq_desc_get_chip(desc)->irq_ack(&desc->irq_data);
	handle_simple_irq(desc);
}