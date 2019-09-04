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
struct mxc_gpio_port {int both_edges; int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 int fls (int) ; 
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_find_mapping (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mxc_flip_edge (struct mxc_gpio_port*,int) ; 

__attribute__((used)) static void mxc_gpio_irq_handler(struct mxc_gpio_port *port, u32 irq_stat)
{
	while (irq_stat != 0) {
		int irqoffset = fls(irq_stat) - 1;

		if (port->both_edges & (1 << irqoffset))
			mxc_flip_edge(port, irqoffset);

		generic_handle_irq(irq_find_mapping(port->domain, irqoffset));

		irq_stat &= ~(1 << irqoffset);
	}
}