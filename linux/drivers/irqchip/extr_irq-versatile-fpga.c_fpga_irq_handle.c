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
typedef  int u32 ;
struct irq_desc {int dummy; } ;
struct fpga_irq_data {int /*<<< orphan*/  domain; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ IRQ_STATUS ; 
 int /*<<< orphan*/  do_bad_IRQ (struct irq_desc*) ; 
 int ffs (int) ; 
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 
 struct fpga_irq_data* irq_desc_get_handler_data (struct irq_desc*) ; 
 int /*<<< orphan*/  irq_find_mapping (int /*<<< orphan*/ ,unsigned int) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static void fpga_irq_handle(struct irq_desc *desc)
{
	struct fpga_irq_data *f = irq_desc_get_handler_data(desc);
	u32 status = readl(f->base + IRQ_STATUS);

	if (status == 0) {
		do_bad_IRQ(desc);
		return;
	}

	do {
		unsigned int irq = ffs(status) - 1;

		status &= ~(1 << irq);
		generic_handle_irq(irq_find_mapping(f->domain, irq));
	} while (status);
}