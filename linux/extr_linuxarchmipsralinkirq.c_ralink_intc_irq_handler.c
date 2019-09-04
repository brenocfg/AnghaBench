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
typedef  scalar_t__ u32 ;
struct irq_domain {int dummy; } ;
struct irq_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTC_REG_STATUS0 ; 
 int /*<<< orphan*/  __ffs (scalar_t__) ; 
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 
 struct irq_domain* irq_desc_get_handler_data (struct irq_desc*) ; 
 int /*<<< orphan*/  irq_find_mapping (struct irq_domain*,int /*<<< orphan*/ ) ; 
 scalar_t__ rt_intc_r32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spurious_interrupt () ; 

__attribute__((used)) static void ralink_intc_irq_handler(struct irq_desc *desc)
{
	u32 pending = rt_intc_r32(INTC_REG_STATUS0);

	if (pending) {
		struct irq_domain *domain = irq_desc_get_handler_data(desc);
		generic_handle_irq(irq_find_mapping(domain, __ffs(pending)));
	} else {
		spurious_interrupt();
	}
}